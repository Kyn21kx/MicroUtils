#include "MicroTimer.h"
#include "Definitions.h"
#include "Logging.h"

#if MICRO_PLATFORM
#include "Arduino.h"
#else
float millis() {
  Logger::WarnLine("Timer started for unsupported platform!");
  return 0.0f;
}
void interrupts() {
  Logger::WarnLine("Interrupt timer enabled for unsupported platform!");
}
#endif

constexpr unsigned long MILLIS_TO_SEC = 1000;

void MicroTimer::Start() {
  interrupts();
  Logger::DebugLine("Enabling interrputs...");
  this->m_initialTime = millis();
  this->m_isRunning = true;
  Logger::DebugLine("Starting timer with initial time of %lu...",
                    this->m_initialTime);
}

unsigned long MicroTimer::Stop() {
  this->m_isRunning = false;
  return this->CurrentSeconds();
}

unsigned long MicroTimer::Reset() {
  unsigned long result = this->Stop();
  this->Start();
  return result;
}

unsigned long MicroTimer::CurrentSeconds() {
  unsigned long currTime = millis();
  Logger::DebugLine("Current time before operation: %lu", currTime);
  unsigned long long diff = (currTime - this->m_initialTime);
  Logger::DebugLine("Difference: %llu", diff);
  unsigned long secs = diff / MILLIS_TO_SEC;
  Logger::DebugLine("Time from timer: %lu", secs);
  return secs;
}

bool MicroTimer::IsRunning() const { return this->m_isRunning; }
