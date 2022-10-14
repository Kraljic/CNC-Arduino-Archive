#ifndef serial_h
#define serial_h

#include "print.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifndef COMMAND_START
  #define COMMAND_START '!'
#endif

namespace cnc {
  
  void SerialInit();
  void SerialReadLine();
  void SerialReadNextCommand();
  void HandleCommand();

  void DecodeMoveToCommand();
  void DecodeLineCommand();
  void DecodeLinesCommand();
  void DecodeRectangleCommand();
  void DecodeEllipseCommand();
}

#endif
