const int PIR1_PIN = 18;
const int PIR2_PIN = 19;

const bool SERIAL_PRINT = true;

int visitors = 0;
int lastRIPdetected = 0;
bool b_PIR1_active = false;
bool b_PIR2_active = false;

void setup()  {
  

  pinMode(PIR1_PIN, INPUT);
  pinMode(PIR2_PIN, INPUT);
  
  
  Serial.begin(115200); 
  Serial.println("Visitor counter Welcome");
}




// -------- Increase/Decrease visitors ---------
void UpdateVisitorsCounter(int x){ 
int duration=100;
  
  visitors = visitors + x;
  
  lastRIPdetected = 0;  // reset detected PIR
  
}



void loop() {    
  
  // ----------- check PIR1 ----------------
  if (digitalRead(PIR1_PIN) == HIGH) {
    
    if ( !b_PIR1_active ) {
      b_PIR1_active = true;
      
      if (lastRIPdetected == 0 && !b_PIR2_active) {  // new start
        lastRIPdetected = 1;    
 
        Serial.println("In PIR1 Visit started");
        Serial.println(visitors);

      } else if (lastRIPdetected == 2) { // if we were in PIR2 before
        UpdateVisitorsCounter(-1);  
      
        Serial.println("Visitor exited Visitors:");
        Serial.println(visitors);
      } 
    }
  }else 
    b_PIR1_active = false ;  // reenable PIR1
  
  
  // ----------- check PIR2 ----------------  
  if (digitalRead(PIR2_PIN) == HIGH ) {
    
    if ( !b_PIR2_active ) {
      b_PIR2_active = true;
      
      if (lastRIPdetected == 0 && !b_PIR1_active) { // new start
        if (visitors > 0) {
          lastRIPdetected = 2;   

          Serial.println("In PIR2 Exit started");
        } else 
          Serial.println("No more visitors to exit");
                
      } else if (lastRIPdetected == 1) {  // if we were in PIR1 before
        UpdateVisitorsCounter(1);      

        Serial.println("Visitor entered Visitors: ");
        Serial.println(visitors);
      }
    }
  } else 
    b_PIR2_active = false; // reenable PIR2
  
}