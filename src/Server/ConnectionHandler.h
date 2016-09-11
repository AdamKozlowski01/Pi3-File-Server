/*********************************************
* ConnectionHandler.h
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* Connection Handling class for servers
*
*
*********************************************/
#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "ThreadPool.h"
#include "ConnectionFactory.h"

class ConnectionHandler{
//Abstract Connection Handler
private:
protected:
	int socket_fd, conn_fd;
public:
	virtual void handle() = 0;
};

class FileConnectionHandler_v1: public ConnectionHandler{
//Implementation of Connection Handler
private:
	//Sub-systems go here
		//Connection Factory
		//Pointer to Thread-Pool?
		//vector or list of connections
	ThreadPool* deadPool;
	ConnectionFactory* connMaker;
	std::vector<Connection*>* connections;

protected:
public:
	FileConnectionHandler_v1(int& socketfd, ThreadPool* tp);
	~FileConnectionHandler_v1();
	void handle();
};

#endif