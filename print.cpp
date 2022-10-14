#include "print.h"

namespace cnc {
  void StartProgram() {
    MoveToHome();
    WakeUp();
  }
  void EndProgram() {
    MoveZ(0);
    Sleep();
  }
  void MoveTool(double x, double y) {
    MoveZ(0);
    MoveTo(x, y);
  }
  void PrintLine(double x1, double y1, double x2, double y2) {  
    MoveZ(0);
    MoveTo(x1, y1);
    MoveZ(1);
    MoveTo(x2, y2);
    MoveZ(0);
  }
  void PrintLines(double x1, double y1) {
    MoveZ(1);
    MoveTo(x1, y1, false);
  }
  void PrintRectangle(double x, double y, double width, double height) {  
    MoveZ(0);
    MoveTo(x, y);
    MoveZ(1);
    MoveTo(x + width, y);
    MoveTo(x + width, y + height);
    MoveTo(x, y + height);
    MoveTo(x, y);
    MoveZ(0);
  }
  void PrintEllipse(double x, double y, double width, double height) {
    double x1, y1;
    x += (width / 2);
    y += (height / 2);
    width /= 2;
    height /= 2;
    
    MoveZ(0);
    
    double n = 2.0d * PI / 75.0d;
    for (double i = 0; i <= 2.0d*PI + 2*n; i+=n) {
      x1 = width * sin(i) + x;
      y1 = height * cos(i) + y;
      MoveTo(x1, y1, false);
      MoveZ(1);
    }
  }
}

