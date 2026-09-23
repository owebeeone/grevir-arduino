#include <GrevirArduinoAVR.h>

using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using Seq = ardo::Sequence<unsigned long, 500UL, 500UL>;
using Blinker = ardo::CyclicTimeSequencePoller<Seq, ardo::ArduinoMillisClock>;

class BlinkModule : public ardo::ModuleBase<ardo::Parameters<Led>> {
public:
  static void runSetup() {
    Led::runSetup();
    poller.init();
  }

  static void runLoop() {
    if (poller.poll()) {
      on = !on;
      Led::set(on);
    }
  }

  inline static Blinker poller{};
  inline static bool on = false;
};

using App = ardo::ArduinoAvrApplication<BlinkModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
