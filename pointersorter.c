#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointersorter.h"


/* Prints var in hex form */
void printAddress(int var) {
	printf("0x%x\n", var);
}

/* Checks if char c is an alphabetical character.
   Returns 0 if alphabetical; 1 if non-alphabetical. */
int isAlphabet(char c) {
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
		return 0;
	} else {
		return 1;
	}
}

/* Extracts tokens and calls functions to store
   the tokens and to sort them when added. */
int extractTokens(char * input, size_t inputSize) {
	// Two pointers from start and end of tokens
	char * tokenStart = input;
	char * tokenEnd = input;

	// Traverse the input string moving tokenStart at the beginning if each token
	while (*tokenStart >= *input+inputSize) {
		if (isAlphabet(*tokenStart)) {
			tokenEnd = tokenStart;
			// continue checking if alphbetical to extract token with loop
		}
		tokenStart++; // not permanent, but for testing purposes

	}
	// TO: Andrew 
	//		I am having issues with this function so try and pick it up here
	// FROM: Steve

	/* Verify Locations and Values Of String */
	//printAddress(*tokenStart); 		// Address of tokenStart
	//printAddress(*tokenEnd);			// Address of tokenEnd
	//printf("%c\n", *tokenStart);		// Value at tokenStart
	//printf("%c\n", *tokenEnd);		// Value at tokenEnd
	


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
	//printAddress(*argv[1]);
	//printf("%s\n", argv[1]);

	extractTokens(argv[1], strlen(argv[1]));	// tokenize input string
		// store tokens
			// sort tokens

	// print tokens


	printf("\n");
	return 0;	
}