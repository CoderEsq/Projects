/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 10/24/2016
*   Last Modification Date:       10/30/2016
*   Filename:                     chatclient.c
*
*   Overview:   This program serves as a TCP client which connects to a python server. 
*                Messages from the client and server are exchanged.
*
*   Input:  The input shall consist of 2 command line arguments, a string which is the 
*           server name and an integer which is the port number the client should connect 
*           to. The user will also enter a string which is the handle of the client as 
*           well as input from the user in the form of messages to be sent to the server.
*
*   Output: The output of the program will be a chat screen containing messages received 
*           from the client and also messages sent to the server.
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#define MSGSIZE 1024

/*********************************************************************
** Function: startup
** Description: Function used to establish connection with server.
** Parameters: socket and port number integers along with the sockaddr_in 
** 			 struct are passed into the function.
** Pre-Conditions: user has entered port number
** Post-Conditions: TCP connection established with server
*********************************************************************/
void startup(int sock, struct sockaddr_in *serv_addr, int pnum);

/*********************************************************************
** Function: sendMessage
** Description: Function used to send messages to server
** Parameters: integer for socket and char array containing message
** Pre-Conditions: user has entered message to send, connection established
** Post-Conditions: message sent to server through TCP connection
*********************************************************************/
void sendMessage(int sock, char* message);

/*********************************************************************
** Function: recvMessage
** Description: Function used to check if client has received message
** Parameters: integer for socket and char array containing message. Also 
**				pointer to an integer serves as a flag so client and server 
**				can take turns sending messages
** Pre-Conditions: TCP connection has been established
** Post-Conditions: If client has received a message, it will be printed to the screen
*********************************************************************/
void recvMessage(int sock, char* message, int* marker);

int main(int argc, char *argv[]) {


    char handle[30];
    char handleTemp[30];
    char handleNotat[30];
    char notation[] = "> ";
    

    printf( "Enter client handle: ");

    /*Asks user for handle name*/
    fgets(handle, 10, stdin);

    /*Removes newline characters from handle, influence for this code design came from: 
    http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input */
    handle[strcspn(handle, "\r\n")] = 0;
    strncpy(handleTemp, handle, sizeof(handleTemp));

    /*Appends > notation to end of handle*/
    strncat(handle, notation, strlen(notation));
    strncpy(handleNotat, handle, sizeof(handleNotat));

    int numRead;
    /*
	int numWrite;
	*/
    int sockfd;
	int portno;
    struct sockaddr_in serv_addr;
	struct hostent *server;

	char readMsg[MSGSIZE];
	char sendMsg[MSGSIZE];
    
	char *hostname;

    /*The design of this program was influenced from Beej's Guide: 
    http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#simpleclient */
    /*Reads in values from command line for hostname and port number*/
     /*Sets address of host.*/
    hostname = argv[1];

    /*Converts passed in argument to port number.*/
	portno = atoi(argv[2]);

    /*Creates new socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server = gethostbyname(hostname);

	/*Sets values of serv_addr struct*/
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	
/*Establishes connection to server.*/
	startup(sockfd, &serv_addr, portno);

    char connectmsg[] = " has connected.";

    strncat(handleTemp, connectmsg, strlen(connectmsg));
    printf("%s\n", handleTemp);

    /*Sends client name and connection msg to server as an initial message.*/
    sendMessage(sockfd, handleTemp);

    char quit[] = "\\quit";
    int flag = 0;

    /*This while loop runs while the client is active.*/
    while (1) {
        
        if (flag % 2 == 1) {
        	recvMessage(sockfd, readMsg, &flag);
        	continue;
        }
        
        /*This Else IF loop runs only after the client recevies a message. The client can 
        only write a message to the server by taking turns sending and receiving messages 
        with the server.*/
        else if (flag % 2 == 0) {
                flag++;
                char sendMsgNotat[MSGSIZE];
                strncpy(sendMsgNotat, handleNotat, sizeof(sendMsgNotat));
                printf("%s", handleNotat);
                bzero(sendMsg, MSGSIZE);
                fgets(sendMsg, MSGSIZE, stdin);
                sendMsg[strcspn(sendMsg, "\r\n")] = 0;
                /*Concatenates user input to end of user handle and notation.*/
                strncat(sendMsgNotat, sendMsg, strlen(sendMsg));
                sendMsgNotat[strcspn(sendMsgNotat, "\r\n")] = 0;

                /*Sends client message to server.*/
                sendMessage(sockfd, sendMsgNotat);
                continue;
        }

     }

    close(sockfd);

    return 0;
}



void startup(int sock, struct sockaddr_in *serv_addr, int pnum) {

	if (connect(sock, (struct sockaddr *) serv_addr, sizeof(struct sockaddr_in)) < 0) {
	fprintf(stderr, "\nERROR: Unable to connect to port %d.\n\n", pnum);
	exit(2);
	}

}

void sendMessage(int sock, char* message) {
	int numWrite;
    numWrite = write(sock, message, strlen(message));
    if (numWrite < 0) {
        printf("\nERROR: Unable to write to socket.\n\n");
        exit(1);
    }

    /*This IF loop checks if the client has sent a quit message to the server.
    If so, the client closes the connection and exits.*/
    if (strstr(message, "\\quit") != NULL) {
        /*Closes socket.*/
        printf("\nCLOSING CONNECTION...\n");
        close(sock);
        exit(0);
    }
}

void recvMessage(int sock, char* message, int* marker) {
	bzero(message, MSGSIZE);
	/*This IF loop checks if the client has recevied a message from the server,
    and then prints the messages to the screen if it has received a message.*/
	if (recv(sock, message, MSGSIZE, MSG_DONTWAIT) > 0 && (*marker) % 2 == 1) {
            (*marker)++;
            printf("%s\n", message);
            message[strcspn(message, "\r\n")] = 0;

        /*This IF loop checks if the client has recevied a quit message from the server.
        If so, the client closes the connection and exits. The client will always be the one to 
        close the connection, even if the server is the one who enters the "quit" 
        command. This is to avoid the "Address in Use" error described here: 
        http://hea-www.harvard.edu/~fine/Tech/addrinuse.html */
            if (strstr(message, "\\quit") != NULL) {
                /*Closes socket.*/
                printf("\nCLOSING CONNECTION...\n");
                close(sock);
                exit(0);
            }
        bzero(message, MSGSIZE);

	}	

}