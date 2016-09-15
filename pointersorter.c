#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointersorter.h"

Node * head;



/*
Sorting is done before each node is appendedi in method newNode 
*/



/* Prints var in hex form */
void printAddress(int var) {
	printf("0x%x\n", var);
}

/* Prints token and length of a single node. */
void printNode(Node * n) {
	printf("Token:   %s\n", n->token);
	//printf("Length:  %i\n", n->length);
}

/* Prints token and length of entire list of nodes. 
   Frees the nodes as list is traversed. */
void printList(Node * head) {
	Node * ptr = head;
	while (ptr != '\0') {
		printf("Token:   %s\n", ptr->token);
		//printf("Length:  %i\n", ptr->length);
		Node * temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
}

/* Checks if char c is an alphabetical character.
   Returns 0 if alphabetical; 1 if non-alphabetical. */
int isAlphabet(char c) {
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
		return 1;
	} else {
		return 0;
	}
}

/* Creates the first Node and fills in data fields */
void createFirstNode(unsigned char * token, int length) {
	head = (Node *)malloc(sizeof(Node));
	head->token = token;
	head->length = length;
	head->next = NULL;
}

/* Creates a new Node, fills in data fields,
   and appends to the end of the linked list. */
void newNode(unsigned char * token, int length) {
	
	// Create and initialize new node
	Node * n = (Node *)malloc(sizeof(Node));
	n->token = token;
	n->length = length;
	n->next = NULL;

	// Append node to the end of the linked list
	Node * ptr = head;
	while (ptr != NULL) {
		if (ptr->next == NULL) {
			ptr->next = n;
			return;
		} else {
			append(n,ptr);
		}	
	
	}
}

//Duplicates new token into all capital letters, sorts relative to ascii number and then appends original node
void append(Node * n, Node * ptr)
{
	int i = 0;
	while(i)
	{
		int nLen = strlen();
		
		char newNode = (char)(toupper(n->token[i]);
		char appended = (char)(toupper(ptr->token[i])));

		if(newNode < appended)
		{
			n -> next = ptr -> next;
			ptr -> next = n;
			break;
		}	
		else if(newNode > appended)
		{
			ptr = ptr -> next;
			break;
		}
		else
		{
			i++;
		}
	}
}

/* Extracts tokens and calls functions to store
   the tokens and to sort them when added. */
int extractTokens(char * input, size_t inputSize) {

	// Two pointers to determine size of tokens
	char * tokenStart = input;
	char * tokenEnd = input;
	unsigned char isFirst = '0';

	// Traverse the input string moving tokenStart at the beginning if each token
	while ((int)tokenStart <= (int)input+inputSize) {

		// Start of new token
		if (isAlphabet(*tokenStart)) {

			// Traverse the token moving tokenEnd to find the size of the token
			tokenEnd = tokenStart;
			while (isAlphabet(*tokenEnd)) {
				tokenEnd++;
			}
			int length = tokenEnd-tokenStart;
			unsigned char * token = (unsigned char *)malloc((length)*sizeof(char));

			// Traverse the token moving tokenStart to tokenEnd to fill in characters
			for (int i = 0; tokenStart < tokenEnd; i++, tokenStart++) {
				token[i] = *tokenStart;
			}

			// Start linked list or add node to existing list
			if (isFirst == '0') {
				createFirstNode(token, length);
				isFirst = '1';
			} else {
				newNode(token, length);
			}

		// Non-alphabetical character; continue to next character	
		} else {
			tokenStart++;
		}
	}
	return 0;
}

/* Main takes input and calls functions to tokenize
   the input, store the tokens, sort the tokens, and
   print the tokens. */
int main(int argc, char** argv) {

	// Checks if number of arguments is incorrect
	if (argc != 2) {
		fprintf(stderr,"Arguments given are not in valid form. Give a single input string surrounded by quotations.\n");
		return -1;
	}
	// Prints help message if -h parameter is set
	if (strcmp(argv[1], "-h") == 0) {
		printf("Enter input string between quotations.\n");
		return 0;
	}

	extractTokens(argv[1], strlen(argv[1]));

	printList(head);

	printf("\n");
	return 0;	
}
