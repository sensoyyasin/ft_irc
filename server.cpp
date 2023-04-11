#include "server.hpp"

Server::Server(int argc, char **argv)
{
	appointment(argc, argv);
	std::cout << "Starting IRC server on port " << std::endl;
	
	socketOperations();
	socketOperations2(argv);
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
}

void	Server::socketOperations()
{
	/* Create a socket */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0)
		std::cout << "Setsockopt set up and connecting to server..." << std::endl;
	else
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2(char **argv)
{
	address.sin_family = AF_INET; //IPV4// inceleee!!!
	address.sin_addr.s_addr = INADDR_ANY;// inceleee!!!
	address.sin_port = htons(atoi(argv[1]));// inceleee!!!

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		exit(1);
	}

	if (listen(server_fd, MAX_USR) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(1);
	}
	pollfds.push_back((pollfd){server_fd, POLLIN, 0});
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

void	Server::parser()
{
    std::string str = buffer;
	int	del_place = str.find(" ");
	std::string token = str.substr(0, del_place);
	std::string args = str.substr(del_place + 1);

	std::cout << "Token recieved: " << token << std::endl;
	std::cout << "Args: " << args << std::endl;
	if (token == "JOIN")
	{
		//join_key = std::stoi(str);
	}
	if (token ==  "QUIT" || token == "EXIT")
	{
		std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		exit(1);
	}
}

void	Server::newClient()
{
	buffer.clear();
	int	addr_len = sizeof(address);
	int new_socet = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (new_socet < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return ;
	}
	pollfds.push_back((pollfd){new_socet, POLLIN, 0});
}

void	Server::executeCommand(int fd)
{
	if (buffer.find("\n\r"))
	{
		buffer.clear();
		char buff[BUFFER_SIZE];
		memset(buff, 0, BUFFER_SIZE);
		int bytes_received = recv(fd, buff, BUFFER_SIZE, 0); 
		if (bytes_received < 0)
		{
			std::cerr << "Receive failed" << std::endl;
			return ;
		}
		buffer = std::string(buff);
		parser();
	}
}
void	Server::loop()
{
	std::string message;
	while (1)
	{
		poll(pollfds.begin().base(), pollfds.size(), -1);
		for (size_t i = 0 ; i < pollfds.size() ; i++)
		{
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == pollfds[0].fd)
				{
					newClient();
					break ;
				}
				executeCommand(pollfds[i].fd);
			}
		}
	}
}
