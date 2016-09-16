#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointersorter.h"

Node * head;

/* Prints token and length of a single node. */
void printNode(Node * n) {
	printf("%s\n", n->token);
}

/* Prints token and length of entire list of nodes. 
   Frees the nodes as list is traversed. */
void printList(Node * head) {
	if (head == NULL) {
		printf("No valid tokens in the input string.\n");
	}
	Node * ptr = head;
	while (ptr != '\0') {
		printNode(ptr);
		Node * temp = ptr;
		ptr = ptr->next;
		free(temp->token);
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

/* Returns uppercase version of character. */
char toUpper (char c) {
	if (c >= 97 && c <= 122) {
		return (c - 32);
	} else {
		return c;
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

	// Create pointers to traverse the linked list
	Node * ptrA = head; // first
	Node * ptrB = head; // second

	// Traverse the linked list and add the node in the proper position
	while (ptrA != NULL) {
		// There are more than one node in the list
		if (ptrA->next == NULL) {
			// ptrA is the last node in the list
			if (compareTokens(n, ptrA)) {
				// Place in linked list after ptrB
				ptrB->next = n;
				n->next = ptrA;
				return;
			} else {
				// Place n at the end of the list
				ptrA->next = n;
				return;
			}
		} else {
			if (ptrA == head && ptrB == head) {
				// Comparing with the first node in the list
				if (compareTokens(n, head)) {
					// Place n at the front of the linked list
					n->next = head;
					head = n;	
					return;
				} else {
					// Continue to the next node
					ptrA = ptrA->next;
				}
			} else if (compareTokens(n, ptrA)) {
				// Place in linked list after ptrB
				ptrB->next = n;
				n->next = ptrA;
				return;
			} else {
				// Continue to next node
				ptrA = ptrA->next;
				ptrB = ptrB->next;	
			}	
		}	
	}
}

/* Compares tokens of nodes to find correct 
   position in linked list of new node */
int compareTokens(Node * n, Node * ptr) {
	int i = 0;

	while (i <= n->length && i <= ptr->length) {
		
		char nChar = toUpper(n->token[i]);
		char ptrChar = toUpper(ptr->token[i]);

		if (nChar < ptrChar) {
			// Place in linked list before ptr
			return 1;
		} else if (nChar > ptrChar) {
			// Continue to next node
			return 0;
		} else {
			// Continue to next character
			i++;
		}
	}

	if (i == n->length) {
		// Place in linked list before ptr
		return 1;
	} else {
		// Continue to next node
		return 0;
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

	// Extract tokens, add to linked list in sorted order, and print linked list
	extractTokens(argv[1], strlen(argv[1]));
	printList(head);
	
	printf("\n");
	return 0;	
}
