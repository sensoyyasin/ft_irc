#include "server.hpp"

Server::Server()
{
	this->opt = 1;	
	memset(buffer, 0, BUFFER_SIZE);
	for(int i = 0; i < MAX_USR; i++)
		client_fd[i] = -1;
}

Server::~Server(){}

void  Server::appointment(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Arg Error." << std::endl;
		exit(1);
	}
	this->my_port = std::stoi(argv[1]);
	this->my_password = argv[2];
	//this->my_password = argv[1];
	//this->my_port = std::stoi(argv[2]);
	this->addr_len = sizeof(this->address);
}

void	Server::socketOperations(Server &server)
{
	/* Create a socket */
	if ((server.server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}

	//setsockopt   araştır
	//listen
	//bind,
	//struct sockaddr_in

	/* Set master socket to allow multiple connections */
	if (setsockopt(server.server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server.opt, sizeof(server.opt)) != 0)
		std::cout << "Setsockopt set up and connecting to server..." << std::endl;
	else
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2(Server &server, char **argv)
{
	server.address.sin_family = AF_INET; //IPV4// inceleee!!!
	server.address.sin_addr.s_addr = INADDR_ANY;// inceleee!!!
	server.address.sin_port = htons(atoi(argv[1]));// inceleee!!!

	if (bind(server.server_fd, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		exit(1);
	}

	if (listen(server.server_fd, MAX_USR) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(1);
	}
}

/* GETTER AND SETTER ON THE WAY -_- */
int	Server::getmyport()
{
	return(this->my_port);
}

std::string	Server::getmypassword()
{
	return (this->my_password);
}