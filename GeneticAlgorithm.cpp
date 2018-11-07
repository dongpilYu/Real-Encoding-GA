#include "GeneticAlgorithm.h"

#include <iomanip>
#include <iostream>
#include <sstream>

GeneticAlgorithm::GeneticAlgorithm()
{
    bestChromosome = new Chromosome();
    SetRandomSeed();
}
GeneticAlgorithm::~GeneticAlgorithm()
{
    delete bestChromosome;
}
void GeneticAlgorithm::Initialize(const int &binaryOrNot, const int &problem_type, const int &royal_number, const int &num_k, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch, const std::string &path, Constraint &constraint)
{
    if (binaryOrNot)
        bestFitness = -9999999999999;
    else
        bestFitness = 9999999999999;

    log.Open(path.c_str());
    SetParameters(binaryOrNot, problem_type, royal_number, num_k, crossover_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch);
    SetConstraints(constraint, chromosome_size, problem_type, royal_number, num_k);
    CreatePopulation(binaryOrNot);
}

void GeneticAlgorithm::SetRandomSeed()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
void GeneticAlgorithm::SetConstraints(Constraint &constraint, const int &chromosome_size, const int &pr, const int &royal_number, const int &num_k)
{
    if (BinValued)
        constraint.setParms(num_k, royal_number, chromosome_size);
    else
        log.Write(constraint.Make_optimal_solution(chromosome_size));
    pop.SetConstraints(constraint);
}

// Run the genetic algorithm
void GeneticAlgorithm::Run()
{
    bool findBest = false;
    for (int i = 0; i < number_iterations + 1; i++)
    {
        if (BinValued)
        {
            if (bestFitness == chromosome_size)
                findBest = true;
        }
        else
        {
            if (bestFitness == 0)
                findBest = true;
        }
        // LogResult(pop);
        LogResult(Evaluate(), i, findBest);
        if (true == findBest)
            break;
        Select();
        Crossover();
        Mutate();
    }
}

// Create initial random population of chromosomes
void GeneticAlgorithm::CreatePopulation(const int &binaryOrNot)
{
    pop.CreateRandomPopulation(population_size, binaryOrNot);
}
double GeneticAlgorithm::Evaluate()
{
    double best = pop.EvaluatePopulation(bestChromosome);

    if (BinValued) // maximization problem
    {
        if (best > bestFitness)
            bestFitness = best;
    }
    else // minimization problem
    {
        if (best < bestFitness)
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

            int point = rand() % chromosome_size;

            if (BinValued)
                pop.OnePointCrossover(index1, index2, point);
            else
                pop.ExtendedBoxCrossover(index1, index2, extension_rate);
        }
    }
}
// Mutate selected chromosomes
void GeneticAlgorithm::Mutate()
{
    for (int i = 0; i < population_size; i++)
    {
        int r = rand() % 100;

        if (BinValued)
            pop.BitwiseMutation(i, mutation_rate);
        else
            pop.GaussianMutation(i, mutation_rate);
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

        double fitness1 = pop.GetChromosomeFitness(index1);
        double fitness2 = pop.GetChromosomeFitness(index2);

        if (BinValued) // maximization problem
        {
            if (fitness1 < fitness2)
                pop.CopyChromosome(index2, index1);
            // Copy chromosome 1 elements into chromosome 2
            else
                pop.CopyChromosome(index1, index2);
            // Copy chromosome 2 elements into chromosome 1
        }
        else // minimization problem
        {
            if (fitness1 > fitness2)
                pop.CopyChromosome(index2, index1);
            else
                pop.CopyChromosome(index1, index2);
        }
        i++;
    }
}
void GeneticAlgorithm::SetParameters(const int &binaryOrNot, const int &problem_type, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch)
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
    this->problem_type = problem_type;
    this->BinValued = binaryOrNot;

    pop.setChromosomeSize(chromosome_size);
    (*bestChromosome).setChromosomeSize(chromosome_size);
}
void GeneticAlgorithm::SetParameters(const int &binaryOrNot, const int &problem_type, const int &royal_number, const int &num_k, const int &crossover_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch)
{
    this->num_k = num_k;
    this->royal_number = royal_number;
    SetParameters(binaryOrNot, problem_type, crossover_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch);
}
void GeneticAlgorithm::LogResult(const Population &pop)
{
    std::vector<Chromosome *> chrs = pop.GetPopulation();

    for (int i = 0; i < chrs.size(); i++)
        log.Write((chrs.at(i)));
}
void GeneticAlgorithm::LogResult(const double &result,
                                 const int &iter, bool findBest)
{
    if (findBest)
    {
        std::stringstream ss;
        ss << "Iteration = " << std::setw(6) << iter << " Best fitness : " << result << std::endl;
        log.Write((char *)ss.str().c_str());
        std::cout << "Iteration = " << std::setw(6) << iter << " Best fitness : " << result << std::endl;
    }
    else
    {
        if (iter % epoch == 0 || iter < epoch)
        {
            std::stringstream ss;
            ss << "Iteration = " << std::setw(6) << iter << " Best fitness : " << result << std::endl;
            log.Write((char *)ss.str().c_str());
            std::cout << "Iteration = " << std::setw(6) << iter << " Best fitness : " << result << std::endl;
        }
    }
}
