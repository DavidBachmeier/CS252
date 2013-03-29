#include <stdio.h>

struct freq {
	int number;
	int frequency;
};

void readScores(int*, int*);
void displayScores(int*, int);
void calcHistogram(struct freq*, int*, int*, int);
void displayHistogram(struct freq*, int);
void sortHistogram(struct freq*, int);

int main() {
	
	int numScores = 0;
	int scores[100];	
	int* numScoresPointer = &numScores;

	readScores(scores, numScoresPointer);
	printf("\n\nScores:\n");
	displayScores(scores, numScores);




	int numFreq = 0;
	struct freq frequencies[numScores];
	
	int i;
	for (i = 0; i < numScores; i++) {
		(*(frequencies + i)).number = 0;
	}

	int* numFreqPointer = &numFreq;




	calcHistogram(frequencies, numFreqPointer, scores, numScores);
	printf("\n\n\nUnsorted Histogram:\n");
	displayHistogram(frequencies, numFreq);

	sortHistogram(frequencies, numFreq);
	printf("\n\n\nSorted Histogram:\n");
	displayHistogram(frequencies, numFreq);

	return 0;
}

void readScores(int* scores, int* numScoresPointer) {
		
	int i = 0;
	while (scanf("%d", (scores + i)) != EOF) {
		(*numScoresPointer) = (*numScoresPointer + 1);
		i++; 
	} 
}

void displayScores(int* scores, int numScores) {
	int i;
	int count = 0;
	for(i = 0; i < numScores; i++) {
		printf("score %d: %d\n", count, *(scores + i));
		count++;
	}
}

void calcHistogram(struct freq* frequencies, int* numFreqPointer, int* scores, int numScores) {
	int i;
	int j; 
	int matchFound;
	for (i = 0; i < numScores; i++) {
		j = 0;
		matchFound = 0;
		while (( j <= (*numFreqPointer)) && (matchFound != 1)) {
			if (*(scores + i) == ((*(frequencies + j)).number)) {
				matchFound = 1;
				((*(frequencies + j)).frequency)++;
			}
			j++;
		}
		if (matchFound == 0) {
			(*(frequencies + j - 1)).number = *(scores + i);
			(*(frequencies + j - 1)).frequency = 1;
			(*numFreqPointer)++;
		}
	}
}

void displayHistogram(struct freq* frequencies, int numFreq) {
	int i;

	for (i = 0; i < numFreq; i++) {
		printf("value %d: freq %d\n", (*(frequencies + i)).number, (*(frequencies + i)).frequency);
	}
}

void sortHistogram(struct freq* frequencies, int numFreq) {
	
	struct freq tempArray[numFreq];
	
	int j;
	for (j = 0; j < numFreq; j++) {
		(*(tempArray)).frequency = 0;
	}

	(*(tempArray)).frequency = (*(frequencies)).frequency; 
	(*(tempArray)).number = (*(frequencies)).number;

	int i;
	int index1;
	int index2;
	int tempFreq;
	int tempNum;


	for (i = 1; i < numFreq; i++) {
		index1 = i - 1;
		index2 = i;
		
		(*(tempArray + index2)).frequency = (*(frequencies + index2)).frequency; 
		(*(tempArray + index2)).number = (*(frequencies + index2)).number;

	
		while ((index2 != 0) && (((*(tempArray + index1)).frequency) < ((*(tempArray + index2)).frequency))) {
			tempFreq = (*(tempArray + index1)).frequency; 
			tempNum = (*(tempArray + index1)).number;

			(*(tempArray + index1)).frequency = (*(tempArray + index2)).frequency;
			(*(tempArray + index1)).number = (*(tempArray + index2)).number;
		
			(*(tempArray + index2)).frequency = tempFreq;
			(*(tempArray + index2)).number = tempNum;

		
			index1--;
			index2--;
		}	
	}

	int k;
	for (k = 0; k < numFreq; k++) {
		(*(frequencies + k)).frequency = (*(tempArray + k)).frequency;
		(*(frequencies + k)).number = (*(tempArray + k)).number;

	}	
}
