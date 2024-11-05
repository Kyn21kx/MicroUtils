#pragma once

#include <stdint.h>

#include "MicroMath.h"

enum MicroColorFormat : uint8_t {
  RGB,
  GRB
};

class MicroColor {

public:
  MicroColor() = default;

  MicroColor(uint8_t r, uint8_t g, uint8_t b);

  void SetRGBFloating(float r, float g, float b);

  void SetRGBInteger(uint8_t r, uint8_t g, uint8_t b);

  uint32_t ToUInt32(MicroColorFormat format) const;

  float GetRed() const;

  float GetGreen() const;

  float GetBlue() const;

  uint8_t GetRedInt() const;

  uint8_t GetGreenInt() const;

  uint8_t GetBlueInt() const;

  static inline MicroColor Lerp(const MicroColor &from, const MicroColor &to,
                                float t) {
    float r, g, b;
    r = MicroMath::Lerp(from.GetRed(), to.GetRed(), t);
    g = MicroMath::Lerp(from.GetGreen(), to.GetGreen(), t);
    b = MicroMath::Lerp(from.GetBlue(), to.GetBlue(), t);
    MicroColor result;
    result.SetRGBFloating(r, g, b);
    return result;
  }

  static float DistanceToSqr(const MicroColor &from, const MicroColor &to);

  operator uint32_t() const;

  void Print() const;

private:
  float m_red = 0.0f;
  float m_green = 0.0f;
  float m_blue = 0.0f;
};
