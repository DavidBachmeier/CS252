#include <iostream>
#include <cmath>
#include "Cache.h"

using namespace std;

//Constructor - creates a new cache
Cache::Cache(int m, int c, int b, int e) {
	//Sets instance variables
	physicalAddrBits = m;
	cacheSize = c;
	blockSize = b;
	blocksPerSet = e;

	//Populates the cache with sets
	int i;
	for(i = 0; i < (cacheSize / (blockSize * blocksPerSet)); i++) {
		sets.push_back(new Set(blockSize, blocksPerSet));	
	}
}

//Destructor - recursively deletes the cache
Cache::~Cache() {

	//Deletes every set int the cache before deleting the cache
	int i;
	for(i = 0; i < (cacheSize / (blockSize * blocksPerSet)); i++) {
		delete sets[i];
	}

}

//Simulates an attempted read from the cache
int Cache::simulateRead(unsigned long addr) {

	//Caclucates the number of bits in the address that will be allocated to the set index, the block offset, and the tag
	int numSetIndexBits = log2((cacheSize) / ((blockSize) * (blocksPerSet)));
	int numBlockOffsetBits = log2(blockSize);
	int numTagBits = physicalAddrBits - (numSetIndexBits + numBlockOffsetBits);

	//Extracts the set index and the tag from the address
	unsigned int setIndex = ((addr << numTagBits) & ((unsigned int)pow(2, physicalAddrBits) - 1)) >> (numTagBits + numBlockOffsetBits);
	 
	unsigned int tag = (addr >> (numBlockOffsetBits + numSetIndexBits));

	//Diverts the rest of the work to the set class
	return sets[setIndex]->simulateRead(tag);

}


//Simulates an attempted write to data in the cache
int Cache::simulateWrite(unsigned long addr) {

	//Caclucates the number of bits in the address that will be allocated to the set index, the block offset, and the tag
	int numSetIndexBits = log2((cacheSize) / ((blockSize) * (blocksPerSet)));
	int numBlockOffsetBits = log2(blockSize);
	int numTagBits = physicalAddrBits - (numSetIndexBits + numBlockOffsetBits);

	//Extracts the set index and the tag from the address
	unsigned int setIndex = ((addr << numTagBits) & ((unsigned int)pow(2, physicalAddrBits) - 1)) >> (numTagBits + numBlockOffsetBits);

	unsigned int tag = (addr >> (numBlockOffsetBits + numSetIndexBits));

	//Diverts the rest of the work to the set class
	return sets[setIndex]->simulateWrite(tag);

}

//Displays the contents of the cache
void Cache::display() {

	//Displays the contents of each individual set in the cache
	int i;
	for (i = 0; i < (cacheSize / (blockSize * blocksPerSet)); i++) {
		sets[i]->display();
	}

}

