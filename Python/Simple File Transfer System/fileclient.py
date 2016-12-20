#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 11/23/2016
#   Last Modification Date:       11/27/2016
#   Filename:                     ftclient.py
#
#   Overview:   This program serves as a TCP client which connects to a C server. 
#               
#
#   Input:  The input shall consist of a server address, a port number, a command,
#			and possible filename to be retreived from the server.
#
#   Output: The output of the program will be messages sent from the server and possible 
#			file creation.
#***************************************************************************************/

import sys
import os
import random
from socket import *

RECVBUFRSIZE = 4096
serverHost = sys.argv[1]
serverPort = sys.argv[2]
command = sys.argv[3]
filename = "NONE"

#This portion initially does client-side command line argument validation
if len(sys.argv) < 5 or len(sys.argv) > 6:
	sys.exit("ERROR: Incorrect number of command line arguments. Please try again.")

if not serverPort.isdigit():
	sys.exit("ERROR: Server Port must be an integer between 0 and 65535. Please try again.")

if int(serverPort) < 0 or int(serverPort) > 65535:
	sys.exit("ERROR: Server Port must be an integer between 0 and 65535. Please try again.")

if not command in ('-l', '-g'):
	sys.exit("ERROR: You have entered an incorrect command, only '-l' or '-g' are acceptable commands. Please try again.")

if command == "-l":
	dataPort = sys.argv[4]
else:
	filename = sys.argv[4]
	dataPort = sys.argv[5]
	
if not dataPort.isdigit():
	sys.exit("ERROR: Data Port must be an integer between 0 and 65535. Please try again.")
if int(dataPort) < 0 or int(dataPort) > 65535:
	sys.exit("ERROR: Data Port must be an integer between 0 and 65535. Please try again.")

#Appends the entered command line args into a single string
msg = command + filename + "|" + dataPort

# Sets up the socket and connects to the server and sends the command line args
# This also serves as the TCP control connection between client and server
# Design influenced from here:
# http://www.informit.com/articles/article.aspx?p=2234249
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverHost, int(serverPort)))
clientSocket.send(msg)

#Use of this unblocking mechanism influenced by http://stackoverflow.com/questions/9770567/python-tcp-socket-blocks-on-recv-method
clientSocket.settimeout(2)

# Reads error message from server, passing errors influenced by https://docs.python.org/3.3/tutorial/errors.html
try:
	readMsg = clientSocket.recv(RECVBUFRSIZE)
	if readMsg:
		print readMsg
except:
	pass

# Creates and binds socket for TCP data connection. Design influenced from here:
# http://www.informit.com/articles/article.aspx?p=2234249
dataSocket = socket(AF_INET, SOCK_STREAM)
dataSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
dataSocket.bind(('', int(dataPort)))
dataSocket.listen(5)
print "The client is ready to receive data from server"

# Flag is used to check if prog is executing through the While loop for the 1st time
flag = 0

# Flag is used to check if file already exists in client directory.
flag2 = 0

connectionSocket, addr = dataSocket.accept()

# Prevents socket from blocking
connectionSocket.settimeout(2)

originalfile = filename

# Opens file for writing if user entered -g command
# Also prepends a random integer to the front of the filename if one already exists in the directory
if command == "-g":
	if os.path.isfile(filename):
		flag2 = 1
		filename = str(random.randint(0,999)) + filename 
		f = open(filename, 'a')
	else:
		f = open(filename, 'a')

#While loop design influenced by discussion here: http://code.activestate.com/recipes/408859-socketrecv-three-ways-to-turn-it-into-recvall/
while True:
	if command == "-l":
	# Receives directory list data over data connection
		data = connectionSocket.recv(RECVBUFRSIZE)
		if data:
			if flag == 0:
				print 'TCP Data Connection created with', serverHost, ':', dataPort
				print 'Receiving directory structure from', serverHost, ':', dataPort
				flag = 1
			print data
			continue;
		else:
			break
	else:
# Reads error message from serer, passing errors influenced by https://docs.python.org/3.3/tutorial/errors.html
		try:
		#Receives error message over control connection
			readMsg = clientSocket.recv(RECVBUFRSIZE)
			if readMsg:
				print serverHost, ':', serverPort, 'says', readMsg
				os.remove(filename)
				break
		except:
			pass
		# Receives file data over data connection
		data = connectionSocket.recv(RECVBUFRSIZE)
		if data:
			if flag == 0:
				if flag2 == 1:
					print originalfile,'already exists in client working directory. Prepending random number to filename'
				print 'TCP Data Connection created with:', serverHost, ':', dataPort
				print 'Receiving "',originalfile,'" from', serverHost, ':', dataPort
				flag = 1
			f.write(data)
			continue;
		else:
			print "File transfer complete."
			#Closes file
			f.close()
			break

# Closes all sockets
connectionSocket.close()
clientSocket.close()
dataSocket.close()