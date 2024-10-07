#define BLYNK_TEMPLATE_ID "TMPL35O0OSbhY"
#define BLYNK_TEMPLATE_NAME "Trial"
#define BLYNK_AUTH_TOKEN "lO3rUmq1tpVKZ5Eu7w2icb6g-2rnys5N"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char* ssid = "ICJ MOTO";
char* pass = "2506keta";

int variable = 10;
int set;
int unset;
int counter;

void setup() {
  Serial.begin(115200);
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

BLYNK_WRITE(V0) {
  set = param.asInt();
}
BLYNK_WRITE(V1) {
  unset = param.asInt();
}
BLYNK_WRITE(V2) {
  variable = param.asInt();
}

void loop(){
  Blynk.run();
  Serial.println(variable);
  if (set==1) {
    variable = 0;
    Serial.println(variable);
    Blynk.virtualWrite(V2, variable);
  }
  if (unset == 1) {
    variable = 10;
    Serial.println(variable);
    Blynk.virtualWrite(V2, variable);
  }
}
