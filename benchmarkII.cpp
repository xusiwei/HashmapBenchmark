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

double btBench(int seed, long tests)
{
	btHashMap<btHashInt, btHashInt> dict;
	
	srand(seed); // setup random seed.
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		int r = rand(); // generate random int.

		// lookup in the hash map.
		btHashInt* val = dict.find(btHashInt(r));
		
		if(val != NULL) { // found, update directly.
			val->setUid1(val->getUid1() + 1);
		}
		else { // not found, insert <key, 1>
			dict.insert(btHashInt(r), btHashInt(1));
		}
	}
	return t.elapsed();
}

double stdBench(int seed, long tests)
{
	std::unordered_map<int, int> dict;
	
	srand(seed); // setup random seed.
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		int r = rand(); // generate random int.
		
		auto it = dict.find(r); // lookup.
		
		if(it != dict.end()) { // found
			++it->second;
		}
		else { // not found
			dict.insert(std::make_pair(r, 1));
		}
	}
	return t.elapsed();
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage: %s tests\n", argv[0]);
		return -1;
	}
	
	long tests = atol(argv[1]);
	int seed = time(NULL);
	
	double stdTime = stdBench(seed, tests);
	double btTime = btBench(seed, tests);
	
	printf("%11d\t% 5.3f\t% 5.3f\n", tests, stdTime, btTime);
	return 0;
}
