#include "Color.h"
#include "Logging.h"
#include <cstdint>

constexpr float MAX_UINT8_F = 255.0f;

constexpr uint8_t GAMMA_TABLE[] = {
    0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   2,   2,
    2,   2,   3,   3,   3,   3,   4,   4,   4,   5,   5,   5,   6,   6,   6,
    7,   7,   7,   8,   8,   9,   9,   10,  10,  10,  11,  11,  12,  12,  13,
    13,  14,  14,  15,  15,  16,  17,  17,  18,  18,  19,  19,  20,  21,  21,
    22,  22,  23,  24,  24,  25,  26,  26,  27,  28,  28,  29,  30,  30,  31,
    32,  33,  33,  34,  35,  36,  36,  37,  38,  39,  39,  40,  41,  42,  43,
    43,  44,  45,  46,  47,  48,  48,  49,  50,  51,  52,  53,  54,  55,  56,
    56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,
    71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,
    86,  88,  89,  90,  91,  92,  93,  94,  95,  97,  98,  99,  100, 101, 102,
    103, 105, 106, 107, 108, 109, 111, 112, 113, 114, 115, 117, 118, 119, 120,
    122, 123, 124, 125, 127, 128, 129, 131, 132, 133, 134, 136, 137, 138, 140,
    141, 142, 144, 145, 146, 148, 149, 151, 152, 153, 155, 156, 157, 159, 160,
    162, 163, 164, 166, 167, 169, 170, 172, 173, 174, 176, 177, 179, 180, 182,
    183, 185, 186, 188, 189, 191, 192, 194, 195, 197, 198, 200, 201, 203, 205,
    206, 208, 209, 211, 212, 214, 216, 217, 219, 220, 222, 224, 225, 227, 228,
    230, 232, 233, 235, 237, 238, 240, 242, 243, 245, 247, 248, 250, 252, 253,
    255
};

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

  // Convert to 8-bit values
  uint8_t red = static_cast<uint8_t>(r * 255);
  uint8_t green = static_cast<uint8_t>(g * 255);
  uint8_t blue = static_cast<uint8_t>(b * 255);

  // Combine into a single uint32_t value
  switch (format) {
  case RGB:
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
  case GRB:
    red = GAMMA_TABLE[red];
    green = GAMMA_TABLE[green];
    blue = GAMMA_TABLE[blue];
    return ((uint32_t)green << 16) | ((uint32_t)red << 8) | blue;
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
      

