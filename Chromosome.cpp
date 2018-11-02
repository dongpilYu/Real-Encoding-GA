#include "Chromosome.h"
#include <iostream>

Chromosome::Chromosome()
{
}
Chromosome::Chromosome(const int &size)
{
    this->size = size;
    chr = std::unique_ptr<double[]>(new double[size]);
}

Chromosome &Chromosome::operator=(const Chromosome &other)
{
    this->size = other.size;
    this->fitness = other.fitness;
    for (int i = 0; i < size; i++)
    {
        this->chr[i] = other.chr[i];
    }
    return *this;
}
Chromosome::~Chromosome()
{
}
void Chromosome::setChromosomeSize(const int &chromosome_size)
{
    size = chromosome_size;
}
void Chromosome::setChromosome(const int &idx, const double &value)
{
    if (idx < 0 || idx >= size)
        return;

    chr[idx] = value;
}
void Chromosome::setChromosome(const int &idx, const int &value)
{
    if (idx < 0 || idx >= size)
        return;

    chr[idx] = value;
}
void Chromosome::setFitness(const double &value)
{
    fitness = value;
}
double Chromosome::getChromosome(const int &idx) const
{
    return chr[idx];
}
double Chromosome::GetFitness() const
{
    return fitness;
}
int Chromosome::GetSize() const
{
    return size;
}
void Chromosome::Print(const int &index) const
{
}
