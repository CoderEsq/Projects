Two separate PuTTy instances should be used to test this program. One instance 
to execute the server and another instance to execute the client. These 
instances should be run on separate servers such as flip1 and flip2. The server 
should be executed first before the client. The server is implemented through 
the file fileserver.c .

To compile the file, use the following command:

	gcc -o fileserver fileserver.c

Alternatively, a makefile has been included and the chatclient can be compiled 
by executing the following command:
	
	make all

The user designates a port on the command line which the server will use to 
listen for an incoming TCP control connection. An example command to setup 
and run the server is as follows:

	./fileserver 54222

where fileserver is the filename of the program and 54222 is the port number.
The server must be running before the client can try and connect to it.

------------------------------------------------------------------------------

The client is implemented though the file fileclient.py . To execute the client 
program, the user designates the hostname and port number 
on the command line. An example command to execute the client is as follows:

	python fileclient.py flip1.engr.oregonstate.edu 54222 -l 32626

where fileclient.py is the name of the program followed by the 
hostname of the server to which the user wishes to connect, and 54222 is the 
port number of the server. The -l command line argument commands the server 
to send the directory listing of the directory in which the server is located. 
The final number indicates the port on which the data connection from the server 
to the client should be made. The client may also request that the server send a 
file to the client by using the -g command followed by the filename of the file 
requested which should appear before the data port.