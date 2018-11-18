#pragma once

#include <memory>

class Chromosome
{
  public:
    Chromosome();
    Chromosome(const int &size);
    ~Chromosome(void);

    double GetFitness() const;
    int GetSize() const;
    double getChromosome(const int &idx) const;

    void setFitness(const double &fitness);
    void setChromosome(const int &idx, const double &value);
    void setChromosome(const int &idx, const int &value);
    void setChromosomeSize(const int &size);

    Chromosome &operator=(const Chromosome &other);

  private:
    std::unique_ptr<double[]> chr;
    double fitness;
    int size;
};
