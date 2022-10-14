#ifndef load_h
#define load_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "serial.h"
#include "config.h"
#include "stepper.h"
#include "print.h"
#include <Servo.h>

namespace cnc {
	void Init();
}

#endif
