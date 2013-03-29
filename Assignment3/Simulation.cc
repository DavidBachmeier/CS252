#include "Cache.h"
#include <iostream>

using namespace std;

int main(){
	
	// Create a cache	
	Cache* cache = new Cache(4, 8, 2, 1);

	int totalTime = 0;
	int time;

	for(int i = 0; i < 16; i++) {
		time = cache->simulateRead(i);
		totalTime += time;
	}


	cout << "Time for test #1:  " << totalTime << endl;

	delete cache;



	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;

	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;
	time = cache->simulateRead(1);
	totalTime += time;
	time = cache->simulateRead(9);
	totalTime += time;

	cout << "Time for test #2:  " << totalTime << endl;
	
	delete cache;




	cache = new Cache(4, 8, 2, 1);

	totalTime = 0;
	time;

	for(int i = 0; i < 16; i++) {
		time = cache->simulateRead(i);
		totalTime += time;
	}

	cout << "Time for test #3:  " << totalTime << endl;

	delete cache;




	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;

	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;
	time = cache->simulateRead(1);
	totalTime += time;
	time = cache->simulateRead(9);
	totalTime += time;

	cout << "Time for test #4:  " << totalTime << endl;

	delete cache;




	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;

	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateRead(4);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;
	time = cache->simulateRead(0);
	totalTime += time;

	cout << "Time for test #5:  " << totalTime << endl;

	delete cache;


	
	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;
	
	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateWrite(0);
	totalTime += time;
	time = cache->simulateRead(4);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;

	cout << "Time for test #6:  " << totalTime << endl;

	delete cache;




	cache = new Cache(16, 256, 16, 4);

	totalTime = 0;
	time;

	for(int i = 0; i < 8192; i++) {
		time = cache->simulateRead(i);
		totalTime += time;
		
		time = cache->simulateWrite(i);
		totalTime += time;
	}

	cout << "Time for test #7:  " << totalTime << endl;

	delete cache;
	





	cache = new Cache(16, 256, 16, 4);

	totalTime = 0;
	time;

	for(int i = 0; i < 8192; i += 16) {
		time = cache->simulateRead(i);
		totalTime += time;

		time = cache->simulateWrite(i);
		totalTime += time;
	}

	cout << "Time for test #8:  " << totalTime << endl;

	delete cache;

}
