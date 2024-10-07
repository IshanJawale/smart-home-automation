int pin_o = 13; // entrance Sensor
int pin_i = 12;
int pin_r = 14; // Exit Sensor
int bulb = 26;

int counter = 0;
bool entryFlag = false; // flag to track Entrance and update counter once per motion
bool exitFlag = false; // flag to track Exit and update counter once per motion

void setup()
{
  pinMode(pin_o, INPUT);
  pinMode(pin_i, INPUT);
  pinMode(pin_r, INPUT);
  pinMode(bulb, OUTPUT);
  Serial.begin(115200);
}

void enter()
{
  if (digitalRead(pin_i))
  {
    delay(200);
    if (!entryFlag)
    { // if flag will make sure update counter only once
      counter++;
      entryFlag = true; // make it true so for the same motion counter will not get updated twice
      Serial.print("Person Entered: ");
      Serial.println(counter);
    }
  }
  else
  {
    // reset the flag to false again if no entrance is detected so on the next motion counter can increment
    entryFlag = false;
  }
}

void exit()
{
  if (digitalRead(pin_o))
  {
    delay(200);
    if (!exitFlag && counter > 0)
    { // if flag will make sure update counter only once per motion
      counter--;
      exitFlag = true; // make it true so for the same motion counter will not get updated twice
      Serial.print("Person Remaining: ");
      Serial.println(counter);
    }
    else
    {
      exitFlag = false;
    }
  }
}

void loop()
{
  if (digitalRead(pin_o))
  {
    enter();
  }
  else if (digitalRead(pin_r))
  {
    exit();
  }

  if (counter > 0)
  {
    digitalWrite(bulb, HIGH);
  }
  else
  {
    digitalWrite(bulb, LOW);
  }
  
}
