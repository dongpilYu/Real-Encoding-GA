#pragma once

#include <memory>

class Chromosome
{
  public:
    Chromosome(const int &size);
    ~Chromosome(void);

    double GetFitness() const;
    int GetSize() const;
    double getChromosome(const int &idx);

    void setFitness(const double &fitness);
    void setChromosome(const int &idx, const double &value);
    void setChromosomeSize(const int &size);

    void Print(const int &index) const;

    Chromosome &operator=(const Chromosome &other);

  private:
    std::unique_ptr<double[]> chr;
    double fitness;
    int size;
};
