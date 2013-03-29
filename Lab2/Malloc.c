#include <stdio.h>
#include <stdlib.h>

typedef struct freq {
	int number;
	int frequency;
} Histogram;

int* readScores(int*);
void displayScores(int*, int);
int calcHistogram(Histogram**, int*, int);
void displayHistogram(Histogram*, int);
void sortHistogram(Histogram*, int);

int main() {
	
	int numScores = 0;	
	int* numScoresPointer = &numScores;


	int* scores = readScores(numScoresPointer);
	printf("\n\nScores:\n");
	displayScores(scores, numScores);

	Histogram* frequencies;
	int numFreq = calcHistogram(&frequencies, scores, numScores);	

	printf("\n\n\nUnsorted Histogram:\n");
	displayHistogram(frequencies, numFreq);

	sortHistogram(frequencies, numFreq);
	printf("\n\n\nSorted Histogram:\n");
	displayHistogram(frequencies, numFreq);

	free(frequencies);
	frequencies = NULL;
	scores = NULL;	

	return 0;
}

int* readScores(int* numScoresPointer) {
	
	int* scores;	
	scores = (int*)malloc(100 * sizeof(int)); 
		
	int i = 0;
	while (scanf("%d", &(scores[i])) != EOF) {
		(*numScoresPointer) = (*numScoresPointer + 1);
		i++; 
	}

	return scores;
}

void displayScores(int* scores, int numScores) {
	int i;
	int count = 0;
	for(i = 0; i < numScores; i++) {
		printf("score %d: %d\n", count, (scores[i]));
		count++;
	}
}

int calcHistogram(Histogram** frequencies, int* scores, int numScores) {
	
	int numFreq = 0;

	Histogram* tmp = (Histogram*)malloc(numScores * sizeof(Histogram));
	
	int n;
	for (n = 0; n < numScores; n++) {
		(tmp[n]).number = 0;
	}


	int i;
	int j; 
	int matchFound;
	for (i = 0; i < numScores; i++) {
		j = 0;
		matchFound = 0;
		while (( j <= (numFreq)) && (matchFound != 1)) {
			if ((scores[i]) == (((tmp[j])).number)) {
				matchFound = 1;
				((tmp[j]).frequency)++;
			}
			j++;
		}
		if (matchFound == 0) {
			((tmp[j - 1])).number = (scores[i]);
			((tmp[j - 1])).frequency = 1;
			numFreq++;
		}
	}
	
	*frequencies = tmp;
	
	free(scores);
	
	return numFreq;
}

void displayHistogram(Histogram* frequencies, int numFreq) {
	int i;

	for (i = 0; i < numFreq; i++) {
		printf("value %d: freq %d\n", ((frequencies[i])).number, ((frequencies[i])).frequency);
	}
}

void sortHistogram(Histogram* frequencies, int numFreq) {
	
	Histogram tempArray[numFreq];
	
	int j;
	for (j = 0; j < numFreq; j++) {
		((tempArray[0])).frequency = 0;
	}

	((tempArray[0])).frequency = ((frequencies[0])).frequency; 
	((tempArray[0])).number = ((frequencies[0])).number;

	int i;
	int index1;
	int index2;
	int tempFreq;
	int tempNum;


	for (i = 1; i < numFreq; i++) {
		index1 = i - 1;
		index2 = i;
		
		((tempArray[index2])).frequency = ((frequencies[index2])).frequency; 
		((tempArray[index2])).number = ((frequencies[index2])).number;

	
		while ((index2 != 0) && ((((tempArray[index1])).frequency) < (((tempArray[index2])).frequency))) {
			tempFreq = ((tempArray[index1])).frequency; 
			tempNum = ((tempArray[index1])).number;

			((tempArray[index1])).frequency = ((tempArray[index2])).frequency;
			((tempArray[index1])).number = ((tempArray[index2])).number;
		
			((tempArray[index2])).frequency = tempFreq;
			((tempArray[index2])).number = tempNum;

		
			index1--;
			index2--;
		}	
	}

	int k;
	for (k = 0; k < numFreq; k++) {
		((frequencies[k])).frequency = ((tempArray[k])).frequency;
		((frequencies[k])).number = ((tempArray[k])).number;

	}	
}
