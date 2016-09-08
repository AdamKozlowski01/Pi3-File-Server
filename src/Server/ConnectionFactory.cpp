/*********************************************
* ConnectionFactory.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/6/2016
* Factory for creating different kinds of connections
*
*
*********************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>

class Connection{
private:
protected:
	bool running;

	friend void* connectionStart(void* arg){
		return static_cast<Connection*>(arg)->connectionProtocol();
	}
public:
	virtual void* connectionProtocol() = 0;
	bool isRunning(){ 
		return running;
	}

};

class EchoConnection : public Connection{
private:
	ThreadPool* deadPool;
	int connection_fd;
	int threadIndex;

	void run(){
		while(threadIndex < 0){
			threadIndex = deadPool->allocThread(connectionStart, this);
		}
		running = true;
	}

protected:
public:
	Connection(int fileDescrptr, ThreadPool& tp){ 
		connection_fd = fileDescrptr; 
		deadPool = tp;
		threadIndex = -1;

		run();
	}

	~Connection(){
		deadPool->freeThread(threadIndex);
	}

	void* connectionProtocol(){
		char str[100];
		char quitStr = "end";

		while(true){
			bzero(str, 100);

			read(connection_fd, str, 100);

			if(!(strcmp(str, quirStr)))
				break;

			printf("Echoing back - %s", str);
			write(connection_fd, str, strlen(str)+1);
		}
		running = false;
		pthread_exit();
	}
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
	EchoFactory(ThreadPool& tp){deadPool = tp;}
	~EchoFactory(){}

	Connection* createConnection(int fileDescrptr){
		Connection* connection = new Connection(fileDescrptr, deadPool);
		return connection;
	}
};

class ConnectionFactory_v1 : public ConnectionFactory{

private:
	ThreadPool* deadPool;
protected:
public:
	ConnectionFactory_v1(ThreadPool tp){}
	~ConnectionFactory_v1(){}
	Connection* createConnection(int fileDescrptr){

		//creates a connection object, and runs it on a thread
		//returns the connection info to the main thread

	}
};