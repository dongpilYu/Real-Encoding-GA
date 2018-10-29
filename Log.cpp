#include "Log.h"

Log::Log()
{
}

Log::Log(char *filename)
{
    m_stream.open(filename, fstream::app);
}

void Log::Write(char *txt)
{
    m_stream << txt << endl;
}

Log::~Log()
{
    m_stream.close();
}

// Open the log file for writing
void Log::Open(const char *filename)
{
    m_stream.open(filename, fstream::app);
}
