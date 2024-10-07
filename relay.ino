int pir1 = 14;
int relay = 26;
int pirState;
int relayState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pir1, INPUT);
  pinMode(relay, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pirState = digitalRead(pir1);
  
  if (pirState == HIGH) {
    relayState = LOW;
  } else {
    relayState = HIGH;
  }
  
  digitalWrite(relay, relayState);  // Update relay state
  
  // Optionally, you can print the pirState and relayState values
  Serial.print("PIR State: ");
  Serial.println(pirState);
  Serial.print("Relay State: ");
  Serial.println(relayState);
  
  delay(100);  // Add a small delay to avoid rapid toggling
}
