#include "Population.h"
#include <bitset>
#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
//#include <sys/time.h>
Population::Population(void)
{
}

Population::~Population(void)
{
    int size = (int)pop.size();

    // Delete the chromosome pointers
    for (int i = 0; i < size; i++)
    {
        Chromosome *chr = pop.at(i);

        if (chr)
        {
            delete chr;
        }
    }

    pop.clear();
}

void Population::SetConstraints(const Constraint &constraint)
{
    constraintType = constraint;
}
void Population::setChromosomeSize(const int &size)
{
    chromosome_size = size;
}
// Create initial arbitrary population of chromosomes, size : size of population
void Population::CreateRandomPopulation(const int &size)
{
    for (int i = 0; i < size; i++)
    {
        Chromosome *chr = CreateRandomChromosome();
        pop.push_back(chr);
    }
}
// Apply one-point crossover to selected chromosome pair
void Population::Crossover(const int &index1, const int &index2, const int &extension_rate)
{
    Chromosome *mom = pop.at(index1);
    Chromosome *dad = pop.at(index2);

    enum parent pa;
    if (mom->GetFitness() > dad->GetFitness())
        pa = mama;
    else
        pa = dady;
    // crossover를 통해 얻은 자식을 적합도가 낮은 부모로 대체
    for (int i = 0; i < chromosome_size; i++)
    {
        double mini, maxi, extendedMin, extendedMax;

        mini = MIN(mom->getChromosome(i), dad->getChromosome(i));
        maxi = MAX(mom->getChromosome(i), dad->getChromosome(i));

        extendedMin = mini - extension_rate / 100 * (maxi - mini);
        if (extendedMin < constraintType.min)
            extendedMin = constraintType.min;
        extendedMax = maxi + extension_rate / 100 * (maxi - mini);
        if (extendedMax > constraintType.max)
            extendedMax = constraintType.max;

        double z = rand() / (double(RAND_MAX) + 1) * (extendedMax - extendedMin) + extendedMax;
        if (pa == mama)
            dad->setChromosome(i, z);
        else
            mom->setChromosome(i, z);
    }
    if (pa == mama)
        dad->setFitness(CalcChromosomeFitness(index2));
    else
        mom->setFitness(CalcChromosomeFitness(index1));
}

// Apply mutation to selected chromosome: x part or y part
void Population::Mutation(const int &index, const int &mutation_rate)
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(constraintType.min, constraintType.max);
    for (int i = 0; i < chromosome_size; i++)
    {
        if (rand() % 100 < mutation_rate)
        {
            double z = pop.at(index)->getChromosome(i);
            z += distribution(generator);
            pop.at(index)->setChromosome(i, z);
        }
    }
    pop.at(index)->setFitness(CalcChromosomeFitness(index));
}

// Evaluate the population fitnesses
double Population::EvaluatePopulation(Chromosome *bestChromosome)
{
    double totalFitness = 0.0;
    double aveFitness = 0.0;
    double bestFitness = infinity;
    int bestFitnessIndex = 0;

    for (int i = 0; i < (int)pop.size(); i++)
    {
        double fitness = CalcChromosomeFitness(i);
        Chromosome *chr = pop.at(i);
        puts("hum\n");
        chr->setFitness(fitness);
        puts("jn\n");
        // Output the chromosome
        //chr->Print( i );
        //totalFitness += fitness;
        // Store best solution
        if (i == 0)
            bestFitness = fitness;
        printf("best : %lf\n", bestFitness);
        if (fitness < bestFitness)
        {
            bestFitness = fitness;
            bestFitnessIndex = i;
            bestChromosome = chr;
        }
    }

    //std::cout << "\n\n";

    //aveFitness = totalFitness / pop.size();
    return bestFitness;
}

// Create an arbitrary random chromosome
Chromosome *Population::CreateRandomChromosome()
{
    //struct timeval time;
    //gettimeofday(&time, NULL);
    //srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    srand(time(NULL));
    Chromosome *chr = new Chromosome(chromosome_size);

    for (int i = 0; i < chr->GetSize(); i++)
    {

        double value = rand() / (double(RAND_MAX) + 1) * constraintType.max;
        if (rand() % 2 == 1)
            value = value * -1;
        // constraintType.max와 constraintType.min이 부호만 다르기 때문에

        //printf("%d %lf\n", i, value);
        chr->setChromosome(i, value);
    }
    //printf("\n");
}
double Population::CalculateFitnessFunction(const Chromosome &chr)
{
    return constraintType.Fitness(chr);
}

double Population::GetChromosomeFitness(const int &index) const
{
    Chromosome *chr = pop.at(index);
    return chr->GetFitness();
}
void Population::CopyChromosome(const int &source, const int &dest)
{
    // Get the chromosomes
    Chromosome *chr1 = pop.at(source);
    Chromosome *chr2 = pop.at(dest);

    // Copy elements and fitness of source chromosome
    // into the destination chromosome
    for (int i = 0; i < chromosome_size; i++)
    {
        // Get source chromosome element
        double value = chr1->getChromosome(i);

        // Write this element value into the destination element
        chr2->setChromosome(i, value);
    }

    // Set the destination chromosome fitness
    double fitness = chr1->GetFitness();
    chr2->setFitness(fitness);
}

double Population::CalcChromosomeFitness(const int &index)
{
    double fitness = CalculateFitnessFunction(*(pop.at(index)));
    return fitness;
}
