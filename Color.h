#pragma once

#include <cstdint>
#include <stdint.h>

class Color {

public:  
  Color() = default;
  
  Color(uint8_t r, uint8_t g, uint8_t b);
  
  void SetRGBFloating(float r, float g, float b);

  void SetRGBInteger(uint8_t r, uint8_t g, uint8_t b);

  uint32_t ToUInt32() const;

  float GetRed() const;

  float GetGreen() const;

  float GetBlue() const;
  
  static Color Lerp(const Color& from, const Color& to, float t);

  static float DistanceToSqr(const Color& from, const Color& to);

private:
  float m_red = 0.0f;
  float m_green = 0.0f;
  float m_blue = 0.0f;
};

