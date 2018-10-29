// GAfunction.cpp : Defines the entry point for the console application.
/* 
������ RGA�� extended box crossover, gaussian mutation �����Ѵ�.
������ GA���� ����ü�� ���յ��� ���� �� ����� ���´�.
���յ��� ���ϴ� �Լ��� ���̽� ���� �ٸ���.
*/
#include "GeneticAlgorithm.h"
#include <string>
const int crossover_rate = 50;
const int extension_rate = 5;
// For extended-box Crossover, alpha is extension rate
const int mutation_rate = 2;
// For Gaussian mutation, sd is fixed to (upper - lower) / 10
const int population_size = 20;
const int number_iterations = 20;
const int chromosome_size = 20;
const int tournament_size = population_size / 10;
const int precision = 6;
const int epoch = 50;
const std::string path = "C:\\Users\\dongpilYu\\Desktop\\vscode\\RealCodedGA\\best.txt";

int main(int argc, char **argv)
{
    GeneticAlgorithm ga;

    Constraint constraint = Constraint::Rastrigin;
    ga.Initialize(crossover_rate, extension_rate, mutation_rate, population_size, number_iterations, chromosome_size, tournament_size, precision, epoch, path, constraint);
    ga.Run();

    return 0;
}
