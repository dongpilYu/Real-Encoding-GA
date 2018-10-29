#pragma once

#include "Chromosome.h"
#include "Constraints.h"
#include <vector>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

const double infinity = 9999999999999;

class Population
{
  public:
    Population(void);
    ~Population(void);
    void SetConstraints(const Constraint &constraint);
    void setChromosomeSize(const int &size);
    void CreateRandomPopulation(const int &size);
    void Crossover(const int &index1, const int &index2, const int &extension_rate);
    void Mutation(const int &index, const int &mutationRate);
    double EvaluatePopulation(Chromosome *bestChromosome);
    double CalcChromosomeFitness(const int &index);

    double GetChromosomeFitness(const int &index) const;
    void CopyChromosome(const int &source, const int &dest);

  private:
    Chromosome *CreateRandomChromosome();

    double CalculateFitnessFunction(const Chromosome &chr);

  private:
    std::vector<Chromosome *> pop;
    int chromosome_size;
    Constraint constraintType;
};
