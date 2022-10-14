#include "load.h"

namespace cnc {  
  void Init() {

    pinMode(INFO_LED, OUTPUT);
    
    pinMode(X_STEP, OUTPUT);
    pinMode(Y_STEP, OUTPUT);
    pinMode(X_DIR, OUTPUT);
    pinMode(Y_DIR, OUTPUT);
    pinMode(Z_SERVO, OUTPUT);
  
    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(MS3, OUTPUT);  
    pinMode(SLEEP, OUTPUT);
  
    pinMode(X_SENSOR, INPUT_PULLUP);
    pinMode(Y_SENSOR, INPUT_PULLUP);  

    // ------------------------------
  
    digitalWrite(INFO_LED, LOW);
    
    digitalWrite(X_STEP, LOW);
    digitalWrite(Y_STEP, LOW);
    digitalWrite(X_DIR, LOW);
    digitalWrite(Y_DIR, LOW);
    digitalWrite(Z_SERVO, LOW);
    
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(MS3, LOW);    
    digitalWrite(SLEEP, LOW);
  
    // ------------------------------

    StepperInit();
    //MoveToHome();    
    SerialInit();
  }

}

