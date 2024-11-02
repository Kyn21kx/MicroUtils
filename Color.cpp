#include "Color.h"
#include "MicroMath.h"

constexpr float MAX_UINT8_F = 255.0f;

Color::Color(uint8_t r, uint8_t g, uint8_t b) { this->SetRGBInteger(r, g, b); }

void Color::SetRGBFloating(float r, float g, float b) {
  this->m_red = r;
  this->m_green = g;
  this->m_blue = b;
}

void Color::SetRGBInteger(uint8_t r, uint8_t g, uint8_t b) {
  this->m_red = r / MAX_UINT8_F;
  this->m_green = g / MAX_UINT8_F;
  this->m_blue = b / MAX_UINT8_F;
}

uint32_t Color::ToUInt32() const {
  // Ensure the values are within the expected range
  float r = (this->m_red < 0.0f)   ? 0.0f
            : (this->m_red > 1.0f) ? 1.0f
                                   : this->m_red;
  float g = (this->m_green < 0.0f)   ? 0.0f
            : (this->m_green > 1.0f) ? 1.0f
                                     : this->m_green;
  float b = (this->m_blue < 0.0f)   ? 0.0f
            : (this->m_blue > 1.0f) ? 1.0f
                                    : this->m_blue;

  // Convert to 8-bit values
  uint8_t red = static_cast<uint8_t>(r * 255);
  uint8_t green = static_cast<uint8_t>(g * 255);
  uint8_t blue = static_cast<uint8_t>(b * 255);

  // Combine into a single uint32_t value
  uint32_t hexColor = (red << 16) | (green << 8) | blue;
  return hexColor;
}

float Color::GetRed() const {
  return this->m_red;
}

float Color::GetGreen() const {
  return this->m_green;
}

float Color::GetBlue() const {
  return this->m_blue;
}

static Color Lerp(const Color &from, const Color &to, float t) {
  float r, g, b;
  r = MicroMath::Lerp(from.GetRed(), to.GetRed(), t);
  g = MicroMath::Lerp(from.GetGreen(), to.GetGreen(), t);
  b = MicroMath::Lerp(from.GetBlue(), to.GetBlue(), t);
  Color result;
  result.SetRGBFloating(r, g, b);
  return result;
}

static float DistanceToSqr(const Color& from, const Color& to) {
  float rDiff = to.GetRed() - from.GetRed();
  float gDiff = to.GetGreen() - from.GetGreen();
  float bDiff = to.GetBlue() - from.GetBlue();
  return (rDiff * rDiff) + (gDiff * gDiff) + (bDiff * bDiff); 
}
  
Color::operator uint32_t() const {
  return this->ToUInt32();
}

