#pragma once

#include <grevir/arduino/arduino_api.hpp>
#include <grevir/core/resource_claims.hpp>

namespace ardo {

/**
 * Arduino HardwareSerial wrapper. Port 0 is the default USB/UART Serial.
 */
template <unsigned PortN = 0>
class SerialIO {
public:
  using Claims = ResourceClaim<SerialResource<PortN>>;

  static void runSetup() {}
  static void runLoop() {}

  static void begin(unsigned long baud) {
    serial().begin(baud);
  }

  static void print(const char* text) {
    serial().print(text);
  }

  static void println(const char* text) {
    serial().println(text);
  }

  static int available() {
    return serial().available();
  }

  static int read() {
    return serial().read();
  }

private:
  static auto& serial() {
    static_assert(PortN == 0, "Only Serial port 0 is wired in this adapter");
    return Serial;
  }
};

} // namespace ardo
