CC = g++
TARGET = GAfunction.exe
FLAGS = -std=c++11
OBJECTS = GAfunction.o GeneticAlgorithm.o Chromosome.o Population.o Log.o

$(TARGET) : $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^

GAfunction.o : GAfunction.cpp 
	$(CC) $(FLAGS) -c -o GAfunction.o GAfunction.cpp 
GeneticAlgorithm.o : GeneticAlgorithm.cpp
	$(CC) $(FLAGS) -c -o GeneticAlgorithm.o GeneticAlgorithm.cpp 
Population.o : Population.cpp 
	$(CC) $(FLAGS) -c -o Population.o Population.cpp 
Chromosome.o : Chromosome.cpp
	$(CC) $(FLAGS) -c -o Chromosome.o Chromosome.cpp 
Log.o : Log.cpp
	$(CC) $(FLAGS) -c -o Log.o Log.cpp 

clean :
	rm *.o $(TARGET)
