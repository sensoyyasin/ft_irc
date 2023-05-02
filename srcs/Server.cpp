/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasinsensoy <yasinsensoy@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:32 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/05/02 08:12:55 by yasinsensoy      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	std::map<int, std::string>::iterator it;
	it = cap_ls.begin();
	while (it != cap_ls.end())
	{
		std::string str = "/";
		str += it->second += "\r\n";
		send(this->new_socket, str.c_str(), str.size(), 0);
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

void	Server::parser(std::string command, std::string args)
{
	std::cout << "*" << command << "*" << std::endl;
	std::cout << "*" << args << "*" << std::endl;
	if (command == "NICK")
		this->my_nick = args;
	else if (!strncmp(cap_ls[0].c_str(), command.c_str(), 3))
		add(*this, args);
	else if (!strncmp(cap_ls[1].c_str(), command.c_str(), 4))
		nick(*this, args);
	else if (!strncmp(cap_ls[2].c_str(), command.c_str(), 4))
		join(*this, args);
	else if (!strncmp(cap_ls[3].c_str(), command.c_str(), 4))
		quit(*this, args);
	else if (!strncmp(cap_ls[4].c_str(), command.c_str(), 3))
		cap(*this, args);
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
	//1 tane kullanicidan azsa patlat.
	if (tokens.size() <= 1)
		return;
	Client new_client;
	//Bircok kullanıcıysa [add] [a b c] ekle hepsini 2 argtan daha fazla olabilir.
	for (int i = 0; i < tokens.size(); i++)
	{
		new_client.client_name = tokens[i];
		clients_.push_back(new_client);
	}
}

void Server::nick(Server &server, std::string str)
{
	/* :yasin!localhost NICK :ali */
	std::string b = ":" + this->my_nick + "!localhost NICK " + str + "\r\n";
	send(this->new_socket, b.c_str(), b.size(), 0);
	this->my_nick.clear();
	this->my_nick = str;
	str.clear();
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
	//bircok kanala katıtlma. Join 1 2 3
	// for (int i = 0; i < tokens.size(); i++)
	// {
	// 	std::string a = ":" + this->my_nick + "!localhost JOIN " + line + "\r\n";
	// 	send(this->new_socket, a.c_str(), a.size(), 0);
	// 	this->my_nick.clear();
	// 	this->my_nick = line;
	// 	line.clear();
	// }
}

void Server::quit(Server &server, std::string str)
{
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		exit(1);
	(void)str;
}
