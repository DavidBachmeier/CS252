#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int threadCount;
int n;
int* nums;


void* findMultiples(void* par) {

	
	int* params = (int*)par;
	printf("%d\n", params[1]);

	int notPrime = 0;
	int originalPrime = params[1];
	int foundFirstNonPrime = 0;

	int startIndex = (params[1] + 1)  + ((n - params[1] - 1) * params[0] / threadCount);
	int endIndex = (params[1] + 1) + ((n - params[1] - 1) * (params[0] + 1) / threadCount);

	printf("start index = %d\n", startIndex);
	printf("end index = %d\n", endIndex);
	printf("\n");
	
	int index = startIndex;
	while((index <= endIndex) && (foundFirstNonPrime != 1)) {
		if ((index % originalPrime == 0) && (nums[index] != notPrime)) {
			nums[index] = notPrime;
			printf("number removed... %d\n", index);
			foundFirstNonPrime = 1;
		}		
		index++;
	}

	int count;
	if (foundFirstNonPrime == 1) {
		index--;
		count = 1;
		while((index + (originalPrime * count)) <= endIndex) {
			if (nums[index + (originalPrime * count)] != notPrime) {
				printf("number removed... %d\n", index + originalPrime * count);
				nums[index + (originalPrime * count)] = notPrime;
			}
			count++;
	
		}
	}

	return NULL;

}

int main() {

	threadCount = 7;
	pthread_t threadHandles[threadCount];

	n = 100;
	nums = (int*)malloc((n + 1) * sizeof(int));	

	int notExamined = -1;
	int notPrime = 0;
	int prime = 1;

	int i;
	for (i = 0; i < (n + 1); i++) {
		nums[i] = notExamined;
	}	

	nums[0] = notPrime;
	nums[1] = notPrime;

	int index = 2;
	int count;
	while(index < (n + 1)) {
	
		while((nums[index] != notExamined) && index < (n + 1)) {
			index++;
		}
		if (index < (n + 1)) {
			nums[index] = prime;	
		
			int threadNum;
			for (threadNum = 0; threadNum < threadCount; threadNum++) {
				int* par = (int*)malloc(2 * sizeof(int));
				par[0] = threadNum;
				par[1] = index; 
				pthread_create(&(threadHandles[threadNum]), NULL, findMultiples, (void*)par);
			//	sleep(1);
			}
	
			printf("About to join...\n");
	
			for(threadNum = 0; threadNum < threadCount; threadNum++) {
				printf("pthread %d joined\n", threadNum);
				pthread_join(threadHandles[threadNum], NULL);
			}
		}
	}
	
	printf("about to print...\n");
	int j;
	for (j = 0; j < (n + 1); j++) {
		if (nums[j] == prime) {
			printf("%d ", j);	
		}
	}








}
