#ifndef XYZ_SHELL_H
#define XYZ_SHELL_H

typedef struct node {

	char* value;
	struct node* next;

} LinkedList;



void parseArgs(char*, char**, int, int*);
int scanForIIR(char**, int);
int scanForIOR(char**, int);
void deleteAtIndex(char**, int);
void handler(int);
LinkedList* llCreate();
void llDisplay(LinkedList*);
void llAdd(LinkedList**, char*);
int size(LinkedList*);
void llAddAtIndex(LinkedList**, char*, int);
void llRemoveAtIndex(LinkedList**, int);
void llRemoveString(LinkedList**, char*);
void llDelete(LinkedList**);
char* llReturnAtIndex(LinkedList*, long);
#endif




