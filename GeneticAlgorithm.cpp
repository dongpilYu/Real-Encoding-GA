#include "GeneticAlgorithm.h"

#include <iomanip>
#include <iostream>
#include <sstream>

GeneticAlgorithm::GeneticAlgorithm()
{
    bestFitness = 9999999999999;
    bestChromosome = new Chromosome();
    SetRandomSeed();
}
GeneticAlgorithm::~GeneticAlgorithm()
{
    delete bestChromosome;
}
void GeneticAlgorithm::Initialize(const int &pr, const int &royal_number, const int &num_k, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch, const std::string &path, Constraint &constraint)
{
    SetParameters(royal_number, num_k, crossover_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch);
    SetConstraints(constraint, chromosome_size, pr, royal_number, num_k);
    CreatePopulation(pr);
    log.Open(path.c_str());
}

void GeneticAlgorithm::SetRandomSeed()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
void GeneticAlgorithm::SetConstraints(Constraint &constraint, const int &chromosome_size, const int &pr, const int &royal_number, const int &num_k)
{
    pop.SetConstraints(constraint);
    if (pr < 5)
        constraint.Make_optimal_solution(chromosome_size);
    else
        constraint.setParms(num_k, royal_number);
}

// Run the genetic algorithm
void GeneticAlgorithm::Run()
{
    for (int i = 0; i < number_iterations; i++)
    {
        LogResult(pop);
        LogResult(Evaluate(), i);
        Select();
        Crossover();
        Mutate();
    }
}

// Create initial random population of chromosomes
void GeneticAlgorithm::CreatePopulation(const int &pr)
{
    pop.CreateRandomPopulation(population_size, pr);
}
double GeneticAlgorithm::Evaluate()
{
    double best = pop.EvaluatePopulation(bestChromosome);

    // In real problem, we must find a chromosome that has small value
    if (best < bestFitness)
    {
        bestFitness = best;
    }

    return bestFitness;
}

// Apply crossover to selected chromosome pairs
void GeneticAlgorithm::Crossover()
{
    for (int i = 0; i < population_size; i++)
    {
        int r = rand() % 100;

        if (r < crossover_rate)
        {
            // Select random pair for crossover
            int index1 = rand() % population_size;
            int index2 = rand() % population_size;

            while (index1 == index2)
            {
                index2 = rand() % population_size;
            }

            if (index1 > index2)
            {
                int tmp = index1;
                index1 = index2;
                index2 = tmp;
            } // index1 < index2 임을 보장

            // Do Extended-box crossover
            pop.Crossover(index1, index2, extension_rate);
        }
    }
}
// Mutate selected chromosomes
void GeneticAlgorithm::Mutate()
{
    for (int i = 0; i < population_size; i++)
    {
        int r = rand() % 100;
        pop.Mutation(i, mutation_rate);
    }
}
// Select population chromosomes according to fitness
// Using a pairwise tournament selection mechanism
void GeneticAlgorithm::Select()
{
    // For each pair of chromosomes selected
    int i = 0;

    while (i < tournament_size)
    {
        // Get the chromosome pair for tournament selection
        int index1 = rand() % population_size;
        int index2 = rand() % population_size;

        while (index1 == index2)
        {
            index2 = rand() % population_size;
        }

        double fitness1 = fabs(pop.GetChromosomeFitness(index1));
        double fitness2 = fabs(pop.GetChromosomeFitness(index2));

        // We seek to find [x,y] that minimizes this function
        // The bigget the value returned, the lower its fitness
        if (fitness1 > fitness2)
        {
            // Copy chromosome 1 elements into chromosome 2
            pop.CopyChromosome(index2, index1);
        }
        else
        {
            // Copy chromosome 2 elements into chromosome 1
            pop.CopyChromosome(index1, index2);
        }

        i++;
    }
}
void GeneticAlgorithm::SetParameters(const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch)
{
    this->crossover_rate = crossover_rate;
    this->extension_rate = 50;
    this->mutation_rate = mutation_rate;
    this->population_size = population_size;
    this->number_iterations = number_iterations;
    this->tournament_size = tournament_size;
    this->precision = precision;
    this->epoch = epoch;
    this->chromosome_size = chromosome_size;
    pop.setChromosomeSize(chromosome_size);
    (*bestChromosome).setChromosomeSize(chromosome_size);
}
void GeneticAlgorithm::SetParameters(const int &royal_number, const int &num_k, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch)
{
    this->num_k = num_k;
    this->royal_number = royal_number;
    SetParameters(crossover_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch);
}
void GeneticAlgorithm::LogResult(const Population &pop)
{
    std::vector<Chromosome *> chrs = pop.GetPopulation();

    for (int i = 0; i < chrs.size(); i++)
        log.Write(*(chrs.at(i)));
}
void GeneticAlgorithm::LogResult(const double &result,
                                 const int &iter)
{

    log.Write(result);
    /*
    if (iter % epoch == 0)
    {

        std::stringstream ss;
        ss << iter << "\t" << result << "\n";

        log.Write((char *)ss.str().c_str());
    }
    */
    /*
    if (iter % epoch == 0 || iter < epoch)
    {
        std::cout << "Iteration = " << std::setw(6) << iter
                  << " X = " << std::fixed << std::setprecision(precision) << std::setw(precision + 1) << best_x
                  << " Y = " << std::fixed << std::setprecision(precision) << std::setw(precision + 1) << best_y
                  << " F(x,y) = " << std::setw(precision + 1) << bestFitness
                  << std::endl;
    }
    */
}
