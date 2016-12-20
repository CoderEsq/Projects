Two separate PuTTy instances should be used to test this program. One instance 
to execute the server and another instance to execute the client. The server 
should be executed first before the client.

The server is implemented through the file chatserve.py . The user designates 
a port on the command line which the server will use to listen for an 
incoming TCP connection. An example command to setup and run the server is as 
follows:

	python chatserve.py 54222

where chatserve.py is the filename of the program and 54222 is the port number.
The server must be running before the client can try and connect to it.

------------------------------------------------------------------------------

The client is implemented though the file chatclient.c . To compile the file, 
use the following command:

	gcc -o chatclient chatclient.c

Alternatively, a makefile has been included and the chatclient can be compiled 
by executing the following command:
	
	make all

To execute the client program, the user designates the hostname and port number 
on the command line. An example command to execute the client is as follows:

	./chatclient localhost 54222

where chatclient is the name of the compiled executable, localhost is the 
hostname of the server to which the user wishes to connect, and 54222 is the 
port number of the server.