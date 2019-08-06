make
#javac -cp $CLASSPATH fitness.java

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
