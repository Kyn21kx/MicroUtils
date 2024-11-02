#include "MicroStringUtils.h"
#include "MicroMath.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void MicroStringUtils::Append(char *buffer, int16_t toAppend, uint32_t offset,
                              uint32_t maxSize) {
  // Get the number of digits here
  uint8_t digitCount = MicroMath::DigitCount(toAppend);
  char appendBuffer[MAX_INT16_BUFFER_SIZE];
  sprintf(appendBuffer, "%d", toAppend);
  strncpy(buffer + offset, appendBuffer, strlen(appendBuffer));
}

char MicroStringUtils::ToChar(int16_t n) { return n + '0'; }

void FormatString(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);
  sprintf(buffer, format, args);
  va_end(args);
}
