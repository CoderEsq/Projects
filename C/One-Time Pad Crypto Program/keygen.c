/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 11/28/2015
*   Last Modification Date:       12/5/2015
*   Filename:                     keygen.c
*
*   Overview:   This program generates a random key of a specified length.
*
*   Input:  The input shall consist of a command line argument consisting of they keylength
*			that should be generated.
*
*   Output: The output of the program will be a key of random characters printed to the screen.
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

	/* Generates random seed for random number generator*/
	srand(time(NULL));

	/*Stores set of possible characters for key*/
	char set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

	/*Checks that the minimum number of arguments has been entered*/
	if(argc == 1) {
		printf("\nInsufficient number of arguments entered. Please try again.\n\n");
		exit(1);
	}

	int keyLength;
	int ii;
	int randNum;

	/*Stores the value of the length of the key that should be generated 
	from the command line argument*/
	keyLength = atoi(argv[1]);

	/*Generates a random number and prints to stdout a character from the char set*/
	for(ii = 0; ii < keyLength; ii++) {
		randNum = rand() % 27;
		printf("%c", set[randNum]);
	}

	/*Prints a newline character at the end*/
	printf("\n");

	return 0;
}