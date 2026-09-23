#include <GrevirArduinoAVR.h>

struct ExclusiveTimer0 {
  using Claims = ardo::ResourceClaim<ardo::HardwareTimer<0>>;
  static void runSetup() {}
  static void runLoop() {}
};

using App = ardo::ArduinoAvrApplication<ardo::ArduinoParamModule<ExclusiveTimer0>>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
