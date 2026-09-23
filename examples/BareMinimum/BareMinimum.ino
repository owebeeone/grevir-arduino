#include <GrevirArduinoAVR.h>

using App = ardo::ArduinoAvrApplication<>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
