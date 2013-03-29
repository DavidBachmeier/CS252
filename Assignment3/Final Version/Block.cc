#include "Block.h"

Block::Block(int b) {
	//Initialize instance variables
	blockSize = b;
	isValid = 0;
	isDirty = 0;
	tag = -1;
	//Create base timestamp
	timestamp.hour = 0;
	timestamp.min = 0;
	timestamp.sec = 0;
	timestamp.usec = 0;
}

//Returns validity
int Block::getValidity() {
	return isValid;
}
//Returns dirtiness
int Block::getDirtiness() {
	return isDirty;
}
//Returns the tag
unsigned long Block::getTag() {
	return tag;
}
//Returns the microseconds from timestamp
long Block::getUsec() {
	return timestamp.usec;
}
//Gets the seconds from timestamp
int Block::getSec() {
	return timestamp.sec;
}
//Returns the minutes from timestamp
int Block::getMin() {
	return timestamp.min;
}
//Returns the hours from timestamp
int Block::getHour() {
	return timestamp.hour;
}
//Sets the validity of the block
void Block::setValidity(int validity) {
	isValid = validity;
}
//Sets the dirtiness of the block
void Block::setDirtiness(int dirtiness) {
	isDirty = dirtiness;
}
//Set the tag variable
void Block::setTag(unsigned int newTag) {
	tag = newTag;
}
//Sets all the time stamp info 
void Block::settimestamp(int hour, int min, int sec, long usec) {
	timestamp.hour = hour;
	timestamp.min = min;
	timestamp.sec = sec;
	timestamp.usec = usec;

}
