// GAfunction.cpp : Defines the entry point for the console application.
/*
������ RGA�� extended box crossover, gaussian mutation �����Ѵ�.
������ GA���� ����ü�� ���յ��� ���� �� ����� ���´�.
���յ��� ���ϴ� �Լ��� ���̽� ���� �ٸ���.
*/
#include "GeneticAlgorithm.h"

const int precision = 6;
const int epoch = 10;
const std::string path = "Log.txt";

Constraint typeOfProblem(const int &problem_type);

int main(int argc, char **argv)
{
    const int binaryOrNot = atoi(argv[1]); // real encoding - 0, binary encoding - 1
    const int chromosome_size = atoi(argv[2]);
    const int population_size = atoi(argv[3]);
    const int tournament_size = population_size / 10;
    const int number_iterations = atoi(argv[4]);
    const int problem_type = atoi(argv[5]);
    const int crossover_rate = atoi(argv[6]);
    const int extension_rate = 50;           // For extended-box Crossover
    const int mutation_rate = atoi(argv[7]); // For Gaussian mutation, SD is fixed to (upper - lower) / 10
    const int royal_number = atoi(argv[8]);
    const int num_k = atoi(argv[9]);

    GeneticAlgorithm ga;
    Constraint constraint = typeOfProblem(problem_type);

    ga.Initialize(binaryOrNot, problem_type, royal_number, num_k, crossover_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch, path, constraint);
    ga.Run();

    return 0;
}
Constraint typeOfProblem(const int &problem_type)
{
    switch (problem_type)
    {
    case 1:
        return Constraint::Rosenbrock;
    case 2:
        return Constraint::Sphere;
    case 3:
        return Constraint::Schwefel;
    case 4:
        return Constraint::Rastrigin;
    case 5:
        return Constraint::Onemax;
    case 6:
        return Constraint::Royalroad;
    case 7:
        return Constraint::NKlandscape;
    case 8:
        return Constraint::Deceptive;
    }
};
