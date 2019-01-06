#pragma once
#define _USE_MATH_DEFINES
#include "Chromosome.h"
#include <cmath>
#include <random>

struct Constraint
{
    double max = 0, min = 0;
    Chromosome *optimalSol;

    int num_k = 0, royal_number = 0;
    double **landscape;
    bool nk_first = true;
    // max, min, optimalSol은 실수 인코딩 문제를 위한 부분
    // 바이너리 인코딩 문제라면, 0, 0, NULL인 상태를 유지한다.
    // 마찬가지로, num_k, landscape, nk_first, royal_number는
    // 바이너리 인코딩 문제를 위한 부분으로
    // 실수 인코딩 문제라면 0, 0, NULL, true인 상태를 유지한다.

    enum Function
    {
        Rosenbrock,
        Sphere,
        Schwefel,
        Rastrigin,
        Onemax,
        Royalroad,
        NKlandscape,
        Deceptive,
        Minimum_sum
    };

    Function _function;
    Constraint(void) {}
    ~Constraint(void) {}
    Constraint(Function f) : _function(f)
    {
        switch (_function)
        {
        case Rosenbrock:
            max = 5;
            min = -5;
            break;
        case Sphere:
            max = 5;
            min = -5;
            break;
        case Schwefel:
            max = 5;
            min = -5;
            break;
        case Rastrigin:
            max = 5;
            min = -5;
            break;
        case Minimum_sum:
            max = 5;
            min = -5;
            break;
        default:
            break;
        }
    }
    // 초기화 하는 과정에서 한번만 호출되야 한다.
    Chromosome *Make_optimal_solution(const int &chromosome_size)
    {
        optimalSol = new Chromosome(chromosome_size);
        for (int i = 0; i < chromosome_size; i++)
        {
            /*
            double value = rand() / (double(RAND_MAX) + 1) * max;
            if (rand() % 2 == 1)
                value = value * -1;
            optimalSol->setChromosome(i, value);
            */
            optimalSol->setChromosome(i, 0);
        }
        // optimalSol->setChromosomeSize(chromosome_size);
        // optimalSol은 적합도와 염색체 크기 필드가 비워져 있다.
        return optimalSol;
    }
    double Fitness_with_noise(const Chromosome &chr)
    {
        double fitness = Fitness(chr);
        double fitness_with_noise = 0.0;
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0, 0.1);
        fitness_with_noise = fitness + distribution(generator);

        return fitness_with_noise;
    }
    double Fitness(const Chromosome &chr)
    {
        switch (_function)
        {
        /* Real encoding problems */
        case Rosenbrock:
            return rosenbrock(chr);
        case Sphere:
            return sphere(chr);
        case Schwefel:
            return schwefel(chr);
        case Rastrigin:
            return rastrigin(chr);

        /* Binary encoding problems */
        case Onemax:
            return onemax(chr);
        case Royalroad:
            return royalroad(chr);
        case NKlandscape:
            return nk(chr);
        case Deceptive:
            return deceptive(chr);

        case Minimum_sum:
            return minimum_sum(chr);
        }
    }
    void setParms(const int &num_k, const int &royal_number)
    {
        this->num_k = num_k;
        this->royal_number = royal_number;
    }
    double rosenbrock(const Chromosome &chr)
    {
        double fitness = 0.0;

        for (int i = 0; i < chr.GetSize() - 1; i++)
        {
            double diff1 = chr.getChromosome(i) - optimalSol->getChromosome(i);
            double diff2 = chr.getChromosome(i + 1) - optimalSol->getChromosome(i + 1);
            fitness += 100 * pow((pow(diff1 + 1, 2) - (diff2 + 1)), 2) + pow(diff1, 2);
        }
        return fitness + 390.0;
    }
    double sphere(const Chromosome &chr)
    {
        double fitness = 0.0;

        for (int i = 0; i < chr.GetSize(); i++)
        {
            double diff = chr.getChromosome(i) - optimalSol->getChromosome(i);
            fitness += pow(diff, 2);
        }
        return fitness - 450.0;
    }
    double schwefel(const Chromosome &chr)
    {
        double fitness = 0.0;

        for (int i = 0; i < chr.GetSize(); i++)
        {
            double val = 0.0;
            for (int j = 0; j <= i; j++)
            {
                double diff = chr.getChromosome(j) - optimalSol->getChromosome(j);
                val += diff;
            }
            fitness += pow(val, 2);
        }
        return fitness - 450.0;
    }
    double rastrigin(const Chromosome &chr)
    {
        double fitness = 0.0;

        for (int i = 0; i < chr.GetSize(); i++)
        {
            double diff = chr.getChromosome(i) - optimalSol->getChromosome(i);
            fitness += (pow(diff, 2) - 10 * cos(2 * M_PI * diff) + 10);
        }
        return fitness - 330.0;
    }
    double minimum_sum(const Chromosome &chr)
    {
        double fitness = 0.0;
        for (int i = 0; i < chr.GetSize(); i++)
            fitness += chr.getChromosome(i);
        return fitness;
    }
    double onemax(const Chromosome &chr)
    {
        double fitness = 0.0;
        for (int i = 0; i < chr.GetSize(); i++)
            fitness += chr.getChromosome(i);
        return fitness;
    }
    double royalroad(const Chromosome &chr)
    {
        double fitness = 0.0;
        for (int i = 0; i < chr.GetSize() / royal_number; i++)
        {
            bool sol = true;
            for (int j = 0; j < royal_number; j++)
                if (chr.getChromosome(royal_number * i + j) != 1)
                {
                    sol = false;
                    break;
                }
            if (true == sol)
                fitness += royal_number;
        }
        return fitness;
    }
    double nk(const Chromosome &chr)
    {
        if (true == nk_first)
        {
            int powerOfK = pow(num_k, 2);
            landscape = new double *[chr.GetSize()];
            for (int i = 0; i < chr.GetSize(); i++)
                landscape[i] = new double[powerOfK * 2];

            for (int i = 0; i < chr.GetSize(); i++)
            {
                for (int j = 0; j < powerOfK * 2; j++)
                    landscape[i][j] = ((double)rand() / RAND_MAX);
            }
            nk_first = false;
        }
        else
        {
            double fitness = 0.0;

            for (int i = 0; i < chr.GetSize(); i++)
            {
                int binary = 0;
                int k = num_k;

                for (int j = 0; j < num_k + 1; j++)
                {
                    int num = 0;
                    if (i + j >= chr.GetSize())
                        num = (i + j) % chr.GetSize();
                    else
                        num = i + j;
                    binary += (chr.getChromosome(num) * pow(k, 2));
                    k--;
                }
                fitness += landscape[i][binary];
            }
            return fitness;
        }
    }

    double deceptive(const Chromosome &chr)
    {
        double fitness = 0.0;
        for (int i = 0; i < chr.GetSize(); i++)
            fitness += chr.getChromosome(i);

        if (fitness == chr.GetSize())
            return 0;
        else
            return fitness - 1;
        return fitness;
    }
};
