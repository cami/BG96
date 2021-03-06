#pragma once

#include <Arduino.h>

// #undef max /* FIXME workaround: https://stackoverflow.com/questions/41093090/esp8266-error-macro-min-passed-3-arguments-but-takes-just-2 */
// #undef min /* FIXME workaround: https://stackoverflow.com/questions/41093090/esp8266-error-macro-min-passed-3-arguments-but-takes-just-2 */

#ifdef ARDUINO_ARCH_NRF52
#include <Wire.h>
#endif // ARDUINO_ARCH_NRF52

// CFG_DEBUG == 0 => (Release)
// CFG_DEBUG == 1 => (Error Message)
// CFG_DEBUG == 2 => (Full Debug)
// CFG_DEBUG == 3 => (Segger SystemView)

#if CFG_DEBUG == 0

#elif CFG_DEBUG == 1

#elif CFG_DEBUG >= 2
  #define CELLULAR_DEBUG
#endif //CFG_DEBUG
