#include "Logging.h"

#if MICRO_PLATFORM
  #include <stdarg.h>
  #include <string.h>
#else
  #include <cstdarg>
  #include <cstring>
#endif

#include <stdint.h>

constexpr uint32_t MAX_LOG_BUFFER_SIZE = 256;

constexpr uint32_t MAX_FORMAT_BUFFER_SIZE = 200;

Print *Logger::s_output;

void Logger::Begin(Print *output) { s_output = output; }

void Logger::LogLevel(ELogLevel level, const char *format, ...) {
  if (s_output == nullptr)
    return;
  va_list args;
  va_start(args, format);
  char formatBuffer[MAX_FORMAT_BUFFER_SIZE] = "";
  char printBuffer[MAX_LOG_BUFFER_SIZE];

  switch (level) {
  case Info:
    strncat(formatBuffer, "[Info] - ", MAX_FORMAT_BUFFER_SIZE);
    break;
  case Debug:
    strncat(formatBuffer, "[Debug] - ", MAX_FORMAT_BUFFER_SIZE);
    break;
  case Error:
    strncat(formatBuffer, "[Error] ", MAX_FORMAT_BUFFER_SIZE);
    break;
  case Warn:
    strncat(formatBuffer, "[Warn] - ", MAX_FORMAT_BUFFER_SIZE);
    break;
  }

  strncat(formatBuffer, format, MAX_LOG_BUFFER_SIZE);

#if MICRO_PLATFORM
  vsprintf(printBuffer, formatBuffer, args);
  s_output->print(printBuffer);
#else

  vfprintf(s_output, formatBuffer, args);

#endif
  va_end(args);
}

void Logger::DebugLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logger::LogLevel(ELogLevel::Debug, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logger::InfoLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logger::LogLevel(ELogLevel::Info, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logger::WarnLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logger::LogLevel(ELogLevel::Warn, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logger::ErrorLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logger::LogLevel(ELogLevel::Error, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logger::SimplePrint(const char *message) {
#if MICRO_PLATFORM
  s_output->print(message);
#else
  fprintf(s_output, "%s", message);
#endif
}
