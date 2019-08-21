make
javac -cp $CLASSPATH:/home/dong/190806/commons-math3-3.6.1/commons-math3-3.6.1.jar fitness.java

for i in {1..50}
do
    ./GAfunction.exe 0 10 100 500 1 50 2 -1 -1 "10_fourier" 0 
    ./GAfunction.exe 0 15 100 500 1 50 2 -1 -1 "15_fourier" 0 
    ./GAfunction.exe 0 20 100 500 1 50 2 -1 -1 "20_fourier" 0
    
    # problem type 
    # 1 : rosenbrock
    # 2 : sphere
    # 3 : schwefel
    # 4 : rastrigin

    # ./GAfunction.exe 1 25 100 1000 7 50 2 -1 1 "25_1_normal" 0 
    # ./GAfunction.exe 1 50 100 1000 7 50 2 -1 1 "50_1_normal" 0 

done
# binaryOrNot, chromosome_size, population_size, number_iterations, problem_type, crossover_rate, mutation_rate, royal_number, num_k, path, transformOrNot
# not transform - 0
# transform - 1

:<<'END'
for i in 20
do
    for j in {1..50}
    do
    	./GAfunction.exe 0 $i 300 100 1 50 2 -1 -1 rosenbrock$i.txt
    done
    for j in {1..50}
    do
    	./GAfunction.exe 0 $i 300 100 2 50 2 -1 -1 sphere$i.txt
    done
    for j in {1..50}
    do
    	./GAfunction.exe 0 $i 300 100 3 50 2 -1 -1 schwefel$i.txt
    done
    for j in {1..50}
    do
    	./GAfunction.exe 0 $i 300 100 4 50 2 -1 -1 rastrigin$i.txt
    done
done
END
