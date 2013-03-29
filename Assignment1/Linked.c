#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

//Creates a LinkedList
LinkedList* llCreate(){
	return NULL;
}


//Displays the c values of every node in LinkedList
void llDisplay(LinkedList* ll){
	LinkedList* p  = ll;

	printf("[");
	while (p != NULL) { 
		printf(" %d ", p->node->c);
		p = p->next;
	}
	printf("]\n");
}

//Adds a link containing a tree node to LinkedList
void llAdd (LinkedList** ll, tNode* str) {
	
	//allocate memory for the link
	LinkedList* nn = (LinkedList*)malloc(sizeof(LinkedList));
	nn->node = str;
	nn->next = NULL;
	
	//Find the end of the list
	LinkedList* p = *ll;

	if(p == NULL) {
		*ll = nn;
	} else{
		while(p->next != NULL){
			p = p->next;
		}
	p->next = nn;
	}
}

//Returns the size of LinkedList
int llSize(LinkedList *ll){
	LinkedList* p = ll;
	int size = 0;
	
	if(p == NULL){
		return size;
	}
	
	while(p != NULL){
		p = p->next;
		size++;
	}
	return size;
}

//Adds a link containing a tree node into a certain index in LinkedList
void llAddAtIndex(LinkedList** ll, tNode* node, int index){
	int size = llSize(*ll);
	if(ll != NULL && index <= size){ //checks for a valid index
		LinkedList* nn = (LinkedList*)malloc(sizeof(LinkedList));
		nn->node = node;
		nn->next = NULL;
		LinkedList* p = *ll;		
		
		//Put node in front of list if index is 0	
		if(index == 0){
			*ll = nn;
			nn->next = p;
		}else{
			//Find the index and insert the node
			int i = 0;
			while(p != NULL && i < index - 1 ){
				p = p->next;
				i++;
			}
			if(p != NULL){
				LinkedList* a = p->next;	
				p->next = nn;
				nn->next = a;
			}else{
				llAdd(ll, node);
			}
		}

	}
}

//Removes a link (but not the node it contains) from a given index in LinkedList
void removeAtIndex(LinkedList** ll, int index){
	int size = llSize(*ll);
	if(*ll != NULL && index < size){
		LinkedList* p = *ll;
		if(index == 0){
			*ll = p->next;
			free(p);	
		}else{
			int i = 0;
			while(p != NULL && i <  index - 1){
				p = p->next;
				i++;
			}
			
			LinkedList* c = p->next;
			LinkedList* a = c->next;
			p->next = a;
			free(c);
		}
	}
}

//Deletes every link in LinkedList
void llDelete(LinkedList** ll){
	LinkedList* p = *ll;
	
	//delete every link in LinkedList
	while(p != NULL){
		LinkedList* c = p->next;
		free(p->node);
		free(p);
		p = c;
	}
	*ll = p;
}

//Adds a tree node in order by weight into LinkedList
void addInOrder(LinkedList** ll, tNode* nn){
	
	if(*ll == NULL){ //the LinkedList is null

		//add the link at the beginning
		llAdd(ll, nn);

	}else{ //the LinkedList is not null
		
		LinkedList* p = *ll;
		int count = 0;
		
		//find the correct index and add the link there
		while ((p != NULL) && (nn->weight > (p->node)->weight)) {
			count++;
			p = p->next;
		}
		
		llAddAtIndex(ll, nn, count);
	}
}

