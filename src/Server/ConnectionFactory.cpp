/*********************************************
* ConnectionFactory.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/6/2016
* Factory for creating different kinds of connections
*
*
*********************************************/

#include "ConnectionFactory.h"


void EchoConnection::run(){
	while(threadIndex < 0){
		threadIndex = deadPool->allocThread(connectionProtocol, NULL);
	}
	running = true;
}

EchoConnection::EchoConnection(int fileDescrptr, ThreadPool* tp){ 
	connection_fd = fileDescrptr; 
	deadPool = tp;
	threadIndex = -1;

	run();
}

EchoConnection::~EchoConnection(){
	deadPool->freeThread(threadIndex);
	close(connection_fd);
}

void* EchoConnection::connectionProtocol(){
	char str[100];
	char quitStr[] = "end";

	while(true){
		bzero(str, 100);

		read(connection_fd, str, 100);

		if(!(strcmp(str, quitStr)))
			break;

		printf("Echoing back - %s", str);
		write(connection_fd, str, strlen(str)+1);
	}
	running = false;
	pthread_exit(NULL);
}

void EchoConnection::endConnection(){
	~EchoConnection();
}