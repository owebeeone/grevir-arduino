#pragma once

#include <grevir/arduino/arduino_api.hpp>
#include <grevir/core/resource_claims.hpp>

namespace ardo {

/**
 * analogWrite wrapper. Timer claims are added by the AVR adapter so this
 * shared type stays portable.
 */
template <unsigned PIN>
class ArduinoPwm {
public:
  using Claims = ResourceClaim<GPIOResource<PIN>>;

  static void runSetup() {}
  static void runLoop() {}

  static void setPwm(int value) {
    analogWrite(PIN, value);
  }
};

} // namespace ardo
