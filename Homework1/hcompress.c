#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hcompress.h"
#include "LinkedList.c"

int main(int argc, char *argv[]) {
	//Check to make sure the input parameters are correct
/*	if (argc != 3) {
		printf("Error: The correct format is \"compress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
	exit(1);
	}
*/	
	//Create the frequency table by reading the generic file
	struct tNode* leafNodes = createFreqTable("decind.txt");
	llDisplay(leafNodes);
/*	//Create the huffman tree from the frequency table
	struct tNode* treeRoot = createHuffmanTree(leafNodes);
	
	//encode
	if(strcmp(argv[1], "-e") == 0){
		//Pass the leafNodes since it process bottom up
		encodeFile(argv[2], leafNodes);
	}else{ //decode
		//Pass the tree root since it will process top down
		decodeFile(argv[2], treeRoot);
	}*/
	return 0;
}

tNode* createFreqTable(char* fileName){
	FILE* stream;
	stream = fopen(fileName, "r");
	
	int size = 128;
	int charArray[size];
	for(int i = 0; i < size; i++) {
		charArray[i] = 0;
	}

	char c;
	while((c = fgetc(stream)) != EOF) {
		charArray[(int)c]++;	
	}	
	
	tNode* leafNodes = llCreate();	
	
	for(int i = 0; i < size; i++){
		addInOrder(&leafNodes, i, charArray[i]);
	}
	
	return leafNodes;
}
