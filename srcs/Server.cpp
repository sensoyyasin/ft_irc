#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

Server::Server(int argc, char **argv)
{
	appointment(argc, argv);
	std::cout << "Starting IRC server on port " << std::endl;

	socketOperations();
	socketOperations2(argv);

	cap_ls[0] =  "ADD";
	cap_ls[1] =  "NICK";
	cap_ls[2] =  "JOIN";
	cap_ls[3] =  "QUIT";
	cap_ls[4] =  "CAP";
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
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));

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

void	Server::parser()
{
	std::string str = buffer;
	int	del_place = str.find(" ");
	std::string token = str.substr(0, del_place);
	std::string args = str.substr(del_place + 1);

	 if (cap_ls[0].find(token) != std::string::npos)
	 	add(*this, args);
	 else if (cap_ls[1].find(token) != std::string::npos)
		nick(*this, args);
	 else if (cap_ls[2].find(token) != std::string::npos)
		join(*this, args);
	 else if (cap_ls[3].find(token) != std::string::npos)
		quit(*this, args);
	 else if (cap_ls[4].find(token) != std::string::npos)
		cap(*this, args);
	else
	{
		std::cerr << "Invalid commands: " << token << std::endl;
		return;
	}
}

void	Server::newClient()
{
	buffer.clear();
	int	addr_len = sizeof(address);
	this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return ;
	}
	pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
	std::map<int, std::string>::iterator it;
	it = cap_ls.begin();
	while (it != cap_ls.end())
	{
		std::string str = "/";
		str += it->second;
		str += "\n\r";
		if (send(this->new_socket, str.c_str(), str.size(), 0) != str.size())
			std::cerr << "Error" << std::endl;
		++it;
	}
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

void Server::cap(Server &server, std::string line)
{
	(void)line; // protected our segmentation fault.
}

void Server::add(Server &server, std::string line)
{
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string token;

	while (std::getline(iss, token, ' ')) //Space parsing
		tokens.push_back(token);
	if (tokens.size() <= 1)
		return;
	Client new_client;
	for (int i = 0; i < tokens.size(); i++)
	{
		new_client.client_name = tokens[i];
		clients_.push_back(new_client);
	}
}

void Server::nick(Server &server, std::string str)
{
	if (clients_.empty())
		return;
	(void)str;
}

void Server::join(Server &server, std::string line)
{
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string token;

	while (std::getline(iss, token, ' ')) // Space parsing
		tokens.push_back(token);
	if (tokens.size() <= 1)
		return;
}

void Server::quit(Server &server, std::string str)
{
	(void)str;
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		exit(1);
}