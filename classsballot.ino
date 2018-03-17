

void initial_prompt()
{   lcd.clear();
    lcd.print("Cast Vote:");
    lcd.setCursor(0, 3);
    lcd.print("*-cancel");
    lcd.setCursor(0, 2); }
void invalid_prompt()
{   lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.print("Invalid Choice");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("               ");
    lcd.setCursor(0,1);
    lcd.print("Choose Again");
    delay(500);
     } 
class Ballot

{ private:
    String ballot_name;
    Candidate* candidates;
    word num_candidates;
    word num_pref;
    word* pref_weight;
    word prefDefault[num_pref];

  public:
  Ballot()
  { Candidate cand = Candidates();
    candidates = &cand;
    num_candidates=1;
    num_pref=1;
    ballot_name="Prezzzzz";
    prefDefault=1;
    pref_weight= &prefDefault;}

  Ballot(word NP,String name1, word NC, word* PW , Candidate* candt)
  {ballot_name=name1;
  num_pref=  NP;
  num_candidates= NC;
  pref_weight= PW;
  candidates= candt; }

  String getBallotName()
    {
      return ballot_name;
      }
    
    
  Candidate getCand(String A)
    {for (int i=0;i<num_candidates;i++)
    {
       y*(candidates +i);
       if (y.getCode()==A)
            {
              return y;}
            }
     p=Candidate(/0,"Invalid");
     return p;}

 
   int getPref()
    {
      return num_pref;
     }
    
    word int* getWeight()
    {
      return *pref_weight
    }
    
    int getNum_Cand()
    {
      return num_candidates;
    }

  void Poll()
  // Vote for president
  {
  lcd.print(ballot_name);
  delay(500);
  lcd.clear();
  char Vote[num_pref];
  String Name[num_pref];
  int count=0;
  int cancel=0;
  while(count<num_pref)
    {initial_prompt();
    lcd.setCursor(0,1);
    String tempdisp = "Preference"+ " " + 'count+1' ;
    lcd.print(tempdisp);
    while( key == NO_KEY )
    {
        key = customKeypad.getKey();
    }
    if (key)
    {   if(key=="*")
        {   cancel=1;
            lcd.clear();
            lcd.print("Cancelled")
            delay(1000);
            lcd.clear()      
            break;         
        }
        Candidate y= *this.getCand(key);
        if (y.getName()=="Invalid")
        {   invalid_prompt();
        }
        else    
        {lcd.setCursor(0,2);
        String tempname=key+" "+y.getName ;
        lcd.print(tempname);
        delay(500);
        lcd.clear();
        Vote[count]=key;
        Name[count]=y.getName;
        count++;
        }
    }
    }
  if (cancel==0)
  {lcd.clear();
  for (int i=0;i<num_pref;i++)
     { lcd.print("You have chosen:");  
      lcd.setCursor(0,1);
      lcd.print('i+1');
      lcd.setCursor(2,1);
      lcd.print(Name(i));
      delay(1000);
      lcd.clear();
     }
   lcd.print("confrim-#");
   lcd.setCursor(0,1);
   lcd.print("Cancel-*");
   while( key == NO_KEY )
    {
        key = customKeypad.getKey();
    }
    if (key){
      if (key=="#")
      {   lcd.clear();
          lcd.print("Thankyou");
          delay(500);
          lcd.clear();
      }
      if (key=="*")
      {     cancel=1;
            lcd.clear();
            lcd.print("Cancelled")
            delay(1000);
            lcd.clear(); }
    }
  }
  
  if (cancel==0)
  {for (int i=0;i<num_pref;i++)
  {
    for (int p=0;p<num_candidates;p++)
   { Candidate C= *(candidate+p);
    if (vote[i]==C.getCode())
      { word A=*(prefweight +i);
        C.Vote(i,A);
      }
    }
  }
  }
  }

}

class Election
{ private:
 Ballot* ballots;
 word num_ballots;

 public:
 
 Election()
 {  Ballot B = Ballot();
    ballots = &B;
    num_ballots=1;
 }
 
 Election(Ballot* ballot1, word N_B)
 {  ballots= &ballot1;
    num_ballots=N_B;}
    
 Ballot getBallot(String A )
 { Ballot y=*(ballots);
 for (int i=0;i<num_ballots;i++)
 { if(y.getBallotName()==A;
    { return y;}
   y++;}

 }

 void conduct()
 {Ballot tempballot= *(ballots);
 for (int i=0; i<num_ballots;i++)
 {tempballot.Poll();
  tempballot++;
 }
 }
 
    





void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
