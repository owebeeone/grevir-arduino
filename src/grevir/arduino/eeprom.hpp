#pragma once

#include <grevir/arduino/arduino_api.hpp>
#include <cstdint>

#ifndef GREVIR_ARDUINO_HOST_MOCK
#include <EEPROM.h>
#endif

namespace ardo {

/**
 * Optional EEPROM adapter. Not included from GrevirArduino.h.
 */
class ArduinoEeprom {
public:
  static std::uint8_t read(int address) {
    return EEPROM.read(address);
  }

  static void write(int address, std::uint8_t value) {
    EEPROM.write(address, value);
  }
};

} // namespace ardo
