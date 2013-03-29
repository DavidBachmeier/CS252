#include <vector>
#include "Block.h"

class Set {

	private:
		int blockSize;
		int blocksPerSet;
		std::vector<Block*> blocks;
		int checkSet(unsigned int tag);
		int getLRU();

	public:
		Set(int b, int e);
		~Set();
		int simulateRead(unsigned int tag);
		int simulateWrite(unsigned int tag);
		void display();
};
