#include "Population.h"
#include <bitset>
#include <iostream>
#include <math.h>

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

    if (constraintType._function == Constraint::NKlandscape)
    {
        for (int i = 0; i < chromosome_size; i++)
            delete constraintType.landscape[i];
        delete constraintType.landscape;
    }
}
const Constraint &Population::GetConstraints() const
{
    return constraintType;
}
void Population::SetConstraints(Constraint &constraint)
{
    constraintType = constraint;
}
void Population::setTransform(const int &transformOrNot)
{
    this->transformOrNot = transformOrNot;
}
void Population::setChromosomeSize(const int &size)
{
    chromosome_size = size;
}
// Create initial arbitrary population of chromosomes, size : size of population
void Population::CreateRandomPopulation(const int &size, const int &binaryOrNot)
{
    if (binaryOrNot)
    {
        for (int i = 0; i < size; i++)
        {
            Chromosome *chr = CreateRandomChromosome_bin();
            pop.push_back(chr);
        }
    }

    else
    {
        for (int i = 0; i < size; i++)
        {
            Chromosome *chr = CreateRandomChromosome_real();
            pop.push_back(chr);
        }
    }
}
std::vector<Chromosome *> Population::GetPopulation() const
{
    return pop;
}
// Apply one-point crossover to selected chromosome pair
void Population::OnePointCrossover(const int &index1, const int &index2, const int &point)
{
    Chromosome *chr1 = pop.at(index1);
    Chromosome *chr2 = pop.at(index2);

    for (int i = point; i < chromosome_size; i++)
    {
        unsigned char v1 = chr1->getChromosome(i);
        unsigned char v2 = chr2->getChromosome(i);

        chr1->setChromosome(index1, v2);
        chr2->setChromosome(index1, v1);
    }
}
void Population::ExtendedBoxCrossover(const int &index1, const int &index2, const int &extension_rate)
{
    Chromosome *mom = pop.at(index1);
    Chromosome *dad = pop.at(index2);

    enum parent pa;

    if (mom->GetFitness() < dad->GetFitness())
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

        double z = rand() / (double(RAND_MAX) + 1) * (extendedMax - extendedMin) + extendedMin;
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
void Population::GaussianMutation(const int &index, const int &mutation_rate)
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, (constraintType.max - constraintType.min) / 10);

    Chromosome *chr = pop.at(index);

    for (int i = 0; i < chromosome_size; i++)
    {
        if (rand() % 100 < mutation_rate)
        {
            double z = chr->getChromosome(i);
            z += distribution(generator);
            if (z > constraintType.max)
                z = constraintType.max;
            if (z < constraintType.min)
                z = constraintType.min;
            chr->setChromosome(i, z);
        }
    }
    chr->setFitness(CalcChromosomeFitness(index));
}

void Population::BitwiseMutation(const int &index, const int &mutation_rate)
{

    Chromosome *chr = pop.at(index);

    for (int i = 0; i < chromosome_size; i++)
    {
        int r = rand() % 100;

        if (r < mutation_rate)
        {
            unsigned char value = chr->getChromosome(i);
            value = rand() % 100 < 50 ? 1 : 0;
            chr->setChromosome(i, value);
        }
    }
    chr->setFitness(CalcChromosomeFitness(index));
}

double Population::EvaluatePopulation_with_ML(Chromosome *bestChromosome, Chromosome *worstChromosome, int *bestIdx, int *worstIdx, double* aveFitness)
{
    double totalFitness = 0.0;
    double bestFitness = infinity;
    double worstFitness = minus_infinity;
    int bestFitnessIndex = 0;
    int worstFitnessIndex = 0;
    char toParser[110000];
    char everySol[100000];
    char type[30];

    memset(toParser, 0, sizeof(toParser));
    memset(everySol, 0, sizeof(everySol));
    memset(type, 0, sizeof(type));

    switch (constraintType._function)
    {
    case Constraint::Onemax:
        strcpy(type, "onemax");
        bestFitness = minus_infinity;
        worstFitness = infinity;

        break;
    case Constraint::Royalroad:
        strcpy(type, "royal");
        bestFitness = minus_infinity;
        worstFitness = infinity;
        break;
    case Constraint::NKlandscape:
        strcpy(type, "nk");
        bestFitness = minus_infinity;
        worstFitness = infinity;
        break;
    case Constraint::Deceptive:
        strcpy(type, "deceptive");
        bestFitness = minus_infinity;
        worstFitness = infinity;
        break;

    case Constraint::Sphere:
        strcpy(type, "sphere");
        break;
    case Constraint::Schwefel:
        strcpy(type, "schwefel");
        break;
    case Constraint::Rosenbrock:
        strcpy(type, "rosenbrock");
        break;
    case Constraint::Rastrigin:
        strcpy(type, "rastrigin");
        break;
    case Constraint::Minimum_sum:
        strcpy(type, "minimum");
        break;
    }
    for (int i = 0; i < (int)pop.size(); i++)
    {
        Chromosome *chr = pop.at(i);

        /*
          코드의 일관성을 높이기 위해
          Walsh transform + surrogate model을 통한 적합도 계산
          모두 fitness.java와 fitness.py에서 수행
        */

        for (int j = 0; j < chromosome_size; j++)
        {
            char str[20];
            memset(str, 0, sizeof(str));
            sprintf(str, "%.3lf", chr->getChromosome(j));

            if (j != chromosome_size - 1)
                strcat(str, ",");
            strcat(everySol, str);
        }

        if (i != pop.size() - 1)
            strcat(everySol, "/");
    }
    bool TensorFlow = false; // else WEKA
    /*
    if (constraintType._function == Constraint::NKlandscape)
    {
        for (int i = 0; i < chromosome_size; i++)
            delete constraintType.landscape[i];
        delete constraintType.landscape;
    }
    */

    // everySol : 0.3,2.1,3.2,-0.34/0.31,-4.3,1.32,-0.32
    // chromosome_size : 4
    // type : rastrigin
    if (TensorFlow)
        sprintf(toParser, "python3 fitness.py --solution [%s] --genes %d --type %s --transformOrNot %d", everySol, chromosome_size, type, transformOrNot);
    else
    {
        if(constraintType._function == Constraint::NKlandscape) // the value of k and machine learning algorithm
            sprintf(toParser, "java fitness %s %s %d %d %s %s", everySol, type, chromosome_size, 1, "walsh", "svr");
            // 현재 코드는 NK landscape만이 바이너리 인코딩 문제이다. 
        else
        {
            sprintf(toParser, "java -cp $CLASSPATH:/home/dong/jar/* fitness %s %s %d %d %s %s", everySol, type, chromosome_size, -1, "fourier", "rbfn");
        }
    }
    system(toParser);

    FILE *fp = fopen("result", "r");
    for (int i = 0; i < (int)pop.size(); i++)
    {
        double fitness = 0.0;
        fscanf(fp, "%lf", &fitness);
        Chromosome *chr = pop.at(i);
        chr->setFitness(fitness);

        totalFitness += fitness;
        if (i == 0)
        {
            bestFitness = fitness;
            worstFitness = fitness;
        }
        if (constraintType._function == Constraint::Rastrigin || constraintType._function == Constraint::Sphere || constraintType._function == Constraint::Rosenbrock || constraintType._function == Constraint::Schwefel || constraintType._function == Constraint::Minimum_sum)
        {
            if (fitness < bestFitness)
            {
                bestFitness = fitness;
                bestFitnessIndex = i;
                bestChromosome = chr;
            }
            if (fitness > worstFitness)
            {
                worstFitness = fitness;
                worstFitnessIndex = i;
                worstChromosome = chr;
            }
        }
        else
        {
            if (fitness > bestFitness)
            {
                bestFitness = fitness;
                bestFitnessIndex = i;
                bestChromosome = chr;
            }
            if (fitness < worstFitness)
            {
                worstFitness = fitness;
                worstFitnessIndex = i;
                worstChromosome = chr;
            }
        }
    }
    fclose(fp);
    *aveFitness = totalFitness / (int)pop.size();
    *bestIdx = bestFitnessIndex;
    *worstIdx = worstFitnessIndex;

    return bestFitness;
}

// Evaluate the population fitnesses
double Population::EvaluatePopulation(Chromosome *bestChromosome, Chromosome *worstChromosome, int *bestIdx, int *worstIdx, double* aveFitness)
{
    double totalFitness = 0.0;
    double bestFitness = infinity;
    double worstFitness = minus_infinity;
    int bestFitnessIndex = 0;
    int worstFitnessIndex = 0;

    switch (constraintType._function)
    {
    case Constraint::Onemax:
    case Constraint::Royalroad:
    case Constraint::NKlandscape:
    case Constraint::Deceptive:
        bestFitness = minus_infinity;
        worstFitness = infinity;
    }

    for (int i = 0; i < (int)pop.size(); i++)
    {
        double fitness = CalcChromosomeFitness(i);
        Chromosome *chr = pop.at(i);
        chr->setFitness(fitness);

        totalFitness += fitness;
        if (i == 0)
        {
            bestFitness = fitness;
            worstFitness = fitness;
        }
        if (constraintType._function == Constraint::Rastrigin || constraintType._function == Constraint::Sphere || constraintType._function == Constraint::Rosenbrock || constraintType._function == Constraint::Schwefel || constraintType._function == Constraint::Minimum_sum) // minimization problem
        {
            if (fitness < bestFitness)
            {
                bestFitness = fitness;
                bestFitnessIndex = i;
                bestChromosome = chr;
            }
            if (fitness > worstFitness)
            {
                worstFitness = fitness;
                worstFitnessIndex = i;
                worstChromosome = chr;
            }
        }

        else // maximization problem 
        {
            if (fitness > bestFitness)
            {
                bestFitness = fitness;
                bestFitnessIndex = i;
                bestChromosome = chr;
            }
            if (fitness < worstFitness)
            {
                worstFitness = fitness;
                worstFitnessIndex = i;
                worstChromosome = chr;
            }
        }
    }
    *aveFitness = totalFitness / (int)pop.size();
    *bestIdx = bestFitnessIndex;
    *worstIdx = worstFitnessIndex;
    return bestFitness;
}

// Create an arbitrary random chromosome
Chromosome *Population::CreateRandomChromosome_real()
{
    Chromosome *chr = new Chromosome(chromosome_size);

    for (int i = 0; i < chr->GetSize(); i++)
    {
        double value = rand() / (double(RAND_MAX) + 1) * constraintType.max;
        if (rand() % 2 == 1)
            value = value * -1;
        // constraintType.max와 constraintType.min이 부호만 다르기 때문에
        chr->setChromosome(i, value);
    }
    return chr;
}
Chromosome *Population::CreateRandomChromosome_bin()
{
    Chromosome *chr = new Chromosome(chromosome_size);

    for (int i = 0; i < chr->GetSize(); i++)
    {
        int value;
        if (rand() % 2 == 1)
            value = 1;
        else
            value = 0;

        chr->setChromosome(i, value);
    }
    return chr;
}
double Population::CalculateFitnessFunction(const Chromosome &chr)
{
    return constraintType.Fitness(chr);
    //return constraintType.Fitness_with_noise(chr);
    // 이 부분을 Fitness()로 하면 noise가 섞이지 않은 적합도가 반환된다.
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
