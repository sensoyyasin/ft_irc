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
	cap_ls[5] =  "KICK";
	cap_ls[6] =  "BOT";
	this->channel_count = 0;
	this->user_count = 0;
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
	if (setsockopt(server_fd, IPPROTO_TCP, TCP_NODELAY , &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
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

void	Server::newClient()
{
	buffer.clear();
	int	addr_len = sizeof(address);
	this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		close(server_fd);
		exit(1);
	}
	
	pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
	Client *client = new Client(this->new_socket, ntohs(address.sin_port));
	this->user_count++;
	std::cout << "User connected: " << this->user_count  << "." << std::endl;

	std::map<int, std::string>::iterator it;
	it = cap_ls.begin();
	std::string str;
	while (it != cap_ls.end())
	{
		str.append('/' + it->second+"\n");
		++it;
	}
	send(this->new_socket, str.c_str(), str.size(), 0);
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
			std::cerr << "Receive ended" << std::endl;
			break;
		}
		buffer = std::string(buff);
		int i = 0;
		while (i < buffer.size())
		{
			std::string command = "";
			std::string args = "";
			while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
				command += buffer[i++]; //first ->command
			while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
				i++;
			while (i < buffer.size())
				args += buffer[i++];
			executable(command, args);
			buffer.erase(0, i);
		}
	}
}

void	Server::executable(std::string command, std::string args)
{
	if (!strncmp(cap_ls[0].c_str(), command.c_str(), 3))
		add(*this, args);
	if (!strncmp(cap_ls[1].c_str(), command.c_str(), 4))
		nick(*this, args);
	if (!strncmp(cap_ls[2].c_str(), command.c_str(), 4))
		join(*this, args);
	if (!strncmp(cap_ls[3].c_str(), command.c_str(), 4))
		quit(*this, args);
	if (!strncmp(cap_ls[4].c_str(), command.c_str(), 3))
		cap(*this, args);
	if (!strncmp(cap_ls[5].c_str(), command.c_str(), 3))
		bot(*this, args);
}


void Server::cap(Server &server, std::string line)
{
	std::vector<std::string> my_vec;
	int i = 0;
	while (line.size() > i)
	{
		std::string command = "";
		std::string args = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "USER" || my_vec[i] == "NICK")
			executable(my_vec[i], my_vec[i + 1]);
		std::cout << my_vec[i] << std::endl;
		i++;
	}
}
