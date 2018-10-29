#pragma once

#include <fstream>

using namespace std;

class Log
{
  public:
    Log();
    Log(char *);
    ~Log();
    void Write(char *txt);
    void Open(const char *);

  private:
    ofstream m_stream;
};
