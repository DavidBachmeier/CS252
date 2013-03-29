#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int primeCount;
int max;
int min;
pthread_mutex_t lock;

void* makeSockets(void* par) {
	
	int* params = (int*)par;
	
	int* startIndex = (int*)malloc(sizeof(int));
	int* endIndex = (int*)malloc(sizeof(int));
	
	*startIndex = min + (((max - min) / params[1]) * params[0]);
	*endIndex = *startIndex + (((max - min) / params[1])) - 1;
	
	// Socket pointer
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr,"ERROR opening socket\n");
		exit(0);
	}

	// port number
	int portno = (params[0] * 1000) + 11000;
	
	// server address structure
	struct sockaddr_in serv_addr;

	// Set all the values in the server address to 0
	memset(&serv_addr, '0', sizeof(serv_addr)); 

	// Setup the type of socket (internet vs filesystem)
	serv_addr.sin_family = AF_INET;

	// Setup the port number
	// htons - is host to network byte order
	// network byte order is most sig bype first
	//   which might be host or might not be
	serv_addr.sin_port = htons(portno);

	// Setup the server host address
	struct hostent *server;
	server = gethostbyname("localhost");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);  /// dest, src, size

	// Connect to the server
	if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR connecting\n");
		exit(0);
	}

	int error = write(sockfd,startIndex,sizeof(int));
	if (error < 0) {
		printf("ERROR writing to socket Start Index\n");
		exit(0);
	}
		
	error = write(sockfd,endIndex,sizeof(int));
	if (error < 0) {
		printf("ERROR writing to socket End Index\n");
		exit(0);
	}
	
	int* localCount = (int*)malloc(sizeof(int));
	error = read(sockfd,localCount,sizeof(int));
	if (error < 0) {
		printf("ERROR reading from socket Local Count\n");
		exit(0);
	}
	
	pthread_mutex_lock(&lock);
	primeCount += *localCount;
	pthread_mutex_unlock(&lock);
	
	close(sockfd);	
	
}

int main() {


	int threadCount = 5;
	pthread_t threadHandles[threadCount];
	
	min = 1000;
	max = 10000;
	primeCount = 0;
		
	int threadNum;
	for (threadNum = 0; threadNum < threadCount; threadNum++) {
		int* par = (int*)malloc(2 * sizeof(int));
		par[0] = threadNum;
		par[1] = threadCount;
		pthread_create(&(threadHandles[threadNum]), NULL, makeSockets, (void*)par);
	}
	
	printf("About to join...\n");
	
	for(threadNum = 0; threadNum < threadCount; threadNum++) {
		printf("pthread %d joined\n", threadNum);
		pthread_join(threadHandles[threadNum], NULL);
	}

	
	printf("Primes between %d and %d = %d\n", min, max, primeCount);








}
