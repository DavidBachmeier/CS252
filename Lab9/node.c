#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>



int main(int argc, char* argv[]) {

  //Check to make sure the input parameters are correct
  if (argc != 2) {
	printf("Error: The correct format is \"./node PortNumner\".\n"); fflush(stdout);
	exit(1);
  }
	
  // Get a socket of the right type
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("ERROR opening socket");
    exit(1);
  }

  // port number
  int portno = atoi(argv[1]);

  printf("portno = %d\n", portno);
  
  // server address structure
  struct sockaddr_in serv_addr;

  // Set all the values in the server address to 0
  memset(&serv_addr, '0', sizeof(serv_addr)); 

  // Setup the type of socket (internet vs filesystem)
  serv_addr.sin_family = AF_INET;

  // Basically the machine we are on...
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Setup the port number
  // htons - is host to network byte order
  // network byte order is most sig bype first
  //   which might be host or might not be
  serv_addr.sin_port = htons(portno);

  // Bind the socket to the given port
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR on binding\n");
    exit(1);
  }

  // set it up to listen
  listen(sockfd,5);
  

  int newsockfd;
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr);

  // Wait for a call
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0) {
    printf("ERROR on accept");
    exit(1);
  }
  printf("call accepted...\n");

  int* startIndex = (int*)malloc(sizeof(int));
  int* endIndex = (int*)malloc(sizeof(int));
	
  int error = read(newsockfd,startIndex,255);
  if (error < 0) {
    printf("ERROR reading from socket Start Index\n");
    exit(1);
  }
	
	error = read(newsockfd,endIndex,sizeof(int));
	if (error < 0) {
		printf("ERROR reading from socket End Index\n");
		exit(0);
	}
	printf("startIndex = %d\n", *startIndex);
	printf("endIndex = %d\n", *endIndex);
	
	int* localCount = (int*)malloc(sizeof(int));
	
	int i;
	int j;
	int isPrime;
	for (i = *startIndex; i <= *endIndex; i++) {
		
		if ((i == 0) || (i == 1) || (i == 2)) {
			printf("%d is prime\n", i);
			(*localCount)++;
		} else {
		j = 2;
		isPrime = 1; //true
		while ((j < (sqrt(i) + 1)) && (isPrime == 1)) {
					
			if ((i % j) == 0) {
				isPrime = 0;
			}
					
			j++;
					
		}
				
		if (isPrime == 1) {
			printf("%d is prime\n", i);
			(*localCount)++;
		}
		}
								
	}				
	
	error = write(newsockfd,localCount,sizeof(int));
	if (error < 0) {
		printf("ERROR writing to socket localCount\n");
		exit(0);
	}
	

  close(newsockfd);
  close(sockfd);	
	
	return 0;
}
