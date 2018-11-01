# Written by
* dongpilYu (https://github.com/dongpilYu/Real-Encoding-GA)
* programming with C++
* g++ compiler

# Real Valued Encoding GA
* Parameters
    * ```Extended Box Crossover``` : Extension rate : 0.5, Crossover rate : 0.5
    * ```Gaussian Mutation``` : Mutation rate : 0.02
    * ```Tournament Selection``` : Tourament size : Population size / 10
* Problems
    * ```Shifted Rosenbrock``` :
    * ```Shifted Sphere``` :
    * ```Shifted Schwefel``` :
    * ```Shifted Rasrigin``` :

# Binary Valued Encoding GA
* Parameters
    * ```One-Point Crossover``` : Crossover rate : 0.5
    * ```Bitwise Mutation``` :  Mutation rate : 0.02
    * ```Tournament Selection``` : Tourament size : Population size / 10
* Problems
    * ```One Max``` :
    * ```Royal Road``` :
    * ```NK Landscape``` :
    * ```Deceptive problem``` :


# How to
* Build - Debug
```shell
g++ GAfunction.cpp GeneticAlgorithm.cpp Chromosome.cpp Population.cpp Log.cpp -o GAfunction.exe -g
```
* Build - Release
```shell
g++ GAfunction.cpp GeneticAlgorithm.cpp Chromosome.cpp Population.cpp Log.cpp -o GAfunction.exe
```
* Execute
```shell
GAfunction.exe [Real valued or not] [chromosome size] [population size]
[number iterations] [problem type] [crossover rate] [mutation rate] [royal number] [num_k]
```
 ```[Real valued or not]``` - 0, 1 (0 : Real, 1 : Binary)<br>
 ```[chromosome size]``` - integer<br>
 ```[population size]``` - integer<br>
 ```[number iterations]``` - integer<br>
 ```[problem type]``` - 1 ~ 8 <br>
 (Respectively Rosenbrock, Sphere, Schwefel, Rastrigin, Onemax, Royalroad, NKlandscape, Deceptive problem)<br>
 ```[crossover rate]``` - 0 ~ 100<br>
 ```[mutation rate]``` - 0 ~ 100<br>
 ```[royal number]``` - when using royal road problem, we need royal number<br>
 ```[num_k]``` - when using NK landscape problem, we need num of k<br>

 You must specify 9 parameters.<br>
 You must set num_k and royal number even if you do not use NK landscape problem and Royal road problem
