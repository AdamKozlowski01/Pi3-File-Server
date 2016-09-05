/*********************************************
* Server.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* A server class which stores relevant information about the server
* And runs all of the Systems needed
*
*
*********************************************/

#include <netinet/in.h>
#include <sys/socket.h>

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

	~FileServer_v1(){
		//Tear Down
		//TO-DO
	}
protected:
public:
	FileServer_v1(){
		//Setup
		//TO-DO
	}
	void run(){
		//Starts the server
		//TO-DO

	} 
	void shutdown(){
		//safely shuts down the server
		//TO-DO
	} 
};