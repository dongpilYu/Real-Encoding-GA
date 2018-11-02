#pragma once

#include "Constraints.h"
#include "Log.h"
#include "Population.h"
#include <random>
#include <sys/time.h>

class GeneticAlgorithm
{
  public:
    GeneticAlgorithm();
    ~GeneticAlgorithm();

    void Initialize(const int &pr, const int &royal_number, const int &num_k, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch, const std::string &path, Constraint &constraint);
    void SetConstraints(Constraint &constraint, const int &chromosome_size, const int &pr, const int &royal_number, const int &num_k);
    void Run();

  private:
    void CreatePopulation(const int &pr);
    double Evaluate();
    void Crossover();
    void Mutate();
    void Select();
    void SetParameters(const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch);
    void SetParameters(const int &royal_number, const int &num_k, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch);
    void SetRandomSeed();
    void LogResult(const double &result, const int &iter);
    void LogResult(const Population &pop);

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

    int num_k;
    int royal_number;

    double bestFitness;
    Chromosome *bestChromosome;

    Population pop;
    Log log;
};
