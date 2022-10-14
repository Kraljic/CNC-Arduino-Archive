#include "serial.h"

namespace cnc {    
  String SERIAL_LINE;
  String tmpStr;
    
  void SerialInit() {
    Serial.begin(BAUD_RATE);
  }
  
  void SerialReadLine() {
    uint8_t i = 0;
    char c;
    SERIAL_LINE = "";
    while (true) {
      if (Serial.available()) {
          c= Serial.read();
          if (c == '\n') 
            break;
          SERIAL_LINE += c;
          i++;
      }
    }
  }

  void SerialReadNextCommand() {
    SerialReadLine();
    if (sizeof(SERIAL_LINE) > 1 && SERIAL_LINE[0] == COMMAND_START) {
      return;
    }
    SerialReadNextCommand();
  }

  void HandleCommand() {

    switch (SERIAL_LINE[1]) {
      case '0':
        EndProgram();
        Serial.println("done");
        break;
      case '1':
        StartProgram();
        Serial.println("done");
        break;
      case '2':
        MoveToHome();
        Serial.println("done");
        break;
      case '3':
        DecodeMoveToCommand();
        Serial.println("done");
        break;
      case '4':
        DecodeLineCommand();
        Serial.println("done");
        break;
      case '5':
        Serial.println("done");
        DecodeLinesCommand();
        break;
      case '6':
        DecodeRectangleCommand();
        Serial.println("done");
        break;
      case '7':
        DecodeEllipseCommand();
        Serial.println("done");
        break;
      case '8':
        Serial.println("ready");
        break;
    }
  }

  void DecodeMoveToCommand() {
    byte cordNumber = 2;
    double cord[cordNumber];
    int b = 0, i = 3;
    char c;
    tmpStr = "";
    while (b < cordNumber) {
      c = SERIAL_LINE[i++];
      if (c == ';') {
        cord[b] = tmpStr.toDouble();
        tmpStr = "";
        b++;
        continue;
      }
      tmpStr += c;
    }
    MoveTool(cord[0], cord[1]);
  }
  void DecodeLineCommand() {
    byte cordNumber = 4;
    double cord[cordNumber];
    int b = 0, i = 3;
    char c;
    tmpStr = "";
    while (b < cordNumber) {
      c = SERIAL_LINE[i++];
      if (c == ';') {
        cord[b] = tmpStr.toDouble();
        tmpStr = "";
        b++;
        continue;
      }
      tmpStr += c;
    }
    PrintLine(cord[0], cord[1], cord[2], cord[3]);
  }
  void DecodeLinesCommand() {
    byte cordNumber = 2;
    double cord[cordNumber];
    int b = 0, i = 3;
    char c;
    tmpStr = "";
    while (b < cordNumber) {
      c = SERIAL_LINE[i++];
      if (c == ';') {
        cord[b] = tmpStr.toDouble();
        tmpStr = "";
        b++;
        continue;
      }
      tmpStr += c;
    }
    PrintLines(cord[0], cord[1]);
    
  }
  void DecodeRectangleCommand() {
    byte cordNumber = 4;
    double cord[cordNumber];
    int b = 0, i = 3;
    char c;
    tmpStr = "";
    while (b < cordNumber) {
      c = SERIAL_LINE[i++];
      if (c == ';') {
        cord[b] = tmpStr.toDouble();
        tmpStr = "";
        b++;
        continue;
      }
      tmpStr += c;
    }
    PrintRectangle(cord[0], cord[1], cord[2], cord[3]);    
  }
  void DecodeEllipseCommand() {
    byte cordNumber = 4;
    double cord[cordNumber];
    int b = 0, i = 3;
    char c;
    tmpStr = "";
    while (b < cordNumber) {
      c = SERIAL_LINE[i++];
      if (c == ';') {
        cord[b] = tmpStr.toDouble();
        tmpStr = "";
        b++;
        continue;
      }
      tmpStr += c;
    }
    PrintEllipse(cord[0], cord[1], cord[2], cord[3]);      
  }
}

