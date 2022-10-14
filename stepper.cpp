#include "stepper.h"

namespace cnc {
  bool sensorX = false;
  bool sensorY = false;
  
  double x_poss = 0.0;
  double y_poss = 0.0;
  bool z_poss = true;
  
  Servo zOS_Servo;  
  
  StepType stepType;
  double stepsPerMM;
  double delayPulse;
  double delayWait;
  
  void StepperInit() {
    SetStepType(Sixteenth);
    
    zOS_Servo.attach(Z_SERVO);

    cnc::WakeUp();
    cnc::MoveToHome();
    cnc::Sleep(); 
  }

  void ReadSensors() {
    sensorX = !digitalRead(X_SENSOR);
    sensorY = !digitalRead(Y_SENSOR);
  }

  void SelectDirection(double x, double y) {    
    // change if not 0
    if (x < 0) 
      digitalWrite(X_DIR, HIGH);
    else if (x != 0)
      digitalWrite(X_DIR, LOW);
      
    // change if not 0
    if (y < 0) 
      digitalWrite(Y_DIR, HIGH);
    else if (y != 0)
      digitalWrite(Y_DIR, LOW);
  }  
    
  void MoveToHome() {
    // Prebaci na full step i spremi trenutni step
    StepType stepTmp = stepType;
    SetStepType(Half); 

    WakeUp();
    // Postavi glavu na (0,0)    
    MoveZ(false);
    MoveX(-400.0);
    MoveY(-400.0);
    MoveX(HOME_OFFSET);
    MoveY(HOME_OFFSET);
    Sleep();

    // Vrati na prvobitni step
    SetStepType(stepTmp);
    x_poss = 0;
    y_poss = 0;
  }
  void MoveX(double val) {
    bool negativeX = (val < 0);
    SelectDirection(val, 0);
    
    val = abs(val * STEPS_PER_MM * (int)stepType);
  
    for (int i = 0; i < val; i++) {
      ReadSensors();
      if (sensorX && negativeX)
        break;
      digitalWrite(X_STEP, HIGH);
      delayMicroseconds(delayPulse);
      digitalWrite(X_STEP, LOW);
      delayMicroseconds(delayPulse); 
      delayMicroseconds(delayWait); 
    }
  }
  void MoveY(double val) {
    bool negativeY = (val < 0);
    SelectDirection(0, val);
    
    val = abs(val * STEPS_PER_MM * (int)stepType);    
      
    for (int i = 0; i < val; i++) {
      ReadSensors();
      if (sensorY && negativeY)
        break;
      digitalWrite(Y_STEP, HIGH);
      delayMicroseconds(delayPulse); 
      digitalWrite(Y_STEP, LOW);
      delayMicroseconds(delayPulse); 
      delayMicroseconds(delayWait); 
    }  
  }
  void MoveZ(bool down) {
    if (down && zOS_Servo.read() > 100) {
      zOS_Servo.write(95);         
      delay(250);
    }
    else if (down == 0) {
      zOS_Servo.write(130);      
      delay(250);
    }
  }
  void MoveTo(double x, double y, bool wait=true) {
    MoveFor(x - x_poss, y - y_poss, wait);
    ReadSensors();    
  }
  
  void MoveFor(double x, double y, bool wait=true) {
    x_poss += x;
    y_poss += y;
    
    bool negativeX = (x < 0);
    bool negativeY = (y < 0);
    SelectDirection(x, y);
  
    x = abs(x * stepsPerMM);
    y = abs(y * stepsPerMM);

    double maks = x > y ? x : y;
    double nX = 0.0d;
    double nY = 0.0d;
    double nX_Ration = maks / x;
    double nY_Ration = maks / y;

    nX = x == 0 ? maks : 0;
    nY = y == 0 ? maks : 0;
    
    long i = 0;
    while (true) {
      // Break if sensors are ENABLED and at least one IS ACTIVE
      if (negativeX || negativeY) {
        ReadSensors();
        if (sensorX || sensorY) {
          Serial.println("error!");
          EndProgram();
          break;
        }
      }
      
      if (nX >= maks && nY >= maks)
        break;
      
      if (nX < i && nX < maks) {
        digitalWrite(X_STEP, HIGH);
        nX += nX_Ration;
      }
      if (nY < i && nY < maks) {
        digitalWrite(Y_STEP, HIGH);
        nY += nY_Ration;
      }
      
      delayMicroseconds(delayPulse); 
      
      digitalWrite(X_STEP, LOW);
      digitalWrite(Y_STEP, LOW);
      
      delayMicroseconds(delayPulse); 
      delayMicroseconds(delayWait); 
      
      i++;
    }
    if (wait)
      delay(250);
  }

  void Sleep() {
    delay(250);
    digitalWrite(SLEEP, LOW);
  }
  void WakeUp() {
    digitalWrite(SLEEP, HIGH);
    delay(100);
  }
  
  void SetStepType(StepType type) {
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(MS3, LOW);
  
    stepType = type;
    switch (type) {
      case Full:
        stepsPerMM = STEPS_PER_MM;
        delayPulse = 500;
        delayWait = 2000;
        break;
      case Half: 
        digitalWrite(MS1, HIGH);
        stepsPerMM = STEPS_PER_MM * 2;
        delayPulse = 500;
        delayWait = 1000;
        break;
      case Quarter: 
        digitalWrite(MS2, HIGH);
        stepsPerMM = STEPS_PER_MM *  4;
        delayPulse = 500;
        delayWait = 500;
        break;
      case Eight:
        digitalWrite(MS1, HIGH);
        digitalWrite(MS2, HIGH);
        stepsPerMM = STEPS_PER_MM * 8;
        delayPulse = 200;
        delayWait = 200;
        break;
      case Sixteenth:
        digitalWrite(MS1, HIGH);
        digitalWrite(MS2, HIGH);
        digitalWrite(MS3, HIGH);
        stepsPerMM = STEPS_PER_MM * 16;
        delayPulse = 75;
        delayWait = 150;
        break;
    }
  }  
}

