/**************************************************
* Client.cpp                                      *
* Made By: Adam Kozlowski                         *
*                                                 *
* A PiFi Client for connecting to the PiFi Server *
**************************************************/
#include "Client.h"

Client::Client(int port_num){
	port = port_num;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof servaddr);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port=htons(port);

	inet_pton(AF_INET,"127.0.0.1", &(servaddr.sin_addr));
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
}

void Client::run(){
	char quit[] = "end";
	bzero(send, 100);
	bzero(recv, 100);

	while(true)//!strcmp(send, quit))
	{
		bzero(send, 100);
		bzero(recv, 100);
		fgets(send, 100, stdin);

		write(sockfd, send,strlen(send)+1);
		read(sockfd,recv, 100);
		printf("%s", recv);

	}
}


int main(){
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
"\tWelcome to PiFi Client\n"<<
"    Created By Adam Kozlowski\n";

	Client* c = new Client(1081);
	c->run();
}