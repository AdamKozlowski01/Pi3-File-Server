/*********************************************
* ConnectionFactory.h
* Created By: Adam Kozlowski
* Last Updated: 8/6/2016
* Factory for creating different kinds of connections
*
*
*********************************************/
#ifndef CONNECTION_FACTORY_H
#define CONNECTION_FACTORY_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "ThreadPool.h"

class Connection{
private:
protected:
	bool running;
	
public:
	virtual void* connectionProtocol() = 0;
	virtual void endConnection() = 0;
	friend void* connectionStart(void* arg){
		return static_cast<Connection*>(arg)->connectionProtocol();
	}
	bool isRunning(){ 
		return running;
	}
};

class EchoConnection : public Connection{
private:
	ThreadPool* deadPool;
	int connection_fd;
	int threadIndex;
	void run();
protected:
public:
	EchoConnection(int fileDescrptr, ThreadPool* tp);
	~EchoConnection();
	void* connectionProtocol();
	void endConnection();
};

class StandardConnection : public Connection{
		//set up key exchange for the session
		
		//ask for credentials

		//check credentials or if create account mode, ask to create credentials

		//send names of all folders in user's file
		//process requests until connection time out or ends
};

class ConnectionFactory{
private:
protected:
public:
	virtual Connection* createConnection(int fileDescrptr) = 0;
};

class EchoFactory : public ConnectionFactory{
private:
	ThreadPool* deadPool;
protected:
public:
	EchoFactory(ThreadPool* tp){deadPool = tp;}
	~EchoFactory();
	Connection* createConnection(int fileDescrptr);
};

class ConnectionFactory_v1 : public ConnectionFactory{

private:
	ThreadPool* deadPool;
protected:
public:
	ConnectionFactory_v1(ThreadPool* tp){deadPool = tp;}
	~ConnectionFactory_v1();
	/*Connection* createConnection(int fileDescrptr){
		//creates a connection object, and runs it on a thread
		//returns the connection info to the main thread
	}*/
};

#endif