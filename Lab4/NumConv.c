#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fibWrapper(int);
int fib(int, int, int);
int largestNForInt();
int largestNForLong();
void finiteRepresentation();
int binToDec(char*);
char* decToBin(int);
int baseToDec(int, char*);
char* decToBase(int, int);

int main() {

	printf("%d\n", fibWrapper(3));

	printf("%d\n", largestNForInt());
	printf("%d\n", largestNForLong());
	finiteRepresentation();

	int num = binToDec("11001");
	printf("Changing 11001 in binary to decimal:  %d\n", num);

	char* bin = decToBin(25);
	printf("Changing 25 in decimal to binary:  %s\n", bin);

	num = baseToDec(16, "f8");
	printf("Changing f8 in base 16 to decimal:  %d\n", num);

	char* base = decToBase(16, 523);
	printf("Changing 523 in decimal to base 16:  %s\n", base);

	num = baseToDec(16, base);
	printf("Changing it back:  %d\n", num);

	free(base);
	free(bin);
}

char* decToBase(int base, int dec) {
	int length = 0;
	while (dec >= pow(base, length)) {
		length++;
	}
	
	length--;
	
	char* tmpString = (char*)malloc(length * sizeof(char));
	
	int remainder = 0;	
	int i = 0;
	while (dec != 0) {
		remainder = dec % base;
		dec /= base;
		if (remainder <= 9) {
			tmpString[i] = (char)(remainder) + 48;
		} else {
			tmpString[i] = (char)(remainder) + 87;
		}

		i++;
	}
	
	//flip the string around
	char* baseString = (char*)malloc(length * sizeof(char));
	int j = 0;
	i--;
	while (i >= 0) {
		
		baseString[j] = tmpString[i];
		j++;	
		i--;

	}	

	free(tmpString);
		
	baseString[i] = '\0';	
	
	return baseString;
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

int binToDec(char* bin) {
	char* tmp = bin;
	int size = 0;
	while ((*(tmp + size)) != '\0') {
		size++;	
	}
	
	int dec = 0;
	int count = 1;
	while ((size - count) >= 0) {
		dec += ((int)(*(tmp + (size - count))) - 48) * pow(2, (count - 1));
		count++;
	}
	
	return dec;
	
}

char* decToBin(int dec) {
	int length = 0;
	while (dec >= pow(2, length)) {
		length++;
	}
	
	length--;
	
	char* bin = (char*)malloc(length * sizeof(char));

	int i;
	for (i = 0; i <= length; i++) {
		if (pow(2, (length - i)) <= dec) {
			dec -= pow(2, (length - i));
			bin[i] = '1';		
		} else {
			bin[i] = '0';
		}
	}	
	
	return bin;
}

int fibWrapper(int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	}
	return fib(n, 0, 1);
}

int fib(int iterationsToGo, int previous, int current) {
	if (iterationsToGo == 0) {
		return previous;
	}
		
	fib(iterationsToGo - 1, current, previous + current);

}

int largestNForInt() {
	int previous = 0;
	int current = 1;
	int tmp;
	int n = 1;

	while (current > 0) {
		tmp = current;
		current = current + previous;
		previous = tmp;
		n++;
	}

	return (n - 1);
}

int largestNForLong() {
	long previous = 0;
	long current = 1;
	long tmp;
	int n = 1;

	while (current > 0) {
		tmp = current;
		current = current + previous;
		previous = tmp;
		n++;
	}

	return (n - 1);
}

void finiteRepresentation() {
	double num0 = 0.2;
	double num1 = 0.2;
	double num2 = 0.2;
	double num3 = 0.6;

	printf("Num0: %f\n", num0);
	printf("Num1: %f\n", num1);
	printf("Num2: %f\n\n", num2);

	double num5 = num0 + num1 + num2 - num3;
	
	printf("Num0 + Num1 + Num2 - Num3: %f\n\n", num5);
	
	double range = 0.00001;
	if ((num5 < (0 + range)) || (num5 > (0 - range)) ) {
		printf("num5 = 0\n");
	} else {
		printf("num5 != 0\n");
	}

	printf("\n");

	printf("More Precise: %.20f\n\n", num5);

}
