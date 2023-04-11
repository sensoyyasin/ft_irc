#include "Server.hpp"

Server::Server()
{
	this->opt = 1;
	this->rv = 0;
	this->timeout = (3 * 60 * 1000);
	this->join_key = 0;
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
	this->addr_len = sizeof(this->address);
	this->buffer[BUFFER_SIZE] = 0;
}

void	Server::socketOperations(Server &server)
{
	/* Create a master socket */
	if ((server.server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}

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
	/* Creating socket and checking the address. */
	server.address.sin_family = AF_INET; //IPV4
	server.address.sin_addr.s_addr = INADDR_ANY;
	server.address.sin_port = htons(atoi(argv[1]));

	if (bind(server.server_fd, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		exit(1);
	}

	if (listen(server.server_fd, MAX_CLIENTS) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(1);
	}
	pollfds.push_back((pollfd){server.server_fd, POLLIN, 0});
}

void	Server::parser(Server &server)
{
    std::string str = server.buffer;
	int	del_place = str.find(" ");
	std::string token = str.substr(0, del_place);
	std::string args = str.substr(del_place + 1); 
	if (token == "JOIN")
	{
		//server.join_key = std::stoi(str);
	}
	if (token ==  "QUIT" || token == "EXIT")
	{
		std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		close(server.new_socket);
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