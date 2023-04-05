#ifndef SERVER_HPP
# define SERVER_HPP

#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define BUFFER_SIZE 1024

class server
{
private:
	/* data */
public:
	server();
	~server();
};

server::server(/* args */)
{
	std::cout << "Server has been destroyed" << std::endl;
}

server::~server()
{
	std::cout << "Server has been created" << std::endl;
}


#endif