#pragma once

#include <grevir/arduino/arduino_api.hpp>
#include <grevir/peripherals/gpio/modes.hpp>
#include <grevir/time/time.hpp>

namespace ardo {

/**
 * Arduino GPIO and millis backend. Pin adapters take this type first:
 * OutputPin<CoreIF, LED_BUILTIN>.
 */
class CoreIF {
public:
  static void pinMode(unsigned pin, gpio::OutputPinMode mode) {
    if (mode == gpio::OutputPinMode::Output) {
      ::pinMode(pin, OUTPUT);
      return;
    }
    ::pinMode(pin, INPUT);
  }

  static void pinMode(unsigned pin, gpio::InputPinMode mode) {
    if (mode == gpio::InputPinMode::PullUp) {
      ::pinMode(pin, INPUT_PULLUP);
      return;
    }
    ::pinMode(pin, INPUT);
  }

  static void digitalWrite(unsigned pin, bool level) {
    ::digitalWrite(pin, level ? HIGH : LOW);
  }

  static bool digitalRead(unsigned pin) {
    return ::digitalRead(pin) != LOW;
  }

  static unsigned long millis() {
    return ::millis();
  }

  static unsigned long micros() {
    return ::micros();
  }
};

struct ArduinoMillisClock {
  using TimeType = setl::Time<unsigned long, setl::TimeUnit::MILLIS>;

  static TimeType now() {
    return TimeType(CoreIF::millis());
  }
};

} // namespace ardo
