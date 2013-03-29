#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedList.h"
#include "hcompress.h"

/********************************************************************************************/
/* Cody Wanless                                                                             */
/* Zach Forster                                                                             */
/*                               Huffman File Compression Homework                          */
/*                                                                                          */
/*                               10/15/2012                                                 */
/*                                                                                          */
/*                                                                                          */
/********************************************************************************************/



int main(int argc, char *argv[]) {
	//Check to make sure the input parameters are correct
	if (argc != 3) {
		printf("Error: The correct format is \"compress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
	exit(1);
	}
	
	//Create the frequency table by reading the generic file
	LinkedList* leafNodes = createFreqTable("decind.txt");
	
	//Create the huffman tree from the frequency table
	struct tNode* treeRoot = createHuffmanTree(leafNodes);	
	
	if(strcmp(argv[1], "-e") == 0){ //decode

		//Pass the leafNodes since it process bottom up
		encodeFile(argv[2], leafNodes);
	
	}else{ //decode
		
		//Pass the tree root since it will process top down
		decodeFile(argv[2], treeRoot);
	
	}
	
	//free up extra memory
	llDelete(&leafNodes);
	deleteTree(treeRoot);

	return 0;
}

//Creates a frequency table for the printable characters
LinkedList* createFreqTable(char* fileName){
	
	//opening the necessary filestreams
	FILE* stream;
	stream = fopen(fileName, "r");
	
	//initializing the array and setting all weights to 0
	int size = 129;
	int charArray[size];
	for(int i = 0; i < size; i++) {
		charArray[i] = 0;
	}

	//reads in every character from a file, and counts the frequencies of each
	char c;
	while((c = fgetc(stream)) != EOF) {
		charArray[(int)c]++;	
	}
	
	//increments the frequency of the special EOF character	
	charArray[128]++;

	//creates a LinkedList and populates it with the contents of the frequency table
	LinkedList* leafNodes = llCreate();	
	for(int i = 0; i < size; i++){
		tNode* nn = (tNode*)malloc(sizeof(tNode));
		nn->c = i;
		nn->weight = charArray[i];
		addInOrder(&leafNodes, nn);
	}

	fclose(stream);	
	
	return leafNodes;
	
}

//Creates a tree of huffman tree nodes
tNode* createHuffmanTree(LinkedList* leafNodes){
	
		//initializing necessary pointers to nodes/links
		tNode* root;
		LinkedList* a = leafNodes;
		while (leafNodes->next != NULL) {
			
			//allocate memory for the root and sets its value to -1
			root = (tNode*)malloc(sizeof(tNode));
			root->c = -1;

			//links the node in the first link to the root
			leafNodes->node->parent = root;
			root->left = leafNodes->node;
			leafNodes = leafNodes->next;
		
			//links the node in the second link to the root
			leafNodes->node->parent = root;
			root->right = leafNodes->node;
			leafNodes = leafNodes->next;			
	
			//sets the weight of the root to the combined weights of each node
			root->weight = (root->left)->weight + (root->right)->weight;
			
			//adds the root in order of weight to the LinkedList
			addInOrder(&leafNodes, root);
				
		}

		leafNodes = a;
		int i = 0;
		
		//adds the ones and zeroes to the tree			
		addOnesAndZeroes(root);

		LinkedList* p = leafNodes;
		//removes all of the links containing previous root nodes from the LinkedList
		while(p != NULL) {
			if (p->node->c == -1) {
				removeAtIndex(&leafNodes, i);
				i--;

			}	
			i++;
			p = p->next;
		}	
		
		return root;
}

//Recursively sdds the 0's and 1's to each branch of the tree
void addOnesAndZeroes(tNode* node) {
		
		//Add a 0 as the weight for all left nodes
		if (node->left->c == -1) {
			node->left->weight = 0;
			addOnesAndZeroes(node->left);
		} 	
		
		//Add a 1 as the weight for all right nodes
		if (node->right->c == -1) {
			node->right->weight = 1;
			addOnesAndZeroes(node->right);
		}
}

//Compresses a text file
void encodeFile(char* file, LinkedList* leafNodes){


	FILE* stream;
	if ((stream = fopen(file, "r")) == NULL) { //the file doesn't exist

		printf("The file you specified does not exist.\n");

	} else { //the file exists
	
		strcat(file, ".huf");
		
		FILE* writeStream;
		writeStream = fopen(file, "w");
	
	
		//Creating necessary nodes and arrays
		tNode* currNode;
		LinkedList* p;
		int charCode[100];
		int bitArray[8];	
		
		//Creating other necessary variables
		unsigned char buffer = 0;
		int bitCount = 0;
		int charCodeSize;
		int packingIndex;
		char c;
		int bytesWritten = 0;
		
		//reads in characters from file one by one
		while((c = fgetc(stream)) != EOF) {
			
			charCodeSize = 0;
			p = leafNodes;
			
			//finds the character in the LinkedList
			while (p->node->c != (int)c) {
				p = p->next;
			}
	
			currNode = p->node->parent;
	
			//adds the first 1 or 0 to the bit array
			if ((currNode->right->c) == (p->node->c)) {
				charCode[charCodeSize] = 1;
			} else {
				charCode[charCodeSize] = 0;
			}
	
			charCodeSize++;
	
			//builds up a string of 1's and 0's for a certain character code
			while (currNode->parent != NULL) {
				
				charCode[charCodeSize] = (int)currNode->weight;
				currNode = currNode->parent;
				charCodeSize++;			
	
			}
	
	
			
			int flippedCharCode[charCodeSize];
			//flips the character code around
			for (int i = 0; i < charCodeSize; i++) {
				flippedCharCode[i] = charCode[charCodeSize - i - 1];
			}
	
			
			for(int j = 0; j < charCodeSize; j++) {
				
				bitArray[bitCount] = flippedCharCode[j];
				
				bitCount++;
				//If bit is full package it up and write it to the file
				if (bitCount == 8) {
					packingIndex = 0;
					while(packingIndex < 8) {
						//Package the bits into the byte
						buffer = buffer << 1;
						if (bitArray[packingIndex] == 1) {
							buffer = buffer | 1;
						}			
						packingIndex++;	
	
					}
					//write the byte to the file
					putc(buffer, writeStream);
					bytesWritten++;
					bitCount = 0;
					buffer = 0;
				}
	
			}
	
			
		}
	
	
			int bitsPacked = 0;
			charCodeSize = 0;
			p = leafNodes;
			
			//finds the character in the LinkedList
			while (p->node->c != 128) {
				p = p->next;
			}
	
			currNode = p->node->parent;
	
			//adds the first 1 or 0 to the bit array
			if ((currNode->right->c) == (p->node->c)) {
				charCode[charCodeSize] = 1;
			} else {
				charCode[charCodeSize] = 0;
			}
	
			charCodeSize++;
	
			//builds up a string of 1's and 0's for a certain character code
			while (currNode->parent != NULL) {
				
				charCode[charCodeSize] = (int)currNode->weight;
				currNode = currNode->parent;
				charCodeSize++;			
	
			}
	
	
	
			int flippedCharCode[charCodeSize];
			//flips the character code around
			for (int i = 0; i < charCodeSize; i++) {
				flippedCharCode[i] = charCode[charCodeSize - i - 1];
			}
	
			
			for(int j = 0; j < charCodeSize; j++) {
				//Add char code at index to the bit array
				bitArray[bitCount] = flippedCharCode[j];
				bitsPacked++;
				
				bitCount++;
				//Pack the bits and write them to file if they are full
				if (bitCount == 8) {
					bitsPacked = 0;
					packingIndex = 0;
					//Package the bits into a byte
					while(packingIndex < 8) {
						buffer = buffer << 1;
						if (bitArray[packingIndex] == 1) {
							buffer = buffer | 1;
						}			
						packingIndex++;	
	
					}
					//write the byte to the file
					putc(buffer, writeStream);
					bytesWritten++;
					bitCount = 0;
					buffer = 0;
				}
	
			}
			//Move final bits to leading end of byte
			if (bitsPacked > 0) {
				//Pack the bits into the byts
				for (int j = 0; j < bitsPacked; j++) {
					buffer = buffer << 1;
					if (bitArray[j] == 1) {
						buffer = buffer | 1;
					}
				}
				//Move all bits to leading end of byte and write them to file
				buffer = buffer << (8 - bitsPacked);
				putc(buffer, writeStream);
				fclose(writeStream);
				fclose(stream);
			}
	}
}
	
void masterDebugger(LinkedList* ll) {

	LinkedList* p  = ll;
	tNode* currNode;
	//Goes through the linked list and prints all nodes and associate weights
	while (p != NULL) { 
		printf(" %d with weight = %f::  ", p->node->c, p->node->weight);

		currNode = p->node->parent;
		//Prints the reverse code for tree traversal
		if ((currNode->right->c) == (p->node->c)) {
			printf("%d", 1);
		} else {
			printf("%d" , 0);
		}
		//Continues the tree path
		while (currNode->parent != NULL) { 
			printf(" weight %f ", currNode->weight);
			currNode = currNode->parent;
		}

		printf("\n");
		//Moves to next node
		p = p->next;
	}
}

void decodeFile(char* file, tNode* root){

	FILE* stream;
	if ((stream = fopen(file, "rb")) == NULL) { //the file doesn't exist
		printf("The file you specified does not exist.\n");

	} else { //the file exists
	
		//computing size of file
		fseek(stream, 0, SEEK_END);
		long charsInFile = ftell(stream);
		rewind(stream);
	
		//opening a file to write to
		strcat(file, ".dec");
		FILE* writeStream;
		writeStream = fopen(file, "w");	
	
		//declaring all necessary variables
		char c;
		char* bin;
		int count = 0;
		tNode* node = root;	
		int isFileDone = 1;
	
		unsigned char characters[charsInFile];
		fread(characters, sizeof(char), charsInFile, stream);
	
		int index = 0;
		while(index < charsInFile && isFileDone == 1) {
			//Get the byte to decode
			c = characters[index];
			//Convert the byte to its 8 bit code
			bin = decToBin(c);
				
			//walk through the tree for each 1 or 0 in the string bin
			count = 0;
			while(count <= 7 && isFileDone == 1){
				if(bin[count] == '1'){
					node = node->right;
				}else if (bin[count] == '0'){
					node = node->left;	
				}
				if(node->c == 128){
					isFileDone = 0;
				}
				//check to see if you're at a leaf node
				if(isFileDone == 1 && node->right == NULL && node->left == NULL){
					putc(node->c, writeStream);	
					node = root;
					
				}
				count++;
			
			}
			index++;
			free(bin);
		}
		
		fclose(stream);	
		fclose(writeStream);
	}
}
	
//Turns a decimal number into a binary string
char* decToBin(int dec){
	//Make sure the incoming is a positive value
	if(dec < 0)
		dec += 256;
	
	char* bin = (char*)malloc(8*sizeof(char));
	//Walk through the 8 bits and assign each a one or zero based on the decimal num
	for(int i = 0; i < 8; i++){
		if(dec - (pow(2, 8 - 1 - i)) >= 0){
			*(bin + i) = '1';
			dec = dec - (pow(2, 8 - 1 - i));
		}else
			*(bin+i) = '0';
	}
	return bin;
}

void deleteTree(tNode* node){
	//Delete the tree recursively 
	if(node != NULL){
	
	deleteTree(node->left);
	deleteTree(node->right);
	free(node);
	}
}
