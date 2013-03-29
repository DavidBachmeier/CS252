#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "shell.h"
#include <string.h>
#include <signal.h>

//buffer is the input string of characters
//args is the output array of arguments.  It has already been created with argsSize slots.
//nargs as the number filled in that is passed back
void parseArgs(char* buffer, char** args, int argsSize, int* nargs) {

		char* bufArgs[argsSize];

		int j = 0;
		while (((bufArgs[j] = strsep(&buffer, " \n\t")) != NULL) && ((bufArgs[j] == '\0') || ((j + 1) < argsSize))) {
			j++;		
		}
		
	
		int i = 0;
		*nargs = 0;
		while (bufArgs[i] != NULL) {
			if (strlen(bufArgs[i]) > 0) {
				args[*nargs] = bufArgs[i];
				(*nargs) = (*nargs) + 1;
			}
			i++;
		}
		//Add the NULL as the end argument because we need that for later
		args[*nargs] = NULL;
	
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

void handler(int sig){
	int status;
	int result = waitpid(sig, &status, WNOHANG);
	
	printf("result = %d\n", result);
}

int main() {

	LinkedList* history = llCreate();
	int historyMaxSize = 25;
	int historyCount = 0;

	int exit = 0;
	while(exit == 0) {

		printf("%s>", getcwd(0,0));			

		char buffer[40];
		fgets(buffer, 40, stdin);

		if (buffer[0] != '\n') {

			llAddAtIndex(&history, buffer, 0);
			historyCount++;
			if (historyCount = 26) {
				llRemoveAtIndex(&history, 26);
				historyCount--;
			}
	
			char* args[10];
			int nargs;
			parseArgs(buffer, args, 10, &nargs);
	
			if (strcmp(args[0], "!5") == 0) {
				if (size(history) >= 5) {
					char* historyCommand = llReturnAtIndex(history, size(history) - 5);
					strcpy(buffer, historyCommand);
					parseArgs(buffer, args, 10, &nargs);
				} else {
					printf("You haven't executed 5 commands yet.\n");
				}
			}
				
			int background = 0;
			int count = 0;
			
			do{
				if(strcmp(args[count], "&") == 0){
					background = 1;
				}
				count++;
			}while(args[count] != NULL);
	
			char toBeInput[20];
			char toBeOutput[20];
	
			signal(SIGCHLD, handler);
			if (args[0] == NULL) {
				printf("\n");
			} else if (strcmp(args[0], "exit") == 0) {
				exit = 1;	
			} else if (strcmp(args[0], "cd") == 0) {
				int dir = chdir(args[1]);
				if (dir != 0) {
					printf("Directory not found\n");
				}
			} else if (strcmp(args[0], "history") == 0) {
				llDisplay(history);	
		
			} else {
				int pid = fork();
				if (pid == -1) {
					printf("Error, unable to create new process\n");
				} else if (pid == 0) { //child
				
					int inputRedir = scanForIIR(args, nargs);
					if (inputRedir != -1) {
						strcpy(toBeInput, args[inputRedir + 1]);
						deleteAtIndex(args, inputRedir + 1);
						deleteAtIndex(args, inputRedir);
						freopen(toBeInput, "r", stdin);
					}
						
					int outputRedir = scanForIOR(args, nargs);
					if (outputRedir != -1) {
						strcpy(toBeOutput, args[outputRedir + 1]);
						deleteAtIndex(args, outputRedir + 1);
						deleteAtIndex(args, outputRedir);	
						freopen(toBeOutput, "w", stdout);
					}
					execvp(args[0], args);
	
				} else { //parent
					if(background == 0){
						int reapingInfo;
						waitpid(pid, &reapingInfo, 0);	
					}
				}		
			}
		}
	}			
}
