/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 11/28/2015
*   Last Modification Date:       12/6/2015
*   Filename:                     otp_enc.c
*
*   Overview:   This program reads in a plaintext file and key file and passes it to
*				otp_enc_d for encryption and prints the encrypted message.
*
*   Input:  The input shall consist of a plain text file and key file in the form of
*			of command line arguments.
*
*   Output: The output of the program will be an encrypted message printed to the screen.
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main(int argc, char *argv[]) {

	/*Checks that the minimum number of arguments has been entered*/
	if(argc < 4) {
		printf("\nInsufficient number of arguments entered. Please try again.\n\n");
		exit(1);
	}

	/*Stores set of possible characters for key*/
	char set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

	char *progName = argv[0];
	char *plainFile = argv[1];
	char *keyFile = argv[2];
	char plainText[100000];
	char keyText[100000];
	int numPlainChars = 0;
	int numKeyChars = 0;

	FILE *key, *plain;

/*Opens plaintext file in read mode.*/
	plain = fopen(plainFile, "r");
	if (plain == NULL) {
		printf("\nError opening %s\n\n", plainFile); 
		exit(1);
	}

	char nextChar = getc(plain);

/*While loop reads in each character in file to count total number found in plaintext file.*/
	while (nextChar != EOF) {
	    numPlainChars++;
	    nextChar = getc(plain);
	}
/*Rewinds file pointer to start at beginning.*/
	rewind(plain);

/*Reads in entire plaintext file into array.*/
	if ( fgets(plainText, 100000 , plain) != NULL ) {}
	fclose(plain);


/*Opens key file in read mode.*/
	key = fopen(keyFile, "r");
	if (key == NULL) {
		printf("\nError opening %s\n\n", keyFile); 
		exit(1);
	}

	nextChar = getc(key);

/*While loop reads in each character in file to count total number found in key file.*/
	while (nextChar != EOF) {
	    numKeyChars++;
	    nextChar = getc(key);
	}
/*Rewinds file pointer to start at beginning.*/
	rewind(key);

/*Reads in entire key file into array.*/
	if ( fgets(keyText, 100000 , key) != NULL ) {}
	fclose(key);

	int ii;
	int jj;

/*Removes newline characters from plain text.*/
	for(ii = 0; ii < numPlainChars; ii++) {
		if (plainText[ii] == '\n') {
			numPlainChars--;
			plainText[ii] = '\0';
		}
	}

/*Removes newline characters from key text.*/
	for(ii = 0; ii < numKeyChars; ii++) {
		if (keyText[ii] == '\n') {
			numKeyChars--;
			keyText[ii] = '\0';
		}
	}

/*Checks if number of characters in key file is less than plaintext file.*/
	if(numKeyChars < numPlainChars) {
		printf("ERROR: Key length is not sufficiently long. Please create a larger key.\n");
		exit(1);
	}

/*Checks plaintext that each character is an uppercase character or a blank space.*/
	for(ii = 0; ii < numPlainChars; ii++) {
		if(isalpha(plainText[ii])) {
			if(isupper(plainText[ii])) {
				continue;
			}
			else {
				fprintf(stderr, "\nERROR: %s contains invalid characters.\n\n", plainFile); 
				exit(1);
			}

		}
		else if(plainText[ii] == ' ') {
			continue;
		}
		else {
			fprintf(stderr, "\nERROR: %s contains invalid characters.\n\n", plainFile);
			exit(1);
		}
	}

/*Checks keytext that each character is an uppercase character or a blank space.*/
	for(ii = 0; ii < numKeyChars; ii++) {
		if(isalpha(keyText[ii])) {
			if(isupper(keyText[ii])) {
				continue;
			}
			else {
				fprintf(stderr, "\nERROR: %s contains invalid characters.\n\n", keyFile); 
				exit(1);
			}

		}
		else if(keyText[ii] == ' ') {
			continue;
		}
		else {
			fprintf(stderr, "\nERROR: %s contains invalid characters.\n\n", keyFile);
			exit(1);
		}
	}

	int sockfd;
	int portno;
	int numRead;
	int numWrite;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char cipher[100000];

/*Converts passed in argument to port number.*/
	portno = atoi(argv[3]);

/*Creates new socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		printf("\nERROR opening socket.\n\n");
		exit(1);
	}
 
 /*Sets address of host.*/
	char *host = "localhost";

 	server = gethostbyname(host);
	if (server == NULL)
	{
		printf("\nERROR: No such host.\n\n");
		exit(1);
	}

/*Sets values of serv_addr struct*/
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

/*Establishes connection to server.*/
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "\nERROR: Unable to connect to port %d.\n\n", portno);
		exit(2);
	}

	char border1 = ';';
	char border2 = '$';
	char border3 = '@';

/*Sends program name to server.*/
	numWrite = write(sockfd, progName, strlen(progName)+1);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

/*Sends boundary char to server to indicate end of program name message.*/
	numWrite = write(sockfd, &border3, 1);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

/*Sends plaintext information to server.*/
	numWrite = write(sockfd, plainText, numPlainChars);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

/*Sends boundary char to server to indicate end of plaintext message.*/
	numWrite = write(sockfd, &border1, 1);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

/*Sends keytext information to server.*/
	numWrite = write(sockfd, keyText, numKeyChars);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

/*Sends boundary char to server to indicate end of keytext information.*/
	numWrite = write(sockfd, &border2, 1);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

/*Reads encrypted text information from server to.*/
	numRead = read(sockfd, cipher, numPlainChars);
	if (numRead < 0) {
		printf("\nERROR: Unable to read from socket.\n\n");
		exit(1);
	}

/*Prints encrypted text information.*/
	for(ii = 0; ii < numPlainChars; ii++) {
		printf("%c", cipher[ii]);
	}

	/*Prints a newline character at the end*/
	printf("\n");

	/*Closes socket.*/
	close(sockfd);

	return 0;
}