#pragma once
#define _USE_MATH_DEFINES
#include "Chromosome.h"
#include <cmath>
#include <random>

struct Constraint
{
    double max = 0, min = 0;
    int num_k = 0, royal_number = 0;
    Chromosome *optimalSol;
    // max, min, optimalSol은 실수 인코딩 문제를 위한 부분
    // 바이너리 인코딩 문제라면, 0, 0, NULL인 상태를 유지한다.
    // 마찬가지로, num_k 와 royal_number는 바이너리 인코딩 문제를 위한 부분으로
    // 실수 인코딩 문제라면 0, 0인 상태를 유지한다.
    enum Function
    {
        Rosenbrock,
        Sphere,
        Schwefel,
        Rastrigin,
        Onemax,
        Royalroad,
        NKlandscape,
        Deceptive
    };

    Function _function;
    Constraint(void) {}
    Constraint(Function f) : _function(f)
    {
        switch (_function)
        {
        case Rosenbrock:
            max = 100;
            min = -100;
            break;
        case Sphere:
            max = 100;
            min = -100;
            break;
        case Schwefel:
            max = 100;
            min = -100;
            break;
        case Rastrigin:
            max = 5;
            min = -5;
            break;
        default:
            break;
        }
    }
    // 초기화 하는 과정에서 한번만 호출되야 한다.
    void Make_optimal_solution(const int &chromosome_size)
    {
        optimalSol = new Chromosome(chromosome_size);
        for (int i = 0; i < chromosome_size; i++)
        {
            double value = rand() / (double(RAND_MAX) + 1) * max;
            if (rand() % 2 == 1)
                value = value * -1;
            // constraintType.max와 constraintType.min이 부호만 다르기 때문에
            optimalSol->setChromosome(i, value);
        }
    }
    double Fitness_with_noise(const Chromosome &chr)
    {
        double fitness = Fitness(chr);

        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0, 0.1);
        fitness += distribution(generator);

        return fitness;
    }
    double Fitness(const Chromosome &chr)
    {
        double fitness = 0.0;
        switch (_function)
        {
        case Rosenbrock:
            for (int i = 0; i < chr.GetSize() - 1; i++)
            {
                double val1 = chr.getChromosome(i);
                double val2 = chr.getChromosome(i + 1);
                fitness += 100 * pow((pow(val1 + 1, 2) - (val2 + 1)), 2) + pow(val1, 2);
            }
            return fitness + 390.0;
        case Sphere:
            for (int i = 0; i < chr.GetSize(); i++)
            {
                double val = chr.getChromosome(i);
                fitness += pow(val, 2);
            }
            return fitness - 450.0;
        case Schwefel:
            for (int i = 0; i < chr.GetSize(); i++)
            {
                double val = 0.0;
                for (int j = 0; j <= i; j++)
                    val += chr.getChromosome(j);
                fitness += pow(val, 2);
            }
            return fitness - 450.0;
        case Rastrigin:
            for (int i = 0; i < chr.GetSize(); i++)
            {
                double val = chr.getChromosome(i);
                fitness += (pow(val, 2) - 10 * cos(2 * M_PI * val) + 10);
            }
            return fitness - 330.0;

        /* Binary encoding problems */
        case Onemax:
            for (int i = 0; i < chr.GetSize(); i++)
                fitness += chr.getChromosome(i);
            return fitness;
        case Royalroad:
            for (int i = 0; i < chr.GetSize() / royal_number; i++)
            {
                bool sol = true;
                for (int j = 0; j < royal_number; j++)
                    if (chr.getChromosome(i + j) != 1)
                    {
                        sol = false;
                        break;
                    }
                if (true == sol)
                    fitness += royal_number;
            }
            return fitness;
        case NKlandscape:
            return fitness;
        case Deceptive:
            for (int i = 0; i < chr.GetSize(); i++)
                fitness += chr.getChromosome(i);

            if (fitness == chr.GetSize())
                return 0;
            else
                return fitness - 1;
        }
    }
    void setParms(const int &num_k, const int &royal_number)
    {
        this->num_k = num_k;
        this->royal_number = royal_number;
    }
};
