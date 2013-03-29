#include "Cache.h"
#include <iostream>

using namespace std;

int main(){



	//TEST 1********************************************************
	
	// Create a cache	
	Cache* cache = new Cache(4, 8, 2, 1);

	//Initialize "time" variables
	int totalTime = 0;
	int time;

	//get times for 0-15
	for(int i = 0; i < 16; i++) {
		time = cache->simulateRead(i);
		totalTime += time;
	}

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();

	//Output times for test 1
	cout << "Time for test #1:  " << totalTime << endl;

	//Delete and recreate our cache
	delete cache;
	cache = new Cache(4, 8, 2, 1);
	totalTime = 0;



	//TEST 2********************************************************	

	//Test 0, 8, 1, 9
	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;
	time = cache->simulateRead(1);
	totalTime += time;
	time = cache->simulateRead(9);
	totalTime += time;

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();

	//Output the result
	cout << "Time for test #2:  " << totalTime << endl;

	//Delete and recreate the cache 
	delete cache;	
	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;



	//Test 3********************************************************
	
	//March through 0-15 and get times with new cache
	for(int i = 0; i < 16; i++) {
		time = cache->simulateRead(i);
		totalTime += time;
	}

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();

	//output results
	cout << "Time for test #3:  " << totalTime << endl;

	//delete and recreate cache
	delete cache;
	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;



	//TEST 4********************************************************
	
	//Go through 0, 8, 1, 9
	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;
	time = cache->simulateRead(1);
	totalTime += time;
	time = cache->simulateRead(9);
	totalTime += time;

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();

	//Output results
	cout << "Time for test #4:  " << totalTime << endl;

	//delete and recreate cache
	delete cache;
	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;



	//Test 5********************************************************
	
	//Go through values 0, 4, 8, 0
	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateRead(4);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;
	time = cache->simulateRead(0);
	totalTime += time;

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();

	//Output result
	cout << "Time for test #5:  " << totalTime << endl;

	//Delete and recreate cache
	delete cache;
	cache = new Cache(4, 8, 2, 2);
	totalTime = 0;



	//TEST 6********************************************************
	
	//Read 0, write 0, read 4 and 8	
	time = cache->simulateRead(0);
	totalTime += time;
	time = cache->simulateWrite(0);
	totalTime += time;
	time = cache->simulateRead(4);
	totalTime += time;
	time = cache->simulateRead(8);
	totalTime += time;

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();

	//Output time
	cout << "Time for test #6:  " << totalTime << endl;

	//Delete and recreate cache
	delete cache;
	cache = new Cache(16, 256, 16, 4);
	totalTime = 0;
	


	//TEST 7********************************************************
	
	//March through 0..8192 reading and writing by 1s and get time
	for(int i = 0; i < 8192; i++) {
		time = cache->simulateRead(i);
		totalTime += time;
		
		time = cache->simulateWrite(i);
		totalTime += time;
	}

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();
		
	//output result
	cout << "Time for test #7:  " << totalTime << endl;
	
	//Delete and recreate cache
	delete cache;
	cache = new Cache(16, 256, 16, 4);
	totalTime = 0;



	//TEST 8********************************************************
	
	//March through 0..8192 by 16s reading and writing 
	for(int i = 0; i < 8192; i += 16) {
		time = cache->simulateRead(i);
		totalTime += time;

		time = cache->simulateWrite(i);
		totalTime += time;
	}

	//Count the dirty spots in cache
	totalTime += cache->getNumDirtyBlocks();
	
	//output result
	cout << "Time for test #8:  " << totalTime << endl;
	
	//delete the cache
	delete cache;

}
