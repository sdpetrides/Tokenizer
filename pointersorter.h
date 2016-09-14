#ifndef POINTERSORTER_H
#define POINTERSORTER_H

// Structs
typedef struct node {
	unsigned char * token;
	int length;
	struct node * next;
} Node;

// Functions
void printAddress(int var);
void printNode(Node * n);
void printList(Node * head);
int isAlphabet(char c);
void createFirstNode(unsigned char * token, int length);
void newNode(unsigned char * token, int length);
int extractTokens(char * input, size_t inputSize);


#endif