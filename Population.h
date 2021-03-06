#pragma once

#include "Chromosome.h"
#include "Constraints.h"
#include <cstdio>
#include <cstring>
#include <vector>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

const double infinity = 9999999999999;
const double minus_infinity = -9999999999999;
class Population
{
public:
    Population(void);
    ~Population(void);
    void SetConstraints(Constraint &constraint);
    void setChromosomeSize(const int &size);
    void CreateRandomPopulation(const int &size, const int &pr);
    void ExtendedBoxCrossover(const int &index1, const int &index2, const int &extension_rate);
    void OnePointCrossover(const int &index1, const int &index2, const int &point);
    void GaussianMutation(const int &index, const int &mutationRate);
    void BitwiseMutation(const int &index, const int &mutationRate);
    double EvaluatePopulation(Chromosome *bestChromosome, Chromosome *worstChromosome, int *bestIdx, int *worstIdx, double* aveFitness);
    double EvaluatePopulation_with_ML(Chromosome *bestChromosome, Chromosome *worstChromosome, int *bestIdx, int *worstIdx, double* aveFitness);
    double CalcChromosomeFitness(const int &index);
    void CopyChromosome(const int &source, const int &dest);
    const Constraint &GetConstraints() const;
    double GetChromosomeFitness(const int &index) const;
    std::vector<Chromosome *> GetPopulation() const;
    void setTransform(const int &transformOrNot);
    enum parent
    {
        mama = 0,
        dady
    };

private:
    Chromosome *CreateRandomChromosome_bin();
    Chromosome *CreateRandomChromosome_real();
    double CalculateFitnessFunction(const Chromosome &chr);

private:
    std::vector<Chromosome *> pop;
    int chromosome_size;
    int transformOrNot;
    Constraint constraintType;
};
