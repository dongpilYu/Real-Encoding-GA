#include "GeneticAlgorithm.h"

#include <iomanip>
#include <iostream>
#include <sstream>

GeneticAlgorithm::GeneticAlgorithm()
{
    bestFitness = -9999999999999;
}
GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::Initialize(const int &crossover_rate, const int &extension_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch, const std::string &path, const Constraint &constraint)
{
    SetParameters(crossover_rate, extension_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch);
    SetConstraints(constraint);
    CreatePopulation();
    log.Open(path.c_str());
}
void GeneticAlgorithm::SetConstraints(const Constraint &constraint)
{
    pop.SetConstraints(constraint);
}

// Run the genetic algorithm
void GeneticAlgorithm::Run()
{
    for (int i = 0; i < number_iterations; i++)
    {
        LogResult(Evaluate(), i);
        Select();
        Crossover();
        Mutate();
    }
}

// Create initial random population of chromosomes
void GeneticAlgorithm::CreatePopulation()
{
    pop.CreateRandomPopulation(population_size);
}
double GeneticAlgorithm::Evaluate()
{
    double best = pop.EvaluatePopulation(bestChromosome);

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
void GeneticAlgorithm::SetParameters(const int &crossover_rate, const int &extension_rate, const int &mutation_rate, const int &population_size, const int &number_iterations, const int &chromosome_size, const int &tournament_size, const int &precision, const int &epoch)
{
    this->crossover_rate = crossover_rate;
    this->extension_rate = extension_rate;
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

void GeneticAlgorithm::LogResult(const double &result,
                                 const int &iter)
{
    /*if ( iter % count == 0 )
	{
		std::stringstream ss;
		ss << iter << "\t" << result << "\t" << best_x << "\t" << best_y;
		log.Write( (char*) ss.str().c_str() );
	}*/
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
