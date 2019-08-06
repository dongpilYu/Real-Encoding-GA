# Written by
* dongpilYu (https://github.com/dongpilYu/Real-Encoding-GA)

# Requirements
* C++ 11 or later
* g++ compiler 6.3.0
* GNU Make 4.1
* git 2.7.4

# Real Valued Encoding GA
* Parameters
    * ```Extended Box Crossover``` : Extension rate : 0.5, Crossover rate : 0.5
    * ```Gaussian Mutation``` : Mutation rate : 0.02, Mean : 0, Standard deviation : (Upper bound - Lower bound) / 10
    * ```Tournament Selection``` : Tourament size : Population size / 10
    * ```Steady state genetic algorithm```
    * ```Elitism```
* Problems
    * ```Shifted Rosenbrock``` : A non-convex function
    * ```Shifted Sphere``` : A continuous, convex and unimal function
    * ```Shifted Schwefel``` : A complex function with many local minima
    * ```Shifted Rastrigin``` : A typical example of non-linear multimodal function

# Binary Valued Encoding GA
* Parameters
    * ```One-Point Crossover``` : Crossover rate : 0.5
    * ```Bitwise Mutation``` :  Mutation rate : 0.02
    * ```Tournament Selection``` : Tourament size : Population size / 10
    * ```Steady state genetic algorithm```
    * ```Elitism```
* Problems
    * ```One Max```
    * ```Royal Road```
    * ```NK Landscape```
    * ```Deceptive problem```

# How to
* Clone
```shell
git clone https://github.com/dongpilYu/Real-Encoding-GA.git
```
* Build
```shell
make
```
* Execute
```shell
./GAfunction.exe [Real valued or not] [chromosome size] [population size]
[number iterations] [problem type] [crossover rate] [mutation rate] [royal number] [num_k]
```
* Comment<br>
 ```[binary valued or not]``` - 0, 1 (0 : Real, 1 : Binary)<br>
 ```[chromosome size]``` - integer > 0<br>
 ```[population size]``` - integer > 0<br>
 ```[number iterations]``` - integer > 0<br>
 ```[problem type]``` - 1 ~ 8 <br>Respectively Rosenbrock, Sphere, Schwefel, Rastrigin, Onemax, Royalroad, NKlandscape, Deceptive problem<br>
    Real valued problem : Rosenbrock, Sphere, Schwefel, Rastrigin<br>
    Binary valued problem : Onemax, Royalroad, NKlandscape, Deceptive problem<br>
 ```[crossover rate]``` - 0 ~ 100<br>
 ```[mutation rate]``` - 0 ~ 100<br>
 ```[royal number]``` - when using royal road problem, program needs royal number<br>
 ```[num_k]``` - when using NK landscape problem, program needs num of k<br>


    ```1. You must specify 9 parameters.```<br>
    ```2. You must set num_k and royal number even if you do not use NK landscape problem and Royal road problem (set unnecessary parameters to -1)```<br>
    ```3. If you use NK landscape, [num_k] must be less than [chromosome size]```<br>
    ```4. If you use Royal road, [royal number] must be divisor of [chromosome size]```<br>
    ```5. If you set [Binary valued or not] to 0, then [problem type] must be smaller than 5 (1,2,3,4)```<br>
    ```6. If you set [Binary valued or not] to 1, then [problem type] must be larger than 4 (5,6,7,8)```<br>
* Example
```shell
./GAfunction.exe 0 20 100 10000 1 50 2 -1 -1
# Real valued problem, Shifted Rosenbrock problem

./GAfunction.exe 1 40 160 20000 5 50 2 -1 -1
# Binary valued problem, One Max problem

./GAfunction.exe 1 50 200 30000 6 50 3 2 -1
# Binary valued problem, Royal road problem (royal number = 2)

./GAfunction.ese 1 60 50 40000 7 40 2 -1 3
# Binary valued problem, NK Landscape problem (num_k = 3)
```
