#include <GrevirArduino.h>
#include <grevir/arduino/eeprom.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using Button = ardo::arduino::InputPin<2>;
using Seq = ardo::Sequence<unsigned long, 500UL, 500UL>;
using Blinker = ardo::CyclicTimeSequencePoller<Seq, ardo::ArduinoMillisClock>;

TEST_CASE("CoreIF translates Grevir pin modes to Arduino constants") {
  grevir::arduino::mock::reset();
  Led::runSetup();
  Button::runSetup();
  REQUIRE(grevir::arduino::mock::state().pin_mode[LED_BUILTIN] == OUTPUT);
  REQUIRE(grevir::arduino::mock::state().pin_mode[2] == INPUT_PULLUP);
}

TEST_CASE("OutputPin writes through CoreIF") {
  grevir::arduino::mock::reset();
  Led::runSetup();
  Led::set(true);
  REQUIRE(grevir::arduino::mock::state().pin_level[LED_BUILTIN]);
  Led::set(false);
  REQUIRE_FALSE(grevir::arduino::mock::state().pin_level[LED_BUILTIN]);
}

TEST_CASE("ArduinoMillisClock drives a blink sequence") {
  grevir::arduino::mock::reset();
  Blinker poller;
  poller.init();
  REQUIRE_FALSE(poller.poll());
  grevir::arduino::mock::state().millis_now = 500;
  REQUIRE_FALSE(poller.poll());
  grevir::arduino::mock::state().millis_now = 501;
  REQUIRE(poller.poll());
  REQUIRE(poller.state() == 1);
}

TEST_CASE("SerialIO appends to the mock UART buffer") {
  grevir::arduino::mock::reset();
  ardo::SerialIO<0>::print("hi");
  ardo::SerialIO<0>::println("there");
  REQUIRE(std::string(grevir::arduino::mock::state().serial_out) == "hithere\n");
}

TEST_CASE("ArduinoPwm records analogWrite") {
  grevir::arduino::mock::reset();
  ardo::ArduinoPwm<9>::setPwm(120);
  REQUIRE(grevir::arduino::mock::state().analog[9] == 120);
}

TEST_CASE("EEPROM adapter reads and writes the mock store") {
  grevir::arduino::mock::reset();
  ardo::ArduinoEeprom::write(10, 42);
  REQUIRE(ardo::ArduinoEeprom::read(10) == 42);
  REQUIRE(ardo::ArduinoEeprom::read(11) == 0);
}
