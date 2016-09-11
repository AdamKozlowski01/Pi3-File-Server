/*********************************************
* Server.h
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* A server class which stores relevant information about the server
* And runs all of the Systems needed
*********************************************/

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "ConnectionHandler.h"
#include "ThreadPool.h"

class Server{
/* The Server Interface */
private:
protected:
	int socket_fd, port, pId; //socket, port number, process ID
public:
	virtual void run() = 0;
	virtual void shutdown() = 0;

};

class FileServer_v1: public Server{
	/* implementation of Server using IPv4*/
private:
	/* Systems go here */
	struct sockaddr_in servaddr;
	ThreadPool* deadPool;
	ConnectionHandler* cHandler;
	~FileServer_v1();
protected:
public:
	FileServer_v1();
	void run();
	void shutdown();
};