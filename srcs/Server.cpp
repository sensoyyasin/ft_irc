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
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
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
		perror("bind ");
		// std::cerr << "Error binding to port " << std::endl;
		close(server_fd);
		exit(1);
	}

	if (listen(server_fd, MAX_USR) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		close(server_fd);
		exit(1);
	}
	pollfds.push_back((pollfd){server_fd, POLLIN, 0});
}

void	Server::parser(std::string command, std::string args)
{
	std::cout << "*" << command << "*" << std::endl;
	std::cout << "*" << args << "*" << std::endl;
	if (command == "USER")
	{
		this->my_nick = args;
		//std::cout << this->my_nick << std::endl; ->ysensoy
	}
	if (cap_ls[0] == command)
		add(*this, args);
	else if (cap_ls[1] == command)
		nick(*this, args);
	else if (cap_ls[2] == command)
		join(*this, args);
	else if (cap_ls[3] == command)
		quit(*this, args);
	else if (cap_ls[4] == command)
		cap(*this, args);
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
		str += "\r\n";
		if (send(this->new_socket, str.c_str(), str.size(), 0) != str.size())
			std::cerr << "Error" << std::endl;
		++it;
	}
}

void	Server::executeCommand(int fd)
{
	while (buffer.find("\r\n"))
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
		while (buffer.size() > 0)
		{
			std::string command = "";
			std::string args = "";
			int i = 0;
			while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
				command += buffer[i++]; //first ->command
			while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
				i++;
			while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
				args += buffer[i++]; //second ->arg
			while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
				i++;
			parser(command, args);
			buffer.erase(0, i);
		}
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

	this->my_nick += "\r\n";
	if (send(this->new_socket, this->my_nick.c_str(), this->my_nick.size(), 0) != this->my_nick.size())
		std::cerr << "Error" << std::endl;
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
