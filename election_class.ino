
class Election_class
{
  private:
     ballot* ballots;
     word num_ballot;
  public:
      election()
     {
        num_ballot=0;
        ballots=0;
     }
     election(word giv_num_Ballot,ballot* giv_ballots)
     {
        num_ballot=giv_num_Ballot;
        ballots=giv_ballot;
     }
     word getBallot()
     {
        return(num_ballot);
     }
     conduct()
     {
        while (digitalRead(enable_pin)!=HIGH)
        {
            lcd.clear();
            lcd.print ("Wait for enable");
            delay(500);
        }
        lcd.clear();
        lcd.print("Enabled");
        delay(500);
        lcd.clear();
        for(i=0;i<num_ballot;i++)
        {
          *(ballot+i).poll();
        }
      
}




void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
