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
	
	srand(seed);
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		// generate random int.
		int r = rand();
		// printf("generated: %d\n", r);
		btHashInt key(r);

		// lookup in the hash map.
		btHashInt* val = dict.find(key);
		
		if(val != NULL) { // found, update directly.
			val->setUid1(val->getUid1() + 1);
		}
		else { // 
			dict.insert(key, btHashInt(1));
		}
	}
	return t.elapsed();
}

double stdBench(int seed, long tests)
{
	typedef std::unordered_map<int, int> stdMap;
	stdMap dict;
	
	srand(seed);
	
	timer t;
	for(long i = 0; i < tests; ++i) {
		// generate random int.
		int r = rand();
		// printf("generated: %d\n", r);
		
		// insert to dict.
		stdMap::iterator it = dict.find(r);
		if(it != dict.end()) {
			++it->second;
		}
		else {
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
	
	int tests = atoi(argv[1]);
	int seed = time(NULL);
	
	double stdTime = stdBench(seed, tests);
	double btTime = btBench(seed, tests);
	
	printf("%11d\t% 5.3f\t% 5.3f\n", tests, stdTime, btTime);
	return 0;
}
