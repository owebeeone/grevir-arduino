#define GREVIR_ARDUINO_HOST_MOCK
#include <GrevirArduino.h>

using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using App = ardo::Application<ardo::ArduinoParamModule<Led>>;

int main() {
  grevir::arduino::mock::reset();
  App::runSetup();
  if (grevir::arduino::mock::state().pin_mode[LED_BUILTIN] != OUTPUT) {
    return 1;
  }
  Led::set(true);
  if (!grevir::arduino::mock::state().pin_level[LED_BUILTIN]) {
    return 2;
  }
  return 0;
}
