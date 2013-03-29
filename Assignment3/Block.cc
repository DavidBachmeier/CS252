#include "Block.h"

Block::Block(int b) {
	blockSize = b;
	isValid = 0;
	isDirty = 0;
	tag = -1;

	timestamp.hour = 0;
	timestamp.min = 0;
	timestamp.sec = 0;
	timestamp.usec = 0;
}


int Block::getValidity() {
	return isValid;
}

int Block::getDirtiness() {
	return isDirty;
}

unsigned long Block::getTag() {
	return tag;
}

long Block::getUsec() {
	return timestamp.usec;
}

int Block::getSec() {
	return timestamp.sec;
}

int Block::getMin() {
	return timestamp.min;
}

int Block::getHour() {
	return timestamp.hour;
}

void Block::setValidity(int validity) {
	isValid = validity;
}

void Block::setDirtiness(int dirtiness) {
	isDirty = dirtiness;
}

void Block::setTag(unsigned int newTag) {
	tag = newTag;
}

void Block::settimestamp(int hour, int min, int sec, long usec) {
	timestamp.hour = hour;
	timestamp.min = min;
	timestamp.sec = sec;
	timestamp.usec = usec;

}
	
