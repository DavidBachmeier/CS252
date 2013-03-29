#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tNode {
	int c;
	int weight;
	struct tNode* right;
	struct tNode* left;
	struct tNode* parent;
} tNode;

#include "LinkedList.h"

tNode* llCreate(){
	return NULL;
}

void llDisplay(tNode* ll){
	tNode* p  = ll;

	printf("[");
	while (p != NULL) { 
		printf(" %d ", p->weight);
		p = p->right;
	}
	printf("]\n");
}

void llAdd (tNode** ll, int num, int freq) {

	tNode* nn = (tNode*)malloc(sizeof(tNode));
	nn->c = num;
	nn->weight = freq;
	nn->right = NULL;
	nn->left = NULL;
	nn->parent = NULL;
	
	//Find the end of the list
	tNode* p = *ll;

	if(p == NULL) {
		*ll = nn;
	} else{
		while(p->right != NULL){
			p = p->right;
		}
	p->right = nn;
	}
}

int llSize(tNode *ll){
	tNode* p = ll;
	int size = 0;
	
	if(p == NULL){
		return size;
	}
	
	while(p != NULL){
		p = p->right;
		size++;
	}
	return size;
}

void llAddAtIndex(tNode** ll, int num, int index, int freq){
	int size = llSize(*ll);
	if(ll != NULL && index <= size){
		tNode* nn = (tNode*)malloc(sizeof(tNode));
		nn->c = num;
		printf("%d\n", freq);
		nn->weight =  freq;
		nn->right = NULL;
		nn->left = NULL;
		nn->parent = NULL;
		tNode* p = *ll;		
			
		if(index == 0){ 
			*ll = nn;
			nn->right = p;
		}else{
			int i = 0;
			while(p != NULL && i < index - 1 ){
				p = p->right;
				i++;
			}
			if(p != NULL){
				tNode* a = p->right;	
				p->right = nn;
				nn->right = a;
			}else{
				llAdd(ll, num, freq);
			}
		}
	}
}

void llRemoveAtIndex(tNode** ll, int index){
	int size = llSize(*ll);
	if((index < size) && (index >= 0)){
		tNode* p = *ll;
		if(index == 0){
			*ll = p->right;
			free(p);		
		}else{
			int i = 0;
			while(p != NULL && i <  index - 1){
				p = p->right;
				i++;
			}
			
			tNode* d = p->right;
			tNode* a = d->right;
			p->right = a;
			free(d);
		}
	}
}

void llRemoveInt(tNode** ll, int num) {
	
	if (*ll != NULL) {
		tNode* p = *ll;
		int index = 0;
		while (p->right != NULL) {
			p = *ll;
			while((p->right != NULL) && ((p->c) != num)) {
				p = p->right;
				index++;
			}	
			if (index < llSize(*ll)) {
				llRemoveAtIndex(ll, index);
			} 
		}
	}	
}

void llDelete(tNode** ll){
	while(*ll != NULL){
		llRemoveAtIndex(ll, 0);
		llDisplay(*ll);
	}
}

void addInOrder(tNode** node, int val, int freq){
	if(*node == NULL){
		llAdd(node, val, freq);
	}else{
		tNode* p = *node;
		int count = 0;
		while (p != NULL && (freq > p->weight)) {
			count++;
			p = p->right;
		}
		
		
		llAddAtIndex(node, val, count, freq);
	}
}

/* int main() {
	
	tNode* ll = llCreate();

	int int1 = 7;
	int int2 = 8;
	int int3 = 3;
	int int4 = 4;
	int int5 = 10;
	int int6 = 11;
	int int7 = 123;

	llAdd(&ll, int1, 9834);
	llAdd(&ll, int1, 2342);
	llAdd(&ll, int1, 23423);
	llAdd(&ll, int4, 4234);
	llAdd(&ll, int1, 23423);
	llAdd(&ll, int6, 23422);
	

	printf("LinkedList after adding a bunch of strings:\n");
	llDisplay(ll);
	printf("Size:  %d\n\n", llSize(ll));


	int index = 4;
	printf("LinkedList after adding '%d' at index %d:\n", int7, index);
	llAddAtIndex(&ll, int7, index, 234234);
	llDisplay(ll);
	printf("Size:  %d\n\n", llSize(ll));

	
	index = 3;
	printf("LinkedList after removing the word at index %d:\n", index);
	llRemoveAtIndex(&ll, index);
	llDisplay(ll);
	printf("Size:  %d\n\n", llSize(ll));

	printf("LinkedList after removing all instances of %d:\n", int1);
	llRemoveInt(&ll, int1);
	llDisplay(ll);
	printf("Size:  %d\n\n", llSize(ll));
	
	llAdd(&ll, int1, 2234);
	llAdd(&ll, int1, 2234);
	llAdd(&ll, int1, 22342);
	llAdd(&ll, int4, 1123);
	llAdd(&ll, int1, 4456);
	llAdd(&ll, int6, 4345);
	
	printf("LinkedList after repopulation:\n");
	llDisplay(ll);

	llDelete(&ll);
	
	printf("Size:  %d\n", llSize(ll));
} */
