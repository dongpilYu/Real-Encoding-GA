
for i in 4 5 6 7 8 20 25 50 100
do
    ./GAfunction.exe 0 $i 300 300 1 50 2 -1 -1 rosenbrock$i
    ./GAfunction.exe 0 $i 300 300 1 50 2 -1 -1 sphere$i
    ./GAfunction.exe 0 $i 300 300 1 50 2 -1 -1 schwefel$i
    ./GAfunction.exe 0 $i 300 300 1 50 2 -1 -1 rastrigin$i
done
