#include "Color.h"
#include "Logging.h"
#include <cstdint>

constexpr float MAX_UINT8_F = 255.0f;

MicroColor::MicroColor(uint8_t r, uint8_t g, uint8_t b) {
  this->SetRGBInteger(r, g, b);
}

void MicroColor::SetRGBFloating(float r, float g, float b) {
  this->m_red = r;
  this->m_green = g;
  this->m_blue = b;
}

void MicroColor::SetRGBInteger(uint8_t r, uint8_t g, uint8_t b) {
  this->m_red = r / MAX_UINT8_F;
  this->m_green = g / MAX_UINT8_F;
  this->m_blue = b / MAX_UINT8_F;
}

uint32_t MicroColor::ToUInt32(MicroColorFormat format) const {
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

  uint32_t red = static_cast<uint32_t>(r * 255);
  uint32_t green = static_cast<uint32_t>(g * 255);
  uint8_t blue = static_cast<uint8_t>(b * 255);

  // Combine into a single uint32_t value
  switch (format) {
  case RGB:
    return (red << 16) | (green << 8) | blue;
  case GRB:
    return (green << 16) | (red << 8) | blue;
  default:
    Logger::ErrorLine("Unidentified color format %d", (uint8_t)format);
    return 0;
  }
}

float MicroColor::GetRed() const { return this->m_red; }

float MicroColor::GetGreen() const { return this->m_green; }

float MicroColor::GetBlue() const { return this->m_blue; }

static float DistanceToSqr(const MicroColor &from, const MicroColor &to) {
  float rDiff = to.GetRed() - from.GetRed();
  float gDiff = to.GetGreen() - from.GetGreen();
  float bDiff = to.GetBlue() - from.GetBlue();
  return (rDiff * rDiff) + (gDiff * gDiff) + (bDiff * bDiff);
}

MicroColor::operator uint32_t() const {
  return this->ToUInt32(MicroColorFormat::RGB);
}

void MicroColor::Print() const {
  Logger::LogLevel(ELogLevel::Info, "(%f, %f, %f)", this->m_red, this->m_green,
                   this->m_blue);
}

uint8_t MicroColor::GetRedInt() const {
  return static_cast<uint8_t>(this->m_red * 255.0f);
}

uint8_t MicroColor::GetGreenInt() const {
    return static_cast<uint8_t>(this->m_green * 255.0f);
}

uint8_t MicroColor::GetBlueInt() const {
    return static_cast<uint8_t>(this->m_blue * 255.0f);
}
      

