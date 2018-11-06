#include "Log.h"

Log::Log()
{
}
Log::~Log()
{
    m_stream.close();
}
Log::Log(char *filename)
{
    m_stream.open(filename, std::fstream::app);
}

void Log::Write(char *txt)
{
    m_stream << txt;
}

void Log::Write(const Chromosome *chr)
{
    m_stream << "Optimal chromosome : ";
    for (int i = 0; i < chr->GetSize(); i++)
        m_stream << chr->getChromosome(i) << ' ';

    m_stream << std::endl;
}

// Open the log file for writing
void Log::Open(const char *filename)
{
    m_stream.open(filename, std::fstream::app);
}
