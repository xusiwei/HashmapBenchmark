#include "btHashMap.h"
#include "getCPUTime.h"

// #include <ctime>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <assert.h>

#include <string>
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

char* readfile(const char* filename, int* plen)
{
	std::FILE* fin = fopen(filename, "r");
	assert(fin);
	
	int ret = fseek(fin, 0, SEEK_END);
	assert(!ret);
	
	long size = ftell(fin);
	assert(size >= 0);
	
	rewind(fin);
	
	char* buffer = (char*)malloc(size + 1);
	long readed = fread(buffer, 1, size, fin);
	// prinf("readed: %d, size: %d\n", readed, size);
	buffer[size] = 0;
	assert(readed == size);
	
	if(plen) *plen = static_cast<int>(size);
	fclose(fin);
	return buffer;
}

// took a word from text.
// @return int, number of chars scaned on the text.
int took(const char* text, char* word, int* plen)
{
	int count = 0;
	const char* p = text;
	
	while(*p && !isalpha(*p)) p++;  // ignore prefix non alpha chars.
	for( ; *p; p++) {
		if(isalpha(*p)) word[count++] = *p;
		else break;
	}
	word[count++] = '\0';
	// printf("took: %s\n", word);
	if(plen) *plen = count;
	return p - text;
}

void btBench(const char* text, int length)
{
	btHashMap<btHashString, btHashInt> btDict;
	
	int count = 0;
	int cursor = 0;
	char word[256];
	
	timer t;
	do {
		int wlen = 0;
		cursor += took(&text[cursor], word, &wlen);
		if(!word[0]) break;
		
		count++;
		
		btHashString key(word);
		btHashInt* val = btDict.find(key);
		if(val != NULL) {
			val->setUid1(val->getUid1() + 1);
		}
		else {
			btDict.insert(key, btHashInt(1));
		}
	}while(cursor < length);
	double timeUsed = t.elapsed();
	
	printf("%9s: time used: %.3f, word tooks: %d\n", __func__, timeUsed, count);
}

void stdBench(const char* text, int length)
{
	std::unordered_map<std::string, int> dict;
	
	int count = 0;
	int cursor = 0;
	char word[256];
	
	timer t;
	do {
		int wlen = 0;
		cursor += took(&text[cursor], word, &wlen);
		if(!word[0]) break;
		
		count++;
		
		// insert to dict.
		auto pos = dict.find(word);
		if(pos != dict.end()) {
			pos->second++;
		}
		else {
			dict.insert(std::make_pair(word, 1));
		}
	}while(cursor < length);
	double timeUsed = t.elapsed();
	
	printf("%9s: time used: %.3f, word tooks: %d\n", __func__, timeUsed, count);
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return -1;
	}

	int len = 0;
	char* text = readfile(argv[1], &len);
	
	stdBench(text, len);
	
	btBench(text, len);
	return 0;
}
