/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 12/5/2015
*   Last Modification Date:       12/6/2015
*   Filename:                     otp_enc_d.c
*
*   Overview:   This program receives a plaintext file and key file from a client, encodes
*				the plain text message, and passes it to the client.
*
*   Input:  The input shall consist of a plain text string and key file string via the
*			client.
*
*   Output: The output of the program will be an encrypted message sent to the client.
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void encrypt(int);

int main(int argc, char *argv[]) {

/*Checks that the minimum number of arguments has been entered*/
	if(argc < 2) {
		printf("\nInsufficient number of arguments entered. Please try again.\n\n");
		exit(1);
	}

	int sockfd, newsockfd, portno, pid;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

/*Creates new socket*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
    	printf("\nERROR opening socket.\n\n");
		exit(1);
    }

/*Initializes serve_addr to zero.*/
	bzero((char *) &serv_addr, sizeof(serv_addr));

/*Converts passed in argument to port number.*/
	portno = atoi(argv[1]);

/*Sets values of serv_addr struct*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

/*Binds socket to address of current host and port number.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nERROR on binding.\n\n");
		exit(1);
	}

/*Allows process to listen on socket and allows for 5 connections in queue.*/
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
	  perror(0);
	  exit(1);
	}

/*This loop continues the run and forks off processes as new connections are made to clients.*/
	while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			printf("\nERROR on accept.\n\n");
			exit(1);
		}
		pid = fork();
		if (pid < 0) {
			printf("\nERROR on fork.\n\n");
		}
/*Child process*/
		if (pid == 0)  {
			close(sockfd);
			encrypt(newsockfd);
			exit(0);
		}

		else {
			close(newsockfd);
		}

	}

	return 0;
}

/*This function handles the encryption for every child client connection.*/
void encrypt(int sock) {
    int numRead;
	int numWrite;
	char plainText[100000];
	char keyText[100000];
	char cipher[100000];
	char progName[15];
	char temp;
	int numProgChars = 0;
	int numPlainChars = 0;
	int numKeyChars = 0;
	int index = 0;

/*This loop reads in characters from the client. The first group of characters contain
the name of the client program making the connection. This group of characters is terminated
with an @ symbol.*/
	do {

		numRead = read(sock, &temp, 1);

		if (numRead < 0) {
			printf("\nERROR: Unable to read from socket.\n\n");
		}
		/*Exits out of while loop when @ character is encountered.*/
		if (temp == '@') {
			break;
		}
		else {
			/*Stores program name in array*/
			progName[numProgChars] = temp;
			numProgChars++;
			if(numProgChars > 20) {
				printf("\nERROR: INFINITE LOOP DETECTED WHEN READING PROG NAME.\n\n");
				exit(1);
			}

		}

	} while(1);

/*Checks if client program name matches disallowed client program.
If so, ends the connection.*/
	if (strstr(progName, "dec") != NULL) {
	    printf("\nERROR: otp_dec cannot use otp_enc_d, closing connection.\n\n");
		return;
	}

/*This do-while loop reads in the plaintext information from client. The ; character
indicates the end of the plaintext information.*/
	do {

		numRead = read(sock, &temp, 1);

		if (numRead < 0) {
			printf("\nERROR: Unable to read from socket.\n\n");
		}

		if (temp == ';') {
			break;
		}
		else {
			plainText[numPlainChars] = temp;
			numPlainChars++;
			if(numPlainChars > 100005) {
				printf("\nERROR: INFINITE LOOP DETECTED WHEN READING PLAINTEXT.\n\n");
				exit(1);
			}

		}

	} while(1);

/*This do-while loop reads in the key from the client. The $ character indicates the
end of the key information.*/
	do {

		numRead = read(sock, &temp, 1);

		if (numRead < 0) {
			printf("\nERROR: Unable to read from socket.\n\n");
		}

		if (temp == '$') {
			break;
		}
		else {
			keyText[numKeyChars] = temp;
			numKeyChars++;
			if(numKeyChars > 100005) {
				printf("\nERROR: INFINITE LOOP DETECTED WHEN READING KEYTEXT.\n\n");
				exit(1);
			}

		}

	} while(1);

	int ii = 0;
	int jj = 0;
	int plainVal = 0;
	int keyVal = 0;
	int cipherVal = 0;
	char set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

/*Assigns a value to every plain text and corresponding key text character.*/
	for (ii = 0; ii < numPlainChars; ii++) {
		for (jj = 0; jj < 27; jj++) {
			if( plainText[ii] == set[jj] ) {
				plainVal = jj;
			}
			if( keyText[ii] == set[jj] ) {
				keyVal = jj;
			}


		}

/*Sums the assigned values to calculate the index of the encrypted character.*/
		cipherVal = plainVal + keyVal;

		if(cipherVal > 26) {
			cipherVal = cipherVal - 27;
		}

/*Fills in encrypted array based on calculated index value of encrypted character.*/
		cipher[ii] = set[cipherVal];

	}

/*Writes encrypted information to client.*/
	numWrite = write(sock, cipher, numPlainChars);
	if (numWrite < 0) {
		printf("\nERROR: Unable to write to socket.\n\n");
		exit(1);
	}

	return;
}