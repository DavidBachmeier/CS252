#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "shell.h"
#include <string.h>



//buffer is the input string of characters
//args is the output array of arguments.  It has already been created with argsSize slots.
//nargs as the number filled in that is passed back
void parseArgs(char* buffer, char** args, int argsSize, int *nargs) {

	char *bufArgs[argsSize];
	char **cp;
	char *wbuf;
	int i;
	int j;

	wbuf = buffer;
	bufArgs[0] = buffer;
	args[0] = buffer;

	for (cp = bufArgs; (*cp = strsep(&wbuf, " \n\t")) != NULL;) {

		if ((*cp != '\0') && (++cp >= &bufArgs[argsSize])) {
			break;
		}
	}	

	for (j = i = 0; bufArgs[i] != NULL; i++) {

		if (strlen(bufArgs[i]) > 0 ) {
			args[j++] = bufArgs[i];
		}
				
	}

	//Add the NULL as the end argument because we need that for later
	*nargs = j;
	args[j] = NULL;

}

int scanForIIR(char** args, int nargs) {

	int i = 0;
	while (i < nargs) {

		if (strcmp(args[i], "<") == 0) {
			return i;
		}
		i++;

	}
	
	return -1;

}


int scanForIOR(char** args, int nargs) {

	int i = 0;
	while (i < nargs) {

		if (strcmp(args[i], ">") == 0) {
			return i;
		}
		i++;

	}

	return -1;

}

void deleteAtIndex(char** args, int index) {

	int i = index;
	while(args[i + 1] != NULL) {
		args[i] = args[i + 1];
		i++;
	}

	args[i] = NULL;


	//Printing args
	int argIndex = 0;
	while (args[argIndex] != NULL) {
		printf("%s  ", args[argIndex]);
		argIndex++;
	} 	
	printf("\n");
}

int main() {

	int exit = 0;
	while(exit == 0) {

		printf("%s>", getcwd(0,0));			

		char buffer[40];
		fgets(buffer, 40, stdin);

		char* args[10];
		int nargs;
		parseArgs(buffer, args, 10, &nargs);


				//Printing args
				int argIndex = 0;
				while (args[argIndex] != NULL) {
					printf("%s  ", args[argIndex]);
					argIndex++;
				} 		
				printf("\n");
			

		char toBeInput[20];
		char toBeOutput[20];

		if (strcmp(args[0], "exit") == 0) {
			exit = 1;	
		} else if (strcmp(args[0], "cd") == 0) {
			int dir = chdir(args[1]);
			if (dir != 0) {
				printf("Directory not found\n");
			}
		} else {
			int pid = fork();
			if (pid == -1) {
				printf("You don't do that!");
			} else if (pid == 0) { //child
			
				int inputRedir = scanForIIR(args, nargs);
				printf("inputRedir = %d\n", inputRedir);		
				if (inputRedir != -1) {
					strcpy(toBeInput, args[inputRedir + 1]);
					deleteAtIndex(args, inputRedir + 1);
					deleteAtIndex(args, inputRedir);
					freopen(toBeInput, "r", stdin);
				}
					
				int outputRedir = scanForIOR(args, nargs);
				printf("outpurRedir = %d\n", outputRedir);
				if (outputRedir != -1) {
					strcpy(toBeOutput, args[outputRedir + 1]);
					deleteAtIndex(args, outputRedir + 1);
					deleteAtIndex(args, outputRedir);	
					freopen(toBeOutput, "w", stdout);
				}
				execvp(args[0], args);

			} else { //parent
				int reapingInfo;
				waitpid(pid, &reapingInfo, 0);	
			}		
		}
	}			

}


