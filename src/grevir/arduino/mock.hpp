#pragma once

// Explicit host stand-in for Arduino.h. Never selected by an absent
// INPUT_PULLUP or similar accidental probe.

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif
#ifndef HIGH
#define HIGH 1
#endif
#ifndef LOW
#define LOW 0
#endif
#ifndef INPUT
#define INPUT 0
#endif
#ifndef OUTPUT
#define OUTPUT 1
#endif
#ifndef INPUT_PULLUP
#define INPUT_PULLUP 2
#endif

#include <cstdint>
#include <cstring>

namespace grevir::arduino::mock {

inline constexpr unsigned kPinCount = 32;
inline constexpr unsigned kEepromSize = 1024;

struct State {
  int pin_mode[kPinCount]{};
  bool pin_level[kPinCount]{};
  int analog[kPinCount]{};
  unsigned long millis_now = 0;
  unsigned long micros_now = 0;
  char serial_out[512]{};
  unsigned serial_out_len = 0;
  std::uint8_t eeprom[kEepromSize]{};
};

inline State& state() {
  static State instance{};
  return instance;
}

inline void reset() {
  state() = State{};
}

} // namespace grevir::arduino::mock

inline void pinMode(unsigned pin, int mode) {
  if (pin < grevir::arduino::mock::kPinCount) {
    grevir::arduino::mock::state().pin_mode[pin] = mode;
  }
}

inline void digitalWrite(unsigned pin, int level) {
  if (pin < grevir::arduino::mock::kPinCount) {
    grevir::arduino::mock::state().pin_level[pin] = level != 0;
  }
}

inline int digitalRead(unsigned pin) {
  if (pin < grevir::arduino::mock::kPinCount) {
    return grevir::arduino::mock::state().pin_level[pin] ? HIGH : LOW;
  }
  return LOW;
}

inline void analogWrite(unsigned pin, int value) {
  if (pin < grevir::arduino::mock::kPinCount) {
    grevir::arduino::mock::state().analog[pin] = value;
  }
}

inline unsigned long millis() {
  return grevir::arduino::mock::state().millis_now;
}

inline unsigned long micros() {
  return grevir::arduino::mock::state().micros_now;
}

class HardwareSerial {
public:
  void begin(unsigned long) {}

  void print(const char* text) {
    auto& serial = grevir::arduino::mock::state();
    if (text == nullptr) {
      return;
    }
    const unsigned remaining = sizeof(serial.serial_out) - 1 - serial.serial_out_len;
    const unsigned copied = static_cast<unsigned>(
      std::strlen(text) < remaining ? std::strlen(text) : remaining);
    std::memcpy(serial.serial_out + serial.serial_out_len, text, copied);
    serial.serial_out_len += copied;
    serial.serial_out[serial.serial_out_len] = '\0';
  }

  void println(const char* text) {
    print(text);
    print("\n");
  }

  void println() {
    print("\n");
  }

  int available() {
    return 0;
  }

  int read() {
    return -1;
  }
};

inline HardwareSerial Serial{};

class EEPROMClass {
public:
  std::uint8_t read(int address) const {
    if (address < 0 ||
        address >= static_cast<int>(grevir::arduino::mock::kEepromSize)) {
      return 0;
    }
    return grevir::arduino::mock::state().eeprom[static_cast<unsigned>(address)];
  }

  void write(int address, std::uint8_t value) {
    if (address < 0 ||
        address >= static_cast<int>(grevir::arduino::mock::kEepromSize)) {
      return;
    }
    grevir::arduino::mock::state().eeprom[static_cast<unsigned>(address)] = value;
  }
};

inline EEPROMClass EEPROM{};
