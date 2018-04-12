#include <LiquidCrystal.h> 
#include <Keypad.h> 
#include <SPI.h> 
#include <EEPROM.h> 
#include <SD.h> 
 
File myFile; 
// Constants 
const byte NUM_PRESIDENTIAL_CANDIDATES = 4; 
const byte LCD_RS = 2; 
const byte LCD_E = 3; 
const byte LCD_D4 = 4; 
const byte LCD_D5 = 5; 
const byte LCD_D6 = 6; 
const byte LCD_D7 = 7; 
const byte ROWS = 4; //four rows 
const byte COLS = 4; //four columns 
const byte SD_CS = 10; 
const byte enable_pin = 1; 
const byte pin_addr = 0; 
const byte pin_length = 0; 
const byte counter_addr = pin_addr + pin_length; 

char hexaKeys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'}, 
  {'*', '0', '#', 'D'} 
}; 
byte rowPins[ROWS] = {8, 9, 14, 15}; //connect to the row pinouts of the keypad 
byte colPins[COLS] = {16, 17, 18, 19}; //connect to the column pinouts of the keypad 
 
//Candidate classes 
 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7); 

void initial_prompt(){
    lcd.clear();
    lcd.print("Cast Vote:");
    lcd.setCursor(0, 3);
    lcd.print("*-cancel");
    lcd.setCursor(0, 2); 
}

void invalid_prompt(){
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.print("Invalid Choice");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("               ");
    lcd.setCursor(0,1);
    lcd.print("Choose Again");
    delay(500);
}

class Candidate{
  private:
  String code;
  String Name;
  word* votes;
  word num_prefs;
  
  public:
  Candidate(){ 
    code="0";
    Name=" ";
    *votes = 0;
  }
  Candidate( String candCode, String candName){
    code = candCode;
    Name = candName;
    num_prefs = 0;
    *votes = 0;
  }
  Candidate(String candCode, String candName, word num_pref){
    code = candCode;
    Name = candName;
    num_prefs = num_pref;
    for(word i=0; i<num_prefs; i++){
      *(votes+i*sizeof(word))= 0;
    }
  }
  void vote(word pref_num){
    if(pref_num >= 0 && pref_num < num_prefs){ 
      *(votes+pref_num) += 1; 
    }  
    else
      return;
  }
  String getCode(){
    return code;
  }
  String getName(){
    return Name;
  }
  int getVotes(word pref_num){
    if(pref_num >= 0 && pref_num < num_prefs){ 
      return *(votes+pref_num);
    }
    else
      return -1;  
  }   
}; 
 
class Ballot {
  private:
  String ballot_name;
  Candidate* candidates;
  word num_candidates;
  word num_pref;
  word* pref_weight;
  

  public:
  Ballot(){
    Candidate cand = Candidate();
    candidates = &cand;
    num_candidates=1;
    num_pref=1;
    ballot_name="Prezzzzz";
    *pref_weight= 1;
  }

  Ballot(word NP,String b_name, word NC, word* PW , Candidate* candt){
    ballot_name=b_name;
    num_pref=  NP;
    if (num_pref == 1){
      *(pref_weight)=1;
    }
    else{
      pref_weight= PW;  
    }
    num_candidates= NC;
    candidates= candt; 
  }

  String getBallotName(){
    return ballot_name;
  }
    
  Candidate getCand(String A){
    for (int i=0;i<num_candidates;i++){
      Candidate y = *(candidates +i);
      if (y.getCode()==A){
        return y;
      }
    }
    return Candidate("-1","Invalid");
  }
  
  int getPref(){
    return num_pref;
  }
  word* getWeight(){
    return *pref_weight;
  }
  
  int getNum_Cand(){
    return num_candidates;
  }

  void poll(){
    // Vote for president
    lcd.print(ballot_name);
    delay(500);
    lcd.clear();
    char key;
    char Vote[num_pref];
    String Name[num_pref];
    int count=0;
    int cancel=0;
    while(count<num_pref){
      initial_prompt();
      lcd.setCursor(0,1);
      String tempdisp = String("Preference") + String(" ") + String(count+1) ;
      lcd.print(tempdisp);
      while( key == NO_KEY ){
        key = customKeypad.getKey();
      }
      if (key){
        if(key=="*"){
          cancel=1;
          lcd.clear();
          lcd.print("Cancelled");
          delay(1000);
          lcd.clear();      
          break;         
        }
        Candidate y = this->getCand(String(key));
        if (y.getName()=="Invalid"){
          invalid_prompt();
        }
        else{   
          lcd.setCursor(0,2);
          String tempname = String(key) + String(" ") + String(y.getName()) ;
          lcd.print(tempname);
          delay(500);
          lcd.clear();
          Vote[count]=key;
          Name[count]=y.getName();
          count++;
        }
      }
    }
    if (cancel==0){
      lcd.clear();
      for (int i=0;i<num_pref;i++){
        lcd.print("You have chosen:");  
        lcd.setCursor(0,1);
        lcd.print('i+1');
        lcd.setCursor(2,1);
        lcd.print(Name[i]);
        delay(1000);
        lcd.clear();
      }
      lcd.print("confrim-#");
      lcd.setCursor(0,1);
      lcd.print("Cancel-*");
      while( key == NO_KEY ){
          key = customKeypad.getKey();
      }
      if (key){
        if (key=="#"){
          lcd.clear();
          lcd.print("Thankyou");
          delay(500);
          lcd.clear();
        }
        if (key=="*"){
          cancel=1;
          lcd.clear();
          lcd.print("Cancelled");
          delay(1000);
          lcd.clear(); 
        }
      }
    }
    
    if (cancel==0){
      for (int i=0;i<num_pref;i++){
        for (int p=0;p<num_candidates;p++){
          Candidate C= *(candidates+p);
          if (String(Vote[i])==C.getCode()){
            word A=*(pref_weight +i); // To be removed
            C.vote(i);
          }
        }
      }
    }
  }
};

class Election{
  private:
  Ballot* ballots;
  word num_ballots;

  public:
  Election(){
    Ballot B = Ballot();
    ballots = &B;
    num_ballots=1;
  }

  Election(Ballot* ballot1, word N_B){
    ballots = ballot1;
    num_ballots=N_B;
  }
    
  Ballot getBallot(String A ){
    for (int i=0;i<num_ballots;i++){
      if((ballots+i)->getBallotName()==A){
        return *(ballots+i);
      }
    }
  }
  void conduct(){
    for (int i=0; i<num_ballots;i++){
      (ballots+i)->poll();
    }
  }
};

void setup() {
  lcd.begin(16,4);
  // put your setup code here, to run once:
  word num_pref=2;
  Candidate obj1 = Candidate("A","Priyanka",num_pref);
  Candidate obj2 = Candidate("B","Anuj",num_pref);
  Candidate list[2] = {obj1,obj2};
  int prefs[2] = {2,1};
  Ballot ballot1 = Ballot(2,"President",2,prefs,list);
  ballot1.poll();

  Serial.begin(9600);  
  Serial.println(obj1.getVotes(0));
  Serial.println(obj1.getVotes(1));
  Serial.println(obj1.getVotes(2));

}

void loop() {
  // put your main code here, to run repeatedly:

}
