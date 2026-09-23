#include <GrevirArduino.h>

#if CASE_ID == 0
using App = ardo::Application<ardo::ArduinoParamModule<
  ardo::arduino::OutputPin<13>,
  ardo::arduino::InputPin<2>>>;
#elif CASE_ID == 1
using App = ardo::Application<ardo::ArduinoParamModule<
  ardo::arduino::OutputPin<13>,
  ardo::SerialIO<0>>>;
#elif CASE_ID == 2
struct FirstLed : ardo::ModuleBase<ardo::Parameters<ardo::arduino::OutputPin<13>>> {};
struct SecondLed : ardo::ModuleBase<ardo::Parameters<ardo::arduino::OutputPin<13>>> {};
using App = ardo::Application<FirstLed, SecondLed>;
#elif CASE_ID == 3
struct FirstSerial : ardo::ModuleBase<ardo::Parameters<ardo::SerialIO<0>>> {};
struct SecondSerial : ardo::ModuleBase<ardo::Parameters<ardo::SerialIO<0>>> {};
using App = ardo::Application<FirstSerial, SecondSerial>;
#else
#error "unknown CASE_ID"
#endif

void instantiate() {
  App::runSetup();
  App::runLoop();
}
