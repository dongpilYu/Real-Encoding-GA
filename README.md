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
    * ```Shifted Rosenbrock``` : Rosenbrock function is a non-convex function.
    * ```Shifted Sphere``` : Sphere function is a continuous, convex and unimal function
    * ```Shifted Schwefel``` : Schwefel function is a complex function with many local minima.
    * ```Shifted Rastrigin``` : Rasrigin function is a typical example of non-linear multimodal function

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
* Comment<br>
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


    ```You must specify 9 parameters.```<br>
    ```You must set num_k and royal number even if you do not use NK landscape problem and Royal road problem (set unnecessary parameters to 0)```<br>
    ```If you use NK landscape, [num_k] must be less than [chromosome size]```<br>
    ```If you use Royal road, [royal number] must be divisor of [chromosome size]```<br>
    ```If you set [Real valued or not] to 0, then [problem type] must be smaller than 5 (1,2,3,4)```<br>
    ```If you set [Real valued or not] to 1, then [problem type] must be larger than 4 (5,6,7,8)```<br>


 * Example
```shell
GAfunction.exe 0 20 100 10000 1 50 2 0 0
# Real valued problem, Shifted Rosenbrock problem

GAfunction.exe 1 40 160 20000 5 50 2 0 0
# Binary valued problem, One Max problem

GAfunction.exe 1 50 200 30000 6 50 3 2 0
# Binary valued problem, Royal road problem (royal number = 2)

GAfunction.ese 1 60 50 40000 7 40 2 0 3
# Binary valued problem, NK Landscape problem (num_k = 3)
```
