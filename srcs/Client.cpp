#include "../headers/Client.hpp"

Client::Client(int fd, int port)
{
	this->status = 0;
	this->fd = fd;
	this->port = port;
}

Client::~Client() {}
