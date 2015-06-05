all: b1 b2 b3

btAlignedAllocator.o: btAlignedAllocator.h btAlignedAllocator.cpp
	g++ -c -o btAlignedAllocator.o btAlignedAllocator.cpp
	
benchmark.o: benchmark.cpp
	g++ -c -std=c++0x -o benchmark.o benchmark.cpp

b1: benchmark.o btAlignedAllocator.o
	g++ -o b1 btAlignedAllocator.o benchmark.o

benchmarkII.o: benchmarkII.cpp
	g++ -c -std=c++0x -o benchmarkII.o benchmarkII.cpp
	
b2: benchmarkII.o btAlignedAllocator.o
	g++ -o b2 btAlignedAllocator.o benchmarkII.o
	
benchmarkIII.o: benchmarkIII.cpp
	g++ -c -std=c++0x -o benchmarkIII.o benchmarkIII.cpp

b3: benchmarkIII.o btAlignedAllocator.o
	g++ -o b3 btAlignedAllocator.o benchmarkIII.o

clean:
	rm *.o res* b1 b2 b3
	