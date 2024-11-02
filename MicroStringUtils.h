#pragma once

#include "Definitions.h"

#include <stdint.h>

constexpr uint32_t MAX_INT16_BUFFER_SIZE = 6;

class MicroStringUtils {

public:    
    static void Append(char* buffer, int16_t toAppend, uint32_t offset,  uint32_t maxSize);
  
    static char ToChar(int16_t n);

    static void FormatString(char* buffer, const char* format, ...);

    //static void ToString(int16_t n);
};


