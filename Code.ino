int out=12;
int door=13;
int in=14;
int bulb=26;
bool entryTrigger=false,entryTrigger2=false;
bool exitTrigger=false,exitTrigger2=false;
int counter=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  pinMode(14,INPUT);
  pinMode(26,OUTPUT);
  Serial.begin(115200);
  Serial.println("Intialiasing...");
  delay(30000);
  Serial.println("Initialised");
}

void loop() {
  // put your main code here, to run repeatedly:
  int outStat=digitalRead(out);
  int doorStat=digitalRead(door);
  int inStat=digitalRead(in);

  if(outStat==1 && doorStat==0 && inStat==0)
  {
    entryTrigger=true;
    exitTrigger=false;
  }
  if(outStat==0 && doorStat==0 && inStat==1)
  {
    exitTrigger=true;
    entryTrigger=false;
  }
  if(entryTrigger && doorStat==1)
  {
    entryTrigger2=true;
  }
  if(exitTrigger && doorStat==1)
  {
    exitTrigger2=true;
  }
  if(entryTrigger2 && inStat==1){
  	entryTrigger=false;
    entryTrigger2=false;
    counter++;
    Serial.println("Person Entered");
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  if(exitTrigger2 && outStat==1){
    exitTrigger=false;
    exitTrigger2=false;
    if(counter>0)
    counter--;
    Serial.println("Person Exits");
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  if (counter>0 || inStat==1) digitalWrite(bulb,HIGH);
  else if (counter<=0) digitalWrite(bulb,LOW);
  delay(20);
}