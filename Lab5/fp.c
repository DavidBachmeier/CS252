#include <stdio.h>
#include <math.h>

typedef union fi {

	unsigned int i;
	float f;

}fi;

void displayFloat(float);
float makeFloat(char*);
void displayInt(unsigned int);
int baseToDec(int, char*);

int main() {

	char fString[27] = "-101.1101";
/*	f[0] = '-';
	f[1] = '1';
	f[2] = '0';
	f[3] = '1';
	f[4] = '.';
	f[5] = '1';
	f[6] = '1';
	f[7] = '0';
	f[8] = '1';
*/
	
	printf("This is the binary float:  %s\n", fString);
	float f = makeFloat(fString);
	printf("%f\n", f);

	displayFloat(f);

}
void displayInt(unsigned int bs) {
	int i;
	for (i = 0; i < 32; i++) {
		printf("%d", ((bs & (int)pow(2, (31 - i))) >> (31 - i)));
	}

	printf("\n");
}

void displayFloat(float f) {

	fi thing;	

	thing.f = f;

	unsigned int integer = thing.i;

	displayInt(thing.i);
}

float makeFloat(char* f) {


	unsigned int package = 0;

	//if the number is negative, add a 1 in the first spot
	if (f[0] == '-') {
		package = package | 1;
	}

	//find out which index the '.' is at
	int i = 1;
	while(f[i] != '.' && f[i] != '\0') {
		i++;	
	}
	int indexOfPeriod = i;


	//find the exponent and add it to package
	i -= 2;
	int bias = 127;
	unsigned int exp = i + bias;

	package = package << 8;

	package = package | exp;

	//delete the '.' from the string f
	i = indexOfPeriod;
	while (f[i] != '\0') {
		
		f[i] = f[i + 1];
		i++;

	}

	//remove the sign and the first 1 from the string f
	i = 0;
	while (f[i] != '\0') {

		f[i] = f[i + 2];	
		i++;
	}

	//padd f with zeroes
	i -= 2;
	while (i < 23) {
		f[i] = '0';
		i++;
	}

	//turn f into an integer
	int mantissa = baseToDec(2, f);

	//make room in package to hold the mantissa
	package = package << 23;
	
	//add the mantissa to package
	package = package | mantissa;
	
	//cast package to a float
	fi thing;
	thing.i = package;
	return thing.f;


}

int baseToDec(int base, char* numString) {

	char* tmp = numString;
	int size = 0;
	while ((*(tmp + size)) != '\0') {
		size++;	
	}

	int dec = 0;
	int count = 1;
	while (size >= count) {
		if ((int)(*(tmp + (size - count))) >= 97) {
			dec += ((int)(*(tmp + (size - count))) - 87) * pow(base, (count - 1));
		} else {
			dec += ((int)(*(tmp + (size - count))) - 48) * pow(base, (count - 1));
		}
		count++;
	}
	
	return dec;
	
}
