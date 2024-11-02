#pragma once

#include <stdint.h>

class MicroTimer {

public:
  void Start();

  unsigned long Stop();

  unsigned long Reset();

  unsigned long CurrentSeconds();

  bool IsRunning() const;
  
private:
  unsigned long m_initialTime = 0;
  bool m_isRunning;
};

