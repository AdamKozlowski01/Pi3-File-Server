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
#include <unistd.h>
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

	~FileServer_v1(){
		//Tear Down
	}
protected:
public:
	FileServer_v1(){
		//Setup
		port = 1081;

		socket_fd = socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));

		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s = htons(INADDR_ANY);
		servaddr.sin_port = htons(port);
		
		deadPool = new ThreadPool_v1();
		cHandler = new ConnectionHandler_v1(socket_fd);

		bind(socket_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	}

	void run(){
		//Starts the server
		listen(server_fd, 20);
		while(true){
			cHandler.handle();
		}

	} 

	void shutdown(){
		//safely shuts down the server
		close(server_fd);
		~FileServer_v1();
	} 
};