#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "shell.h"

LinkedList* llCreate() {
	return NULL;
}

void llDisplay(LinkedList* ll) {
	LinkedList* p = ll;
	
	int index = 0;
	while (ll != NULL) {
		printf("Command ID: %d\t----\tCommand: %s\n", index, (ll)->value);
		ll = (ll)->next;
		index++;
	}

}

void llAdd(LinkedList** ll, char* str) {
	
	char* string = (char*)malloc(6*sizeof(char*));
	strcpy(string, str);

	LinkedList* nn = (LinkedList*)malloc(1*sizeof(LinkedList));
	nn->value = string;
	nn->next = NULL;

	//Find the end of the line
	LinkedList* p = *ll;	

	if (p == NULL) {
		//adding to an empty list
		(*ll) = nn;
	} else {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nn;
	}
	
}


int size(LinkedList* ll) {
	
	int size = 0;	

	if ((ll) == NULL) {
		
		return size;
	
	} else {
		size++;

		while (ll->next != NULL) {
			
			ll = ll->next;
			size++;
		
		}
		
	}

	return size;


}

void llAddAtIndex(LinkedList** ll, char* str, int index) {
	
	char* string = (char*)malloc(6*sizeof(char*));
	strcpy(string, str);

	LinkedList* nn = (LinkedList*)malloc(1*sizeof(LinkedList));
	nn->value = string;
	nn->next = NULL;

	LinkedList* p = *ll;
	
	if ((index == 0 && p == NULL) || (index == (size(*ll) - 1)) ) { //(index is zero and size is zero) or (index is the last in the array)
		llAdd(ll, string);	
	} else if (index == 0 && p != NULL) {
		LinkedList** newLL = ll;
		*newLL = nn;
		nn->next = p;
	} else if ((index < size(*ll)) && (index > 0)) { //index is between 0 and size and size is greater than 0
		int i = 0;
		while(i < (index - 1)) {
			p = p->next;
			i++;
		}
		
		LinkedList* tmp = p->next;
		p->next = nn;
		nn->next = tmp;
		
		
	}

}

void llRemoveAtIndex(LinkedList** ll, int index) {
	if ((index < size(*ll)) && (index > 0)) {
		LinkedList* p = *ll;
		LinkedList* c = *ll;	
		
		int i = 0;
		while (i < (index - 1)) {
			p = p->next;
			i++;
		}
		

		int j = 0;
		while (j < (index + 1)) {
			c = c->next;
			j++;
		}

		free((p->next)->value);
		free(p->next);
		p->next = c;
		 
	}
	
	if (index == 0) {
		LinkedList* p = *ll;
		*ll = (*ll)->next;
		free(p->value);
		free(p);

	}
}

char* llReturnAtIndex(LinkedList* ll, long index) {
	if ((index < size(ll)) && (index > 0)) {
		int i = 0;
		while (i < index) {
			ll = ll->next;
			i++;
		}
		
		return ll->value;
		 
	}
	
	if (index == 0) {
		return (ll)->value;
	}
}

void llRemoveString(LinkedList** ll, char* str) {
	
	LinkedList* p = *ll;
	if (p != NULL) {
		int index = 0;
		while (p->next != NULL) {
			p = *ll;
			while((p->next != NULL) && (strcmp(p->value, str) != 0)) {
				p = p->next;
				index++;
			}	
			if (index < size(*ll)) {
				llRemoveAtIndex(ll, index);
			} 
		}
	}	
}

void llDelete(LinkedList** ll) {

	while(*ll != NULL) {
		llRemoveAtIndex(ll, 0);
		llDisplay(*ll);
	}
	
}
