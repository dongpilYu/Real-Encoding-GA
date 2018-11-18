
for idx in 4 5 6 7 8 20 25 50 100
do
	./GAfunction.exe 0 $idx 300 300 1 50 2 -1 -1 rosenbrock$idx.txt
	./GAfunction.exe 0 $idx 300 300 2 50 2 -1 -1 sphere$idx.txt
	./GAfunction.exe 0 $idx 300 300 3 50 2 -1 -1 schwefel$idx.txt
	./GAfunction.exe 0 $idx 300 300 4 50 2 -1 -1 rastrigin$idx.txt
done
