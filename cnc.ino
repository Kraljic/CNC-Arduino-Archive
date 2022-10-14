
#include "load.h"


void setup() {
  cnc::Init();
}

void loop() {
  cnc::SerialReadNextCommand();
  cnc::HandleCommand();
}

void drawHouse() {
  cnc::WakeUp();
  cnc::MoveZ(1);
  cnc::MoveFor(50, 0); 
  cnc::MoveFor(0, 50); 
  cnc::MoveFor(-50, 0); 
  cnc::MoveFor(25, 25); 
  cnc::MoveFor(25, -25); 
  cnc::MoveFor(-50, -50); 
  cnc::MoveFor(0, 50); 
  cnc::MoveFor(50, -50); 
  cnc::MoveZ(0);
  cnc::Sleep();  
}
