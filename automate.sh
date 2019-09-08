make
javac -cp $CLASSPATH:/home/dong/jar/* fitness.java

for i in {1..30}; do

    ./GAfunction.exe 0 2 300 500 2 50 2 -1 -1 "2_sphere_fourier" 0
    ./GAfunction.exe 0 4 300 500 2 50 2 -1 -1 "4_sphere_fourier" 0
    ./GAfunction.exe 0 8 300 500 2 50 2 -1 -1 "8_sphere_fourier" 0

    ./GAfunction.exe 0 2 300 500 3 50 2 -1 -1 "2_schwefel_fourier" 0
    ./GAfunction.exe 0 4 300 500 3 50 2 -1 -1 "4_schwefel_fourier" 0
    ./GAfunction.exe 0 8 300 500 3 50 2 -1 -1 "8_schwefel_fourier" 0

    ./GAfunction.exe 0 2 300 500 4 50 2 -1 -1 "2_rastrigin_fourier" 0
    ./GAfunction.exe 0 4 300 500 4 50 2 -1 -1 "4_rastrigin_fourier" 0
    ./GAfunction.exe 0 8 300 500 4 50 2 -1 -1 "8_rastrigin_fourier" 0



#./GAfunction.exe 0 8 300 500 2 50 2 -1 -1 "8_sphere_fourier" 0
#./GAfunction.exe 0 16 300 500 2 50 2 -1 -1 "16_sphere_fourier" 0
#./GAfunction.exe 0 32 300 500 2 50 2 -1 -1 "24_sphere_fourier" 0

#./GAfunction.exe 0 8 300 500 3 50 2 -1 -1 "8_schwefel_fourier" 0
#./GAfunction.exe 0 16 300 500 3 50 2 -1 -1 "16_schwefel_fourier" 0
#./GAfunction.exe 0 32 300 500 3 50 2 -1 -1 "24_schwefel_fourier" 0

#./GAfunction.exe 0 8 300 500 4 50 2 -1 -1 "8_rastrigin_fourier" 0
#./GAfunction.exe 0 16 300 500 4 50 2 -1 -1 "16_rastrigin_fourier" 0
#./GAfunction.exe 0 32 300 500 4 50 2 -1 -1 "32_rastrigin_fourier" 0
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

: <<'END'
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
