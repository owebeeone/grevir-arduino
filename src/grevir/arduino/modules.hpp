#pragma once

#include <grevir/core/module.hpp>

namespace ardo {

/**
 * One Core module whose parameters are the given claim-bearing types
 * (pins, SerialIO, PWM).
 */
template <typename... Params>
using ArduinoParamModule = ModuleBase<Parameters<Params...>>;

} // namespace ardo
