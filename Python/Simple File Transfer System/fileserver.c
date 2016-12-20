/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 11/23/2016
*   Last Modification Date:       11/27/2016
*   Filename:                     ftserver.c
*
*   Overview:   This program serves as a TCP server which connects to a python client. 
*               
*
*   Input:  The input shall consist of a integer as a command line argument which is the 
#           port number the server should listen on.
*
*   Output: The output of the program will be a file  or directory information sent to the
*			client.
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
#include <netdb.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>


#define MINPORT 0
#define MAXPORT 65535
#define BUFRSIZE 1024

int main(int argc, char *argv[]) {

	/*Checks that the minimum number of arguments has been entered*/
	if(argc < 2) {
		printf("\nPlease enter a Port Number. Please try again.\n\n");
		exit(1);
	}

	int portNum;

	char numSet[] = "0123456789";

	// Checks that the port number only contains numeric digits
	if (strlen(argv[1]) != strspn(argv[1], numSet)) {
		printf("\nPlease enter a positive integer for the Port Number. Please try again.\n\n");
		exit(1);
	}
	else {
		/*Converts passed in argument to integer for port number.*/
		portNum = atoi(argv[1]);

		if (portNum < MINPORT || portNum > MAXPORT) {
			printf("\nPlease enter a valid Port Number between 0 and 65535. Please try again.\n\n");
			exit(1);
		}
	}

	printf("Server open on %d\n", portNum);

	int sockfd, newsockfd, numRead;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr, data_addr;
	char control[256];

/*Creates new socket*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
    	printf("\nERROR opening socket.\n\n");
		exit(1);
    }

/*Initializes serve_addr to zero.*/
	bzero((char *) &serv_addr, sizeof(serv_addr));

/*Sets values of serv_addr struct*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNum);

/*Binds socket to address of current host and port number.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nERROR on binding.\n\n");
		exit(1);
	}

/*Allows process to listen on socket and allows for 5 connections in queue.*/
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	//Catches termination command by supervisor
	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
	  perror(0);
	  exit(1);
	}

	int readFile;
/*This loop continues to run while the server is running.*/
	while (1) {
		printf("\nWaiting for connection from client....\n\n");
		//Creates control connection with client
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			printf("\nERROR on accepting connection from client.\n\n");
			exit(1);
		}

		char clienthostname[1024];
		char clientservice[20];
		getnameinfo((struct sockaddr *) &cli_addr, sizeof cli_addr, clienthostname, sizeof clienthostname, clientservice, sizeof clientservice, 0);
		printf("Connection from %s\n", clienthostname);

		bzero(control,256);
		//Reads initial commands from client
		numRead = read(newsockfd, &control, 255);
		if (numRead < 0) {
			printf("\nERROR: Unable to read from socket.\n\n");
		}

		char command[5];
		char filename[256];
		char dPort[8];
		int dataPort;
		char * delimit;

		//Copies user command to string
		strncpy(command, control, 2);
		delimit = strchr(control,'|');
		//Copies and stores dataport
		strncpy(dPort, delimit+1, delimit - control);
		dataPort = atoi(dPort);
		int splicePoint = strlen(control) - strlen(dPort) - 3;
		//Copy and stores filename
		strncpy(filename, control+2, splicePoint);
		filename[splicePoint] = '\0';

		command[2] = '\0';
		
		int numSend;

		char badFile[] = "FILE NOT FOUND. Please try again.";

		//Checks if user entered a good command
		if (strcmp(command, "-l") == 0 || strcmp(command, "-g") == 0) {

			int datasockfd;
			struct sockaddr_in data_addr;
			struct hostent *dataserver;

			/*Creates new socket for TCP data connection*/
			datasockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (datasockfd < 0) {
				printf("\nERROR: Unable to open socket.\n\n");
			}

			//Gets hostname of client
			dataserver = gethostbyname(clienthostname);
			if (dataserver == NULL) {
				printf("\nERROR: No such host exists.\n\n");
			}
			

			/*Initializes data_addr to zero.*/
			bzero((char *) &data_addr, sizeof(data_addr));
			data_addr.sin_family = AF_INET;
			bcopy((char *)dataserver->h_addr, (char *)&data_addr.sin_addr.s_addr, dataserver->h_length);
			data_addr.sin_port = htons(dataPort);

			int optval = 1;

			//suggestion to sleep suggested by Joshua Caddell on discussion board to resolve connection issue.
			sleep(5);

			//Completes connection for TCP data connection with client
			if (connect(datasockfd, (struct sockaddr *) &data_addr, sizeof(data_addr)) < 0) {
			fprintf(stderr, "\nERROR: Unable to connect to port %d.\n\n", dataPort);
			}
			
			/*Design for this IF loop influenced from http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html */
			//Sends directory info to client
			if (strcmp(command, "-l") == 0) {
				printf("List directory requested on port %d.\n", dataPort);
				printf("Sending directory contents to %s:%d.\n", clienthostname, dataPort);
		  		DIR *directory;
			  	struct dirent *cwd;

			 	directory = opendir ("./");
			  	if (directory != NULL) {
			  		//Loop lists every file in directory and sends to client
		      		while (cwd = readdir(directory)) {
		      			//Design to add newline to end of string was influenced by discussion here: http://stackoverflow.com/questions/7195621/how-to-add-a-new-line-in-a-text-file
		      			char withNewline[80];
						withNewline[0] = 0;
		      			strcat(withNewline, cwd->d_name);
		      			//Newline character is appended to end of each directory listing
		      			strcat(withNewline, "\n");
		      			printf("%s", withNewline);
		      			numSend = send(datasockfd, withNewline, strlen(withNewline), 0);
						if (numSend < 0) {
							printf("\nERROR: Unable to write to socket.\n\n");
						}

		      		}
		      		(void) closedir(directory);
		    	}
		    	
		  		else {
		    		printf("\nERROR: Unable to open the current directory.\n\n");
		  		}

			}
			else {
				printf("File %s requested on port %d.\n", filename, dataPort);
				//Opens file on server for reading and sending to client
				readFile = open(filename, O_RDONLY);
				if (readFile == -1) {
			    	printf("\nERROR: File not found. Sending error message to %s:%d\n\n", clienthostname, dataPort);
			    	numSend = send(newsockfd, badFile, strlen(badFile), 0);
					if (numSend < 0) {
						printf("\nERROR: Unable to write to socket.\n\n");
					}
			    }
			    else {
			    	printf("Sending %s to %s:%d.\n", filename, clienthostname, dataPort);
			    	//STORES WRITE BUFFER
			    	char writeBuffer[BUFRSIZE];
			    	size_t bytesRead;
			    	//Design for this loop influenced from here: http://stackoverflow.com/questions/2014033/send-and-receive-a-file-in-socket-programming-in-linux-with-c-c-gcc-g
			    	while ( (bytesRead = read(readFile, writeBuffer, BUFRSIZE)) > 0) {
			    		numSend = send(datasockfd, writeBuffer, bytesRead, 0);
			    	}

			    }

			}
			//Closes all sockets and files
			close(readFile);
			close(newsockfd);
			close(datasockfd);
			continue;
		}
	//This block only executes if the user entered an invalid command that passed through client-side validation
	else {
		char badCommand[] = "You have sent an invalid command to the server. Please try again.";
		numSend = send(newsockfd, badCommand, strlen(badCommand), 0);
		if (numSend < 0) {
			printf("\nERROR: Unable to write to socket.\n\n");
		}
		close(newsockfd);
		continue;
	}

 	close(sockfd);
 	
 	}

	return 0;

}
