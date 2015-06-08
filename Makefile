all: b1 b2 b3

getCPUTime.o: getCPUTime.c getCPUTime.h
	g++ -c -o getCPUTime.o getCPUTime.c

btAlignedAllocator.o: btAlignedAllocator.h btAlignedAllocator.cpp
	g++ -c -o btAlignedAllocator.o btAlignedAllocator.cpp
	
benchmark.o: benchmark.cpp
	g++ -c -std=c++0x -o benchmark.o benchmark.cpp

b1: benchmark.o btAlignedAllocator.o getCPUTime.o
	g++ -o b1 getCPUTime.o btAlignedAllocator.o benchmark.o -lrt

benchmarkII.o: benchmarkII.cpp
	g++ -c -std=c++0x -o benchmarkII.o benchmarkII.cpp
	
b2: benchmarkII.o btAlignedAllocator.o getCPUTime.o
	g++ -o b2 getCPUTime.o btAlignedAllocator.o benchmarkII.o -lrt
	
benchmarkIII.o: benchmarkIII.cpp
	g++ -c -std=c++0x -o benchmarkIII.o benchmarkIII.cpp

b3: benchmarkIII.o btAlignedAllocator.o getCPUTime.o
	g++ -o b3 getCPUTime.o btAlignedAllocator.o benchmarkIII.o -lrt

clean:
	rm *.o res* b1 b2 b3
	