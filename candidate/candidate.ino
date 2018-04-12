class candidate_class
{
  private:
    char code;
    String Name;
    word* votes;
    word num_prefs;
  public:
    candidate()
    { 
      code=0;
      Name=" ";
      *votes = 0;
    }
    candidate( char candCode, String candName)
    {
      code = candCode;
      Name = candName;
      num_prefs = 0;
      *votes = 0;
    }
    candidate(char candCode, String candName, word num_pref)
    {
      code = candCode;
      Name = candName;
      num_prefs = num_pref;
      for(word i=0; i<num_prefs; i++)
      {
        *(votes+i*sizeof(word))= 0;
      }
    }
    void vote(word pref_num)
    {
      *(votes+pref_num) += 1;
      
    }
    char getCode()
    {
      return code;
    }
    String getName()
    {
      return Name;
    }
    int getVotes(word pref_num)
    {
      return *(votes+pref_num);
    }
    
    
};
candidate_class obj1;
void setup() {
  // put your setup code here, to run once
  word num_pref=2;
  word candCode=0;
  String candName="abc";
  obj1.candidate(candCode,candName,num_pref);
  obj1.vote(0);
  obj1.vote(1); 
  obj1.vote(2);
  obj1.vote(2);
  Serial.begin(9600);  
  Serial.print(obj1.getVotes(0));
}

void loop() {
  // put your main code here, to run repeatedly:

}
