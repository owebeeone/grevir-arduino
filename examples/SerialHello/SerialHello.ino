#include <GrevirArduinoAVR.h>

using Serial0 = ardo::SerialIO<0>;

class HelloModule : public ardo::ModuleBase<ardo::Parameters<Serial0>> {
public:
  static void runSetup() {
    Serial0::begin(9600);
    Serial0::println("grevir");
  }
};

using App = ardo::ArduinoAvrApplication<HelloModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
