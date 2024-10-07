int pir1 = 12;
int pir2 = 14;
int pir3 = 27;
int pinStateCurrent1   = LOW;  // current state of pin
int pinStatePrevious1  = LOW;
int pinStateCurrent2   = LOW;  // current state of pin
int pinStatePrevious2  = LOW;
int pinStateCurrent3   = LOW;  // current state of pin
int pinStatePrevious3  = LOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinStatePrevious1 = pinStateCurrent1; // store old state
  pinStateCurrent1 = digitalRead(pir1);   // read new state

  if (pinStatePrevious1 == LOW && pinStateCurrent1 == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("ON! pir1");
    // TODO: turn on alarm, light or activate a device ... here
  }
  else
  if (pinStatePrevious1 == HIGH && pinStateCurrent1 == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("OFF! pir1");
  }

  pinStatePrevious2 = pinStateCurrent2; // store old state
  pinStateCurrent2 = digitalRead(pir2);   // read new state

  if (pinStatePrevious2 == LOW && pinStateCurrent2 == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("ON! pir2");
    // TODO: turn on alarm, light or activate a device ... here
  }
  else
  if (pinStatePrevious2 == HIGH && pinStateCurrent2 == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("OFF! pir2");
  }

  pinStatePrevious3 = pinStateCurrent3; // store old state
  pinStateCurrent3 = digitalRead(pir3);   // read new state

  if (pinStatePrevious3 == LOW && pinStateCurrent3 == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("ON! pir3");
    // TODO: turn on alarm, light or activate a device ... here
  }
  else
  if (pinStatePrevious3 == HIGH && pinStateCurrent3 == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("OFF! pir3");
}
}
