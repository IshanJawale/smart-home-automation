#define BLYNK_TEMPLATE_ID "TMPL3asX99Ton"
#define BLYNK_TEMPLATE_NAME "IoT Enabled Smart Home Automation"
#define BLYNK_AUTH_TOKEN "y7rxTj4-NS020FdrselNnHc5oG_CJw5q"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char* ssid = "ICJ MOTO";
char* pass = "2506keta";

int out = 12;
int door = 13;
int in = 14;
int bulb = 26;
bool entryTrigger = false, entryTrigger2 = false;
bool exitTrigger = false, exitTrigger2 = false;
int counter = 0;
int set;

void setup() {
  pinMode(out, INPUT);
  pinMode(door, INPUT);
  pinMode(in, INPUT);
  pinMode(bulb, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Initializing...");
  delay(3000);
  Serial.println("Initialized");
  
  WiFi.mode(WIFI_STA);//Station Mode
  WiFi.begin(ssid, pass);
  Serial.println("\nWi-Fi Connecting");
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }
  Serial.println("\nSuccessfully Connected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_CONNECTED() {
   Blynk.syncAll();
}

BLYNK_WRITE(V5) {
  set = param.asInt();
}

void loop() {
  Blynk.run();
  
  int outStat = digitalRead(out);
  int doorStat = digitalRead(door);
  int inStat = digitalRead(in);

  if (outStat == HIGH && doorStat == LOW && inStat == LOW) {
    entryTrigger = true;
    exitTrigger = false;
  }
  if (outStat == LOW && doorStat == LOW && inStat == HIGH) {
    exitTrigger = true;
    entryTrigger = false;
  }
  
  if (entryTrigger && doorStat == HIGH) {
    entryTrigger2 = true;
  }
  if (exitTrigger && doorStat == HIGH) {
    exitTrigger2 = true;
  }
  
  if (entryTrigger2 && inStat == HIGH) {
    entryTrigger = false;
    entryTrigger2 = false;
    counter++;
    Serial.println("Person Entered");
    Serial.print("Counter: ");
    Serial.println(counter);
    Blynk.virtualWrite(V4, counter);  // Update counter value on Blynk app
  }
  if (exitTrigger2 && outStat == HIGH) {
    exitTrigger = false;
    exitTrigger2 = false;
    if (counter > 0)
      counter--;
    Serial.println("Person Exited");
    Serial.print("Counter: ");
    Serial.println(counter);
    Blynk.virtualWrite(V4, counter);  // Update counter value on Blynk app
  }
  
  if(set == 1) {
    counter = 0;
    Serial.println("Counter reseted to zero");
    Blynk.virtualWrite(V4, counter);
  }
  if (counter > 0 || inStat == HIGH) {
    digitalWrite(bulb, HIGH);
  } else {
    digitalWrite(bulb, LOW);
  }
  
  delay(20);
}
