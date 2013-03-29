#ifndef XYZ_HCOMPRESS_H
#define XYZ_HCOMPRESS_H
LinkedList* createFreqTable(char*);
struct tNode* createHuffmanTree(LinkedList*);
void encodeFile(char*, LinkedList*);
void decodeFile(char*, struct tNode*);
void addOnesAndZeroes(tNode*);
void masterDebugger(LinkedList*);
char* decToBin(int);
void deleteTree(struct tNode*);
void clearLinkedList(LinkedList*);
#endif 
