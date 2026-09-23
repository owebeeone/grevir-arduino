#include <GrevirArduino.h>
#include <grevir/arduino/eeprom.hpp>

namespace {
using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using Button = ardo::arduino::InputPin<2>;
using Serial0 = ardo::SerialIO<0>;
using Pwm9 = ardo::ArduinoPwm<9>;
using App = ardo::Application<ardo::ArduinoParamModule<Led, Button, Serial0, Pwm9>>;
}

void instantiate_arduino() {
  App::runSetup();
  App::runLoop();
  Led::set(true);
  (void)Button::get();
  Serial0::print("ok");
  Pwm9::setPwm(64);
  (void)ardo::ArduinoEeprom::read(0);
  ardo::ArduinoEeprom::write(0, 7);
  (void)ardo::ArduinoMillisClock::now();
}
