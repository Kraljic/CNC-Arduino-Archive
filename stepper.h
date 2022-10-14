#ifndef stepper_h
#define stepper_h

#include <Servo.h>
#include "print.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "config.h"

namespace cnc {  
  enum StepType {
    Full = 1,
    Half = 2,
    Quarter = 4,
    Eight = 8,
    Sixteenth = 16
  };
  
  void StepperInit();

  void SelectDirection(double x, double y);
  void ReadSensors();
  
  void MoveX(double);
  void MoveY(double);
  void MoveZ(bool);
  void MoveToHome();
  void MoveTo(double, double, bool=true);
  void MoveFor(double, double, bool=true);

  // Sleep
  void Sleep();
  void WakeUp();
  
  // Steps
  void SetStepType(StepType);
}

#endif
