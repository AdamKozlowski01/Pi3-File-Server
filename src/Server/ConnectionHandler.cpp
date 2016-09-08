/*********************************************
* ConnectionHandler.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* Connection Handling class for servers
*
*
*********************************************/

#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream.h>

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

	std::string connErrMsg = "Could Not Accept Connection\n";

protected:
public:

	FileConnectionHandler_v1(int socketfd){
		//set up
		socket_fd = socketfd;
	}
	~FileConnectionHandler_v1(){
		//tear down
	}
	void handle(){
		//handles accept() and requests thread resources
		conn_fd = accept(socket_fd, (struct sockaddr *) NULL, NULL);

		if(conn_fd < 0){
			std::cerr << connErrMsg;
		}
		else{
			//get a new thread and process the connection
		}
	}
};