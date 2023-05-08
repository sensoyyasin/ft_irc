#include "../headers/Client.hpp"

<<<<<<< HEAD
Client::Client(int fd, int port)
{
	this->status = 0;
	this->fd = fd;
	this->port = port;
=======
Client::Client(int fd, std::string username,std::string hostname, std::string servername, std::string realname, std::string nickname)
{
	this->fd = fd;
	this->username = username;
	this->nickname = nickname;
	this->realname = realname;
	this->hostname = hostname;
	this->servername = servername;
	
	this->setStatus(1);
>>>>>>> 28184583832779898723191b451770961cc0f9db
}

Client::~Client() {}
