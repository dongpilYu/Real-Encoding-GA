#pragma once

#include "Constraints.h"
#include "Log.h"
#include "Population.h"
#include <random>
#include <sys/time.h>

class GeneticAlgorithm {
  public:
    GeneticAlgorithm();
    ~GeneticAlgorithm();

    void Initialize(const int &binaryOrNot, const int &problem_type,
                    const int &royal_number, const int &num_k,
                    const int &crossover_rate, const int &mutation_rate,
                    const int &population_size, const int &number_iterations,
                    const int &chromosome_size, const int &tournament_size,
                    const int &precision, const int &epoch,
                    const std::string &path, Constraint &constraint,
                    const int &transformOrNot);
    void SetConstraints(Constraint &constraint, const int &chromosome_size,
                        const int &pr, const int &royal_number,
                        const int &num_k);
    void Run();

  private:
    void CreatePopulation(const int &pr);
    double *Evaluate();
    double *Evaluate_with_ML();
    void Crossover();
    void Mutate();
    void Select();
    void Elitism();
    void SetParameters(const int &binaryOrNot, const int &problem_type,
                       const int &crossover_rate, const int &mutation_rate,
                       const int &population_size, const int &number_iterations,
                       const int &chromosome_size, const int &tournament_size,
                       const int &precision, const int &epoch,
                       const int &transformOrNot);
    void SetParameters(const int &binaryOrNot, const int &problem_type,
                       const int &royal_number, const int &num_k,
                       const int &crossover_rate, const int &mutation_rate,
                       const int &population_size, const int &number_iterations,
                       const int &chromosome_size, const int &tournament_size,
                       const int &precision, const int &epoch,
                       const int &transformOrNot);
    void SetRandomSeed();
    void LogResult(const double *result, const int &iter, bool best);
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
    int problem_type;
    bool BinValued;

    int num_k;
    int royal_number;

    double bestFitness;
    Chromosome *bestChromosome;
    Chromosome *worstChromosome;
    int best_idx;
    int worst_idx;
    Population pop;
    Log log;

    bool evaluateWithML;
    int transformOrNot;
};
