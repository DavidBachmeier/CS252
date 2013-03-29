#include <iostream>
#include "Set.h"
#include <sys/time.h>

using namespace std;

//Constructor - creates a new set
Set::Set(int b, int e) {
	
	//Initializes instance variables
	blockSize = b;
	blocksPerSet = e;

	//Populates the set with blocks
	int i;
	for(i = 0; i < blocksPerSet; i++) {
		blocks.push_back(new Block(blockSize));
	}	

}

//Destructor - recursively deletes the set
Set::~Set() {

	//Deletes every block in the set
	int i;
	for(i = 0; i < blocksPerSet; i++) {
		delete blocks[i];
	}	

}

//Simulates an attempted read from the set
int Set::simulateRead(unsigned int tag) {

	int returnValue;
	struct timeval tv;
	struct tm* tm;
	struct timezone tz;

	if (checkSet(tag) != -1) { //Cache hit - the requested memory was in the cache

		//Set the return value to zero if hit
		returnValue = 0;

		//Update the time stamp information 
		gettimeofday(&tv, &tz);
		tm = localtime(&tv.tv_sec);

		int hour = tm->tm_hour;
		int min = tm->tm_min;
		int sec = tm->tm_sec;
		long usec = tv.tv_usec;

		//Set the timestamp for the block
		blocks[checkSet(tag)]->settimestamp(hour, min, sec, usec);
	
	} else { //Cache miss - the requested memory wasn't in the cache

		returnValue = 1;

		//Looks for an empty block in the set
		int i = 0;
		while((i < blocksPerSet) && (blocks[i]->getValidity() == 1)){
			i++;
		}

		if (i == blocksPerSet) { //The set was full

			//Find oldest block to replace
			i = getLRU();

			if (blocks[i]->getDirtiness() == 1) { //The block that we are replacing is ditry
				returnValue = 2;
			}	
		}

		//Set the tag, validity, and dirtiness
		blocks[i]->setTag(tag);
		blocks[i]->setValidity(1);
		blocks[i]->setDirtiness(0);

		//Creates a timestamp
		gettimeofday(&tv, &tz);
		tm = localtime(&tv.tv_sec);

		int hour = tm->tm_hour;
		int min = tm->tm_min;
		int sec = tm->tm_sec;
		long usec = tv.tv_usec;

		//Update the timestamp
		blocks[i]->settimestamp(hour, min, sec, usec);	
		
	}
	//Return the value specified above
	return returnValue;

}

//Simulate an attempted write to data stored in the set
int Set::simulateWrite(unsigned int tag) {
	//Initialize necessary variables
	int returnValue;
	struct timeval tv;
	struct tm* tm;
	struct timezone tz;

	if (checkSet(tag) != -1) { //If the tag already exists
		//Indicate a cache hit
		returnValue = 0;

		//Update the time info
		gettimeofday(&tv, &tz);
		tm = localtime(&tv.tv_sec);
		int hour = tm->tm_hour;
		int min = tm->tm_min;
		int sec = tm->tm_sec;
		long usec = tv.tv_usec;

		//Set the time and dirtitness
		blocks[checkSet(tag)]->settimestamp(hour, min, sec, usec);
		blocks[checkSet(tag)]->setDirtiness(1);

	} else {
		//Designate a cache miss
		returnValue = 1;

		//Find and empty block, if there is one in the set
		int i = 0;
		while((i < blocksPerSet) && (blocks[i]->getValidity() == 1)){
			i++;
		}

		if (i == blocksPerSet) { //The set was full
			//Find the oldest block
			i = getLRU();

			if (blocks[i]->getDirtiness() == 1) { //The block that we are replacing is dirty
				returnValue = 2;
			}
		} 

		//Update tage, validity, dirtiness and time info
		blocks[i]->setTag(tag);
		blocks[i]->setValidity(1);
		blocks[i]->setDirtiness(1);

		//Creates a timestamp 
		gettimeofday(&tv, &tz);
		tm = localtime(&tv.tv_sec);
		int hour = tm->tm_hour;
		int min = tm->tm_min;
		int sec = tm->tm_sec;
		long usec = tv.tv_usec;

		//Update the timestamp
		blocks[i]->settimestamp(hour, min, sec, usec);	
		
	}
	//return the necessary value as specifed above
	return returnValue;

}	

//Checks to see if the specified memory has already been loaded into the set 
int Set::checkSet(unsigned int tag) {

	//Loops through every block in the set	
	int i;
	for(i = 0; i < blocksPerSet; i++) {
		if ((blocks[i]->getTag() == tag) && (blocks[i]->getValidity() == 1)) { //Our tag is already in one of the blocks
			return i; 	
		}
	}
	//Return val if not found
	return -1;

} 

//Returns the index of the least recently used block
int Set::getLRU(){

	//Initializes the index of the least recently used block
	int LRUIndex = 0;

	//Retrieves the timestamp info from the LRU
	int LRUHour = blocks[LRUIndex]->getHour();
	int LRUMin = blocks[LRUIndex]->getMin();
	int LRUSec = blocks[LRUIndex]->getSec();
	long LRUUsec = blocks[LRUIndex]->getUsec();

	//Loops through each of the other blocks
	int i = 1;
	while(i < blocksPerSet){
		
		//Retrieves the timestamp info from the current block
		int currHour = blocks[i]->getHour();
		int currMin = blocks[i]->getMin();
		int currSec = blocks[i]->getSec();
		long currUsec = blocks[i]->getUsec();

		//Compare the hours
		if(LRUHour > currHour){ //the current block is the new LRU
			
			//Set the new LRU index and timestamp info
			LRUIndex = i;
			LRUHour = blocks[LRUIndex]->getHour();
			LRUMin = blocks[LRUIndex]->getMin();
			LRUSec = blocks[LRUIndex]->getSec();
			LRUUsec = blocks[LRUIndex]->getUsec();

		} else if(LRUHour == currHour){ //compare the minutes
				
			if(LRUMin > currMin){ //The current block is the new LRU

				//Set the new LRU index and timestamp info
				LRUIndex = i;
				LRUHour = blocks[LRUIndex]->getHour();
				LRUMin = blocks[LRUIndex]->getMin();
				LRUSec = blocks[LRUIndex]->getSec();
				LRUUsec = blocks[LRUIndex]->getUsec();

			} else if(LRUMin == currMin){ //Compare the seconds
				
				if(LRUSec > currSec){ //The current block is the new LRU

					//Set the new LRU index and timestamp info
					LRUIndex = i;
					LRUHour = blocks[LRUIndex]->getHour();
					LRUMin = blocks[LRUIndex]->getMin();
					LRUSec = blocks[LRUIndex]->getSec();
					LRUUsec = blocks[LRUIndex]->getUsec();

				} else if(LRUSec == currSec){ //Compare the usecs
					
					if(LRUUsec > currUsec){ //The current block is the new LRU

						//Set the new LRU index and timestamp info
						LRUIndex = i;
						LRUHour = blocks[LRUIndex]->getHour();
						LRUMin = blocks[LRUIndex]->getMin();
						LRUSec = blocks[LRUIndex]->getSec();
						LRUUsec = blocks[LRUIndex]->getUsec();

					}
				}
			}
		}

		i++;	
	}

	return LRUIndex;	
}

//Displays the contents of the set
void Set::display() {

	//Initialze variables
	int hour;
	int min;
	int sec;
	long usec;
	
	int i;
	//March through the blocks in the set and display their info
	for (i = 0; i < blocksPerSet; i++) {
		
		//Display validity if it is set
		if (blocks[i]->getValidity() == 1) {
			cout << "Valid  |  ";
		} else {
			cout << "Invalid  |  ";
		}

		//Display a dirty or not
		if (blocks[i]->getDirtiness() == 1) {
			cout << "Dirty  |  ";
		} else {
			cout << "Not Dirty  |  ";
		}

		//Display the tag information
		if (long(blocks[i]->getTag()) == -1) {
			cout << "Tag: Not Set" << endl; 
		} else {
			cout << "Tag: " << blocks[i]->getTag() << endl;
		}

		//Retrieves the time variables 
		hour = blocks[i]->getHour();
		min = blocks[i]->getMin();
		sec = blocks[i]->getSec();
		usec = blocks[i]->getUsec();

		//Display time variables
		cout << "Last viewed / edited:  " << hour << " hrs : " << min << " mins : " << sec << " secs : " << usec << " usecs : " << endl;
	}

}

//Returns the number of dirty blocks in the set
int Set::getSetNumDirtyBlocks(){
	
	int total = 0;

	//Loops through all of the blocks and adds to the total if they are dirty	
	int i;
	for(i = 0; i < blocksPerSet; i++) {
		if (blocks[i]->getDirtiness() == 1) {
			total++;
		}
	}
	
	return total;
}
