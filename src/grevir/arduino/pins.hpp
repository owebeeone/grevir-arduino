#pragma once

#include <grevir/arduino/core.hpp>
#include <grevir/peripherals/gpio/input.hpp>
#include <grevir/peripherals/gpio/output.hpp>

namespace ardo::arduino {

template <
  unsigned P,
  gpio::OutputPinMode M = gpio::OutputPinMode::Output>
using OutputPin = ardo::OutputPin<CoreIF, P, M>;

template <
  unsigned P,
  gpio::InputPinMode M = gpio::InputPinMode::PullUp>
using InputPin = ardo::InputPin<CoreIF, P, M>;

} // namespace ardo::arduino
