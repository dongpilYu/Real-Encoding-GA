#pragma once

#include "Constraints.h"
#include "Log.h"
#include "Population.h"

class GeneticAlgorithm
{
  public:
    GeneticAlgorithm();
    ~GeneticAlgorithm();

    void Initialize(const int &crossover_rate, const int &alpha, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch, const std::string &path, const Constraint &constraint);

    void SetConstraints(const Constraint &constraint);
    void Run();

  private:
    void CreatePopulation();
    double Evaluate();
    void Crossover();
    void Mutate();
    void Select();
    void SetParameters(const int &crossover_rate, const int &alpha, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch);
    void LogResult(const double &result, const int &iter);

  private:
    int crossover_rate;
    int extension_rate;
    int mutation_rate;
    int population_size;
    int number_iterations;
    int chromosome_size;
    int tournament_size;
    int precision;
    int epoch;

    double bestFitness;
    Chromosome *bestChromosome;

    Population pop;
    Log log;
};
