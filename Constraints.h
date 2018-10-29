#pragma once

#include "Chromosome.h"
#include <math.h>

struct Constraint
{
    double max, min;

    enum Function
    {
        Rosenbrock,
        Sphere,
        Schwefel,
        Rastrigin
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
        }
    }
    double Fitness(const Chromosome &chr)
    {
        double fitness = 0.0;
        switch (_function)
        {
        case Rosenbrock:
            return 0;
        case Sphere:
            return 0;
        case Schwefel:
            return 0;
        case Rastrigin:
            return 0;
        }
    }

  private:
    //prevent automatic conversion for any other built-in types such as bool, int, etc
    template <typename T>
    operator T() const;
};
