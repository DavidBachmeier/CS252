#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {

	char* value;
	struct node* next;

} LinkedList;

LinkedList* llCreate();
void llDisplay(LinkedList*);
void llAdd(LinkedList**, char*);
int size(LinkedList*);
void addAtIndex(LinkedList**, char*, int);
void removeAtIndex(LinkedList**, int);
void removeString(LinkedList**, char*);
void llDelete(LinkedList**);

int main() {
	
	LinkedList* ll = llCreate();

	char* str = "hello";
	char* str2 = "ping";
	char* str3 = "pong";
	char* str4 = "pinga";
	char* str5 = "da";
	char* str6 = "ponga";
	char* str7 = "yup";

	llAdd(&ll, str);
	llAdd(&ll, str);
	llAdd(&ll, str);
	llAdd(&ll, str4);
	llAdd(&ll, str);
	llAdd(&ll, str6);	

	printf("LinkedList after adding a bunch of strings:\n");
	llDisplay(ll);
	printf("Size:  %d\n\n", size(ll));


	int index = 4;
	printf("LinkedList after adding '%d' at index %d:\n", str7, index);
	addAtIndex(&ll, str7, index);
	llDisplay(ll);
	printf("Size:  %d\n\n", size(ll));

	
	index = 3;
	printf("LinkedList after removing the word at index %d:\n", index);
	removeAtIndex(&ll, index);
	llDisplay(ll);
	printf("Size:  %d\n\n", size(ll));

	printf("LinkedList after removing all instances of %d:\n", str);
	removeString(&ll, str);
	llDisplay(ll);
	printf("Size:  %d\n\n", size(ll));
	
	llAdd(&ll, str);
	llAdd(&ll, str);
	llAdd(&ll, str);
	llAdd(&ll, str4);
	llAdd(&ll, str);
	llAdd(&ll, str6);
	
	printf("LinkedList after repopulation:\n");
	llDisplay(ll);

	llDelete(&ll);
	
	printf("Size:  %d\n", size(ll));
}



LinkedList* llCreate() {
	return NULL;
}

void llDisplay(LinkedList* ll) {
	LinkedList* p = ll;

	printf("[");
	while (ll != NULL) {
		printf(" %s ", (ll)->value);
		ll = (ll)->next;
	}

	printf("]\n\n");
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

void addAtIndex(LinkedList** ll, char* str, int index) {
	
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

void removeAtIndex(LinkedList** ll, int index) {
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


void removeString(LinkedList** ll, char* str) {
	
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
				removeAtIndex(ll, index);
			} 
		}
	}	
}

void llDelete(LinkedList** ll) {

	while(*ll != NULL) {
		removeAtIndex(ll, 0);
		llDisplay(*ll);
	}
	
}
