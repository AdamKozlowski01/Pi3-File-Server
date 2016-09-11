/*********************************************
* Server.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* A server class which stores relevant information about the server
* And runs all of the Systems needed
*
*
*********************************************/

#include "Server.h"


FileServer_v1::~FileServer_v1(){
	//Tear Down
	close(socket_fd);
	delete cHandler;
	delete deadPool;
	
}

FileServer_v1::FileServer_v1(){
	//Setup
	port = 1081;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(port);
		
	deadPool = new ThreadPool_v1();
	cHandler = new FileConnectionHandler_v1(socket_fd, deadPool);

	bind(socket_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
}

void FileServer_v1::run(){
	//Starts the server

	std::cout <<
" ___________________________________________\n"<<
"|*******************************************|\n"<<
"|*                                         *|\n"<<
"|* |||\\\\  ---------  ||||||||||  --------- *|\n"<<
"|* ||| \\\\ ---------  |||         --------- *|\n"<<
"|* ||| //    |||     |||            |||    *|\n"<<
"|* |||//     |||     ||||||||       |||    *|\n"<<
"|* |||       |||     |||            |||    *|\n"<<
"|* |||       |||     |||            |||    *|\n"<<
"|* |||    ---------  |||         --------- *|\n"<<
"|* |||    ---------  |||         --------- *|\n"<<
"|*                                         *|\n"<<
"|*******************************************|\n"<<
" -------------------------------------------\n"<<
"\tWelcome to PiFi Sever\n"<<
"    Created By Adam Kozlowski\n";

	listen(socket_fd, 20);
	std::cout <<"Listening on port " << port << "...\n";
	while(true){
		cHandler->handle();
	}

} 

void FileServer_v1::shutdown(){
	//safely shuts down the server

	close(socket_fd);
	delete cHandler;
	delete deadPool;
} 

int main(){
	Server* server = new FileServer_v1();
	server->run();
}
