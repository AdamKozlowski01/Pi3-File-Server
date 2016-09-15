/**************************************************
* Client.h                                        *
* Made By: Adam Kozlowski                         *
*                                                 *
* A PiFi Client for connecting to the PiFi Server *
**************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>


class Client{
private:
protected:
	int port, sockfd, n;
	char send[100];
	char recv[100];
	struct sockaddr_in servaddr;

public:
	Client(int port_num);
	void run();
};