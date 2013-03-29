#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "shell.h"
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>



//buffer is the input string of characters
//args is the output array of arguments.  It has already been created with argsSize slots.
//nargs as the number filled in that is passed back
void parseArgs(char* buffer, char** args, int argsSize, int* nargs) {
		//Create array fro bufferd arguements
		char* bufArgs[argsSize];

		int j = 0;
		//Assign values in buffer to buffer arguements 
		while (((bufArgs[j] = strsep(&buffer, " \n\t")) != NULL) && ((bufArgs[j] == '\0') || ((j + 1) < argsSize))) {
			j++;		
		}
		
	
		int i = 0;
		*nargs = 0;
		//Assign buffered arguements to arguements that were passed in 
		//Set nargs to the proper value of arguements
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

//Scan the arguements for input redirection
int scanForIIR(char** args, int nargs) {

	int i = 0;
	//March through the arguements and look for a "<"
	while (i < nargs) {

		if (strcmp(args[i], "<") == 0) {
			//Return the index if found
			return i;
		}
		i++;

	}
	//Return -1 if not found
	return -1;

}


//Scan arguements for output redirection
int scanForIOR(char** args, int nargs) {

	int i = 0;
	//March through arguements and look for ">"
	while (i < nargs) {

		if (strcmp(args[i], ">") == 0) {
			//Return index if found
			return i;
		}
		i++;

	}
	//return -1 if not found 
	return -1;

}

//Delete the arguement at the given index
void deleteAtIndex(char** args, int index) {

	int i = index;
	//Move elements over 1 position, thus deleting value at the index
	while(args[i + 1] != NULL) {
		args[i] = args[i + 1];
		i++;
	}

	//Set the last arguement equal to NULL
	args[i] = NULL;


	//Printing args
	int argIndex = 0;
	while (args[argIndex] != NULL) {
		printf("%s  ", args[argIndex]);
		argIndex++;
	} 	
	printf("\n");
}

//Reaps any background zombies
void handler(int sig){
	int status;
	//Reap the zombie child if there is one at the current time
	int result = waitpid(-1, &status, 0);
}

int main() {

	//Create Linked list for history
	LinkedList* history = llCreate();
	int historyMaxSize = 25;
	int historyCount = 0;
	signal(SIGCHLD, handler);

	//Boolean flag
	int exit = 0;
	while(exit == 0) {
	
		//Print the current directory and prompt user for input
		printf("%s>", getcwd(0,0));			


		//Get the input from the user
		char buffer[40];
		fgets(buffer, 40, stdin);

		if (buffer[0] != '\n') {//Run only if text is entered


			//Parse the arugements entered by the user
			int bufferSize = 10;
			char* args[bufferSize];
			int nargs;
			parseArgs(buffer, args, bufferSize, &nargs);
	
			//print history item #5 if user prompts for it
			if (*args[0] == '!') {
				int count = 0;
				while(*(args[0] + count + 1) != '\0'){
					*(args[0]+count) = *(args[0] + count + 1);
					count++;
				}
				*(args[0] + count) = '\0';	
				int histIndex = atoi(args[0]);
				if (size(history) >= histIndex) {
					char* historyCommand = llReturnAtIndex(history, histIndex);
					strcpy(buffer, historyCommand);
					parseArgs(buffer, args, bufferSize, &nargs);
				} else {
					printf("You haven't executed %d commands yet.\n", histIndex);
				}
			}

			//Add arguement to history LL
			llAdd(&history, buffer);
			historyCount++;
			
			
			//Maintain history count of 25 elements
			if (historyCount == (historyMaxSize + 1)) {
				llRemoveAtIndex(&history, 0);
				historyCount--;
			}
			//Create background boolean and 
			//counter for its position in the args
			int background = 0;
			int count = 0;
			
			//Look for background specification
			do{	
				//Set to true if process is to be run in background
				if(strcmp(args[count], "&") == 0){
					background = 1;
					args[count] = NULL;
					nargs--;
				}
				count++;
			}while(args[count] != NULL);
	
				
			//Create arrays for i/o redir files
			char toBeInput[20];
			char toBeOutput[20];
	
			//Look for zombie processes and handle if need be 

			if (args[0] == NULL) {
				printf("\n");
			} else if (strcmp(args[0], "exit") == 0) {
				//Exit program if user requests
				exit = 1;	
			} else if (strcmp(args[0], "cd") == 0) {
				//Change the current working directory to the user requested dir
				int dir = chdir(args[1]);
				if (dir != 0) {
					printf("Directory not found\n");
				}
			} else if (strcmp(args[0], "history") == 0) {
				//Diplay the history of commands	
				llDisplay(history);	
			} else {
				//fork off a process
				int pid = fork();
				if (pid == -1) {
					//Error case
					printf("Error, unable to create new process\n");
				} else if (pid == 0) { //child
	 
					//Input redir check
					int inputRedir = scanForIIR(args, nargs);
					if (inputRedir != -1) {
						//Redirect the input if user requests
						strcpy(toBeInput, args[inputRedir + 1]);
						deleteAtIndex(args, inputRedir + 1);
						deleteAtIndex(args, inputRedir);
						freopen(toBeInput, "r", stdin);
					}
						
					//Output redir check
					int outputRedir = scanForIOR(args, nargs);
					if (outputRedir != -1) {
						//Redirect output if user requests
						strcpy(toBeOutput, args[outputRedir + 1]);
						deleteAtIndex(args, outputRedir + 1);
						deleteAtIndex(args, outputRedir);	
						freopen(toBeOutput, "w", stdout);
					}
					
					
					//Run the user requested command
					int res = execvp(args[0], args);

					//Kill the child if the command happens to fail
					if(res == -1){
						printf("Invalid Command!\n");
						exit = 1;;	
					}
	
				} else { //parent
					if(background == 0){
						//Wait for the process to finish
						//unless it is a background program
						int reapingInfo;
						waitpid(pid, &reapingInfo, 0);	
					}
				}		
			}
		}
	}
	llDelete(&history);
	return 0;	
}
