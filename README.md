# Grevir Arduino

Arduino CoreIF, pin aliases, Serial and PWM adapters for Grevir. EEPROM is a
separate header and is not pulled in by `GrevirArduino.h`.

Host tests define `GREVIR_ARDUINO_HOST_MOCK`. That mock is never selected by an
absent Arduino constant. Production sketches include `Arduino.h` because
`ARDUINO` is defined.

```cpp
#include <GrevirArduino.h>

using Led = ardo::arduino::OutputPin<LED_BUILTIN>;
using App = ardo::Application<ardo::ArduinoParamModule<Led>>;
```

`OutputPin` and `InputPin` take `CoreIF` first. PWM timer claims live in
`grevir-arduino-avr`. Arduino CLI compile is validated on weftpi, not on the Mac.
