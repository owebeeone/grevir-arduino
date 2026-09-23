#pragma once

#ifdef GREVIR_ARDUINO_HOST_MOCK
#include <grevir/arduino/mock.hpp>
#else
#if !defined(ARDUINO)
#error "Include Grevir Arduino from an Arduino sketch, or define GREVIR_ARDUINO_HOST_MOCK for host tests."
#endif
#include <Arduino.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef abs
#undef abs
#endif
#ifdef round
#undef round
#endif
#ifdef constrain
#undef constrain
#endif
#ifdef sq
#undef sq
#endif
#endif

