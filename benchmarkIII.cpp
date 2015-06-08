#include "btHashMap.h"
#include "getCPUTime.h"

#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstdlib>

#include <unordered_map>

class timer
{
 public:
         timer() { _start_time = getCPUTime(); } // postcondition: elapsed()==0
  void   restart() { _start_time = getCPUTime(); } // post: elapsed()==0
  double elapsed() const                  // return elapsed time in seconds
    { return  getCPUTime() - _start_time; }

 private:
  double _start_time;
}; // timer

btHashMap<btHashInt, btHashInt> btDict;
std::unordered_map<int, int> stdDict;

double btInsertBench(int seed, long tests)
{
	srand(seed);
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		btDict.insert(btHashInt(rand()), btHashInt(1));
	}
	return t.elapsed();
}

double btFindBench(int seed, long tests)
{
	srand(seed);
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		btDict.find(btHashInt(rand()));
	}
	return t.elapsed();
}

double stdInsertBench(int seed, long tests)
{
	srand(seed);
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		stdDict.insert(std::make_pair(rand(), 1));
	}
	return t.elapsed();
}

double stdFindBench(int seed, long tests)
{
	srand(seed);
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		stdDict.find(rand());
	}
	return t.elapsed();	
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage: %s tests\n", argv[0]);
		return -1;
	}
	
	int tests = atoi(argv[1]);
	int seed = time(NULL);
	
	double stdInsertTime = stdInsertBench(seed, tests);
	double stdFindTime   = stdFindBench(seed, tests);
	
	double btInsertTime = btInsertBench(seed, tests);
	double btFindTime   = btFindBench(seed, tests);
	
	printf("%11d\t% 5.3f\t% 5.3f\t% 5.3f\t% 5.3f\n", tests, stdInsertTime, stdFindTime, btInsertTime, btFindTime);
	return 0;
}
