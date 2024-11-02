#pragma once

#include "Definitions.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

class MicroMath {
public:
  static inline uint8_t DigitCount(int16_t n) {
    if (n == 0)
      return 1;
    int16_t absoluteN = abs(n);
    uint8_t digitCount = (uint8_t)log10f(absoluteN) + 1;
    return digitCount;
  }

  static inline int16_t GetLastDigit(int16_t n) {
    float divResDec = n / 10.0f;
    int16_t divResInt = (int16_t)divResDec;
    return static_cast<int16_t>((divResDec - divResInt) * 10);
  }

  static inline uint8_t Lerp(uint8_t from, uint8_t to, float t) {
    return static_cast<uint8_t>(from * (1.0 - t) + (to * t));
  }

  static inline uint32_t Lerp(uint32_t from, uint32_t to, float t) {
    return static_cast<uint32_t>(from * (1.0 - t) + (to * t));
  }

  static inline float Lerp(float from, float to, float t) {
    return (from * (1.0 - t) + (to * t));
  }
};
