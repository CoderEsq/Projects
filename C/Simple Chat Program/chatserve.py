#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 10/24/2016
#   Last Modification Date:       10/27/2016
#   Filename:                     chatserve.py
#
#   Overview:   This program serves as a TCP server which connects to a C client. 
#               Messages to and from the client and server are exchanged.
#
#   Input:  The input shall consist of a integer as a command line argument which is the 
#           port number the server should listen on as well as input from the user in the 
#           form of messages to be sent to the client.
#
#   Output: The output of the program will be a chat screen containing messages from 
#           the client and also messages sent to the client.
#***************************************************************************************/

import sys
from socket import *

#*********************************************************************
#* Function: startUp
#* Description: Function used to read in port number and bind socket, 
#* also sets socket to listen.
#* Parameters: serverSocket (socket)
#* Pre-Conditions: A socket has been created and user enteted port number.
#* Post-Conditions: Socket is listening on a port for incoming TCP client
#********************************************************************/
def startUp(serverSocket):
    #Converts passed in argument to port number.
    serverPort = int(sys.argv[1])

    # Creates and binds socket. Design influenced from here:
    # http://www.informit.com/articles/article.aspx?p=2234249
    
    serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    serverSocket.bind(('',serverPort))
    serverSocket.listen(1)

    print "The server is ready to receive"

#*********************************************************************
#* Function: readMessage
#* Description: Function used to read and print messages sent from client.
#* Parameters: readMsg (string), connectionSocket (socket), MSGSIZE (max size of msg)
#* Pre-Conditions: Socket has been created and is listening for messages
#* Post-Conditions: Messages have been printed to the screen
#********************************************************************/
def readMessage(readMsg, connectionSocket, MSGSIZE):
    readMsg = connectionSocket.recv(MSGSIZE)
    if readMsg:
        print readMsg

    return readMsg

#*********************************************************************
#* Function: sendMessage
#* Description: Function used to receive user input and send message to
#* client.
#* Parameters: sendMsg(string), connectionSocket(socket)
#* Pre-Conditions: Socket has been created and is prepared to send messages
#* Post-Conditions: Messages sent to client
#********************************************************************/
def sendMessage(sendMsg, connectionSocket):
    handle = "Host A> "
    #Accepts message input from user
    sendMsg = raw_input(handle)
    sendMsg = "Host A> " + sendMsg

    #Sends user message to client.
    connectionSocket.send(sendMsg)

    return sendMsg

# Maximum size of send and received messages.
MSGSIZE = 1024
serverSocket = socket(AF_INET, SOCK_STREAM)

#Function sets up server to listen to client on socket.
startUp(serverSocket)

# While loop executes while server is running
while True:
# This flag indicates whether the server has received an initial message
    flag = 0
    print "Waiting for connection from client..."
    connectionSocket, addr = serverSocket.accept()
    print 'TCP Connection created with:', addr
    print

# Reads initial message from client
    readMsg = connectionSocket.recv(MSGSIZE)

# This IF loop only executes to print the initial message received from the
# client.
    if (readMsg and flag == 0):
        flag = 1
        print readMsg

# This while loop runs to continuously read and write messages
# "Quit" messages entered by the user into the server are passed 
# onto the client so the client can close the connection. This is due avoid 
# "Address in Use" error described here: 
# http://hea-www.harvard.edu/~fine/Tech/addrinuse.html */
    while True:

        #Function reads messages sent from client and prints to screen.
        readMsg = readMessage(readMsg, connectionSocket, MSGSIZE)

        if "quit" in readMsg:
            print "CLOSING CONNECTION..."
            break

        #Function sends messages from server to client and prints to screen.
        sendMsg = " "
        sendMsg = sendMessage(sendMsg, connectionSocket)
        if sendMsg == "Host A> \\quit":
            print "CLOSING CONNECTION..."
        #Break statement escapes inner loop and returns server to listen state.
            break

        continue


    connectionSocket.close()