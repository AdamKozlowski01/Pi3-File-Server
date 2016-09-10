/*********************************************
* ConnectionHandler.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* Connection Handling class for servers
*
*
*********************************************/

#include "ConnectionHandler.h"


FileConnectionHandler_v1::FileConnectionHandler_v1(int socketfd, ThreadPool& tp){
	//set up
	socket_fd = socketfd;
	deadPool = tp;
	connMaker = new EchoFactory(deadPool);
	connections = new std::vector<Connection*>;
}
FileConnectionHandler_v1::~FileConnectionHandler_v1(){
	//tear down'

	delete connMaker;
	delete connections;
}
void FileConnectionHandler_v1::handle(){
	//handles accept() and requests thread resources
	conn_fd = accept(socket_fd, (struct sockaddr *) NULL, NULL);

	if(conn_fd < 0){
		std::cerr << connErrMsg;
	}
	else{
		//get a new thread and process the connection
		connections->push_back(connMaker->createConnection(conn_fd));
	}

	//iterate through the list of connections, for any not running delete the pointers
	for(int i = 0; i < connections->size(); i++){ //Could maybe be put in it's own thread?
		if(!connections[i]->isRunning())
			connections[i]->endConnection();
	}
}