#pragma once

#include "Chromosome.h"
#include <fstream>
class Log
{
  public:
    Log();
    Log(char *);
    ~Log();
    void Write(char *txt);
    void Write(double result);
    void Write(const Chromosome &chr);
    void Open(const char *);

  private:
    std::ofstream m_stream;
};
