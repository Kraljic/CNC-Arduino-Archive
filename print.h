#ifndef print_h
#define print_h

#include "stepper.h"

namespace cnc {
  void StartProgram();
  void EndProgram();
  
  void PrintLine(double x1, double y1, double x2, double y2);
  void PrintLines(double x, double y);
  void PrintEllipse(double x, double y, double width, double height);
  void PrintRectangle(double x, double y, double width, double height);  
  void MoveTool(double x, double y);  
}

#endif
