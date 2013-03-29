#include <vector>
#include "Set.h"

class Cache {

	private:
		int physicalAddrBits;
		int cacheSize;
		int blockSize;
		int blocksPerSet;
		std::vector<Set*> sets;		


	public:
		Cache(int m, int c, int b, int e);
		~Cache();
		int simulateRead(unsigned long addr);
		int simulateWrite(unsigned long addr);
		void display();
};
