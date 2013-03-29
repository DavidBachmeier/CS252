#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <omp.h>


void delay() {
	usleep(1000 * 100);
}



int blocking(int startIndex, int endIndex) {

	printf("Blocking:\n");
	int range = endIndex - startIndex;
	int primeCount = 0;	

	//initialize loop variables
	int i;
	int j;
	int isPrime;
	double startTime;
	double endTime;
	double finalTime;

	//run loop in parallel
 	#pragma omp parallel private(endTime) reduction(+:primeCount)
	{
	startTime = omp_get_wtime();
	#pragma omp for schedule(static, (range / omp_get_num_threads()))  private(isPrime, j) nowait
	for (i = startIndex; i <= endIndex; i++) {

//		printf("Thread # %d: %d\n", omp_get_thread_num(), i);


		if ((i == 0) || (i == 1) || (i == 2)) {
			primeCount = primeCount + 1;
		} else {
			j = 2;
			isPrime = 1; //true
			while ((j < (sqrt(i) + 1)) && (isPrime == 1)) {
						
				if ((i % j) == 0) {
					isPrime = 0;
				}
						
				j++;
						
			}
					
			if (isPrime == 1) { //the number is prime
				primeCount = primeCount + 1;
			}
		}
								
	}
	
	endTime = omp_get_wtime();

	printf("time for %d: %f with %d found\n", omp_get_thread_num(), (endTime - startTime), primeCount);
	
	finalTime = omp_get_wtime();

	}

	printf("overall time: %f with %d found\n", (finalTime - startTime), primeCount);

	return primeCount;
}

int striping(int startIndex, int endIndex) {

	printf("Striping:\n");

	int range = endIndex - startIndex;
	int primeCount = 0;	

	//initialize loop variables
	int i;
	int j;
	int isPrime;
	double startTime;
	double endTime;
	double finalTime;

	//run loop in parallel
	#pragma omp parallel private(endTime) reduction(+:primeCount)
	{
	startTime = omp_get_wtime();
	#pragma omp for schedule(static, 1) private(isPrime, j) nowait
	for (i = startIndex; i <= endIndex; i++) {

//		printf("Thread # %d: %d\n", omp_get_thread_num(), i);
		
		if ((i == 0) || (i == 1) || (i == 2)) {
			primeCount = primeCount + 1;
		} else {
			j = 2;
			isPrime = 1; //true
			while ((j < (sqrt(i) + 1)) && (isPrime == 1)) {
						
				if ((i % j) == 0) {
					isPrime = 0;
				}
						
				j++;
						
			}
					
			if (isPrime == 1) { //the number is prime
				primeCount = primeCount + 1;
			}
		}

	}

	endTime = omp_get_wtime();

	printf("time for %d: %f with %d found\n", omp_get_thread_num(), (endTime - startTime), primeCount);

	finalTime = omp_get_wtime();


	}

	printf("overall time: %f with %d found\n", (finalTime - startTime), primeCount);

	return primeCount;

}


int main(int argc, char* argv[]) {
	
	 //Check to make sure the input parameters are correct
 	 if (argc != 3) {
		printf("Error: Incorrect format.\n"); fflush(stdout);
		exit(1);
 	 }

	//set range
	int startIndex = atoi(argv[1]);
	int endIndex = atoi(argv[2]);

	//set the number of threads
	int numThreads = 5;
	omp_set_num_threads(numThreads);

	int primeCount = blocking(startIndex, endIndex);
//	printf("Number of primes between %d and %d = %d\n", startIndex, endIndex, primeCount);
	
	printf("\n\n");

	primeCount = striping(startIndex, endIndex);
//	printf("Number of primes between %d and %d = %d\n", startIndex, endIndex, primeCount);



	return 0;

}
