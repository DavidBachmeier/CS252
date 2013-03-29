#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	char word[20];
}String;

typedef struct freq {
	String word;
	int frequency;
} Histogram;

String* readScores(int*);
void displayScores(String*, int);
int calcHistogram(Histogram**, String*, int);
void displayHistogram(Histogram*, int);
void sortHistogram(Histogram*, int);

int main() {
	
	int numScores = 0;	
	int* numScoresPointer = &numScores;


	String* string = readScores(numScoresPointer);
	printf("\n\nWords:\n");
	displayScores(string, numScores);

	Histogram* frequencies;
	int numFreq = calcHistogram(&frequencies, string, numScores);	

	printf("\n\n\nUnsorted Histogram:\n");
	displayHistogram(frequencies, numFreq);

	sortHistogram(frequencies, numFreq);
	printf("\n\n\nSorted Histogram:\n");
	displayHistogram(frequencies, numFreq);

	free(frequencies);
	frequencies = NULL;
	string = NULL;	

	return 0;
}

String* readScores(int* numScoresPointer) {
	
	String* string;	
	string = (String*)malloc(100 * sizeof(String)); 
		
	int i = 0;
	while (scanf("%s", &(string[i])) != EOF) {
		(*numScoresPointer)++;
		i++; 
	}

	return string;
}

void displayScores(String* string, int numScores) {
	int i;
	int count = 0;
	for(i = 0; i < numScores; i++) {
		printf("string %d: %s\n", count, ((string[i]).word));
		count++;
	}
}

int calcHistogram(Histogram** frequencies, String* string, int numScores) {
	
	int numFreq = 0;

	Histogram* tmp = (Histogram*)malloc(numScores * sizeof(Histogram));
	
	int n;
	for (n = 0; n < numScores; n++) {
		strcpy(((tmp[n]).word).word, "null");
	}


	int i;
	int j; 
	int matchFound;
	for (i = 0; i < numScores; i++) {
		j = 0;
		matchFound = 0;
		while (( j <= (numFreq)) && (strcmp((string[i].word), ((tmp[j]).word).word) != 0)/* no match found */) {
			j++;
		}
		if (j < numFreq) {	//a match was found
			((tmp[j]).frequency)++;
		} else {		//a match was not found
			strcpy(((tmp[j - 1]).word).word, string[i].word);
			((tmp[j - 1])).frequency = 1;
			numFreq++;
		}
	}
	
	*frequencies = tmp;
	
	free(string);
	
	return numFreq;
}

void displayHistogram(Histogram* frequencies, int numFreq) {
	int i;

	for (i = 0; i < numFreq; i++) {
		printf("value %s: freq %d\n", (((frequencies[i]).word).word), ((frequencies[i])).frequency);
	}
}

void sortHistogram(Histogram* frequencies, int numFreq) {
	
	Histogram tempArray[numFreq];
	
	int j;
	for (j = 0; j < numFreq; j++) {
		((tempArray[j])).frequency = 0;
	}

	tempArray[0] = frequencies[0];

	int i;
	int index1;
	int index2;
	int tempFreq;
	int tempNum;
	Histogram tempHist;

	for (i = 1; i < numFreq; i++) {
		index1 = i - 1;
		index2 = i;
		
		tempArray[index2] = frequencies[index2];
	
		while ((index2 != 0) && ((((tempArray[index1])).frequency) < (((tempArray[index2])).frequency))) {
			
			tempHist = tempArray[index1];			

			tempArray[index1] = tempArray[index2];			

			tempArray[index2] = tempHist;

			index1--;
			index2--;
		}	
	}

	int k;
	for (k = 0; k < numFreq; k++) {

		frequencies[k] = tempArray[k];
	}	
}
