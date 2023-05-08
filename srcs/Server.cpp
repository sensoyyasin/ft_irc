<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:32 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/05/08 13:01:51 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

>>>>>>> 28184583832779898723191b451770961cc0f9db
#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

Server::Server(int argc, char **argv)
{
	appointment(argc, argv);
	std::cout << "Starting IRC server on port " << std::endl;

	socketOperations();
	socketOperations2(argv);

<<<<<<< HEAD
	cap_ls[0] =  "ADD";
	cap_ls[1] =  "NICK";
	cap_ls[2] =  "JOIN";
	cap_ls[3] =  "QUIT";
	cap_ls[4] =  "CAP";
	cap_ls[5] =  "KICK";
	cap_ls[6] =  "BOT";
=======
	cap_ls[0] = "NICK";
	cap_ls[1] = "JOIN";
	cap_ls[2] = "QUIT";
	cap_ls[3] = "CAP";
	cap_ls[4] = "KICK";
	cap_ls[5] = "PRIVMSG";

	this->is_nick_first = 0;
>>>>>>> 28184583832779898723191b451770961cc0f9db
}

Server::~Server()
{
	std::vector<Client>::iterator it = clients_.begin();
	while (it != clients_.end())
	{
		delete(&(*it));
		++it;
	}
	clients_.clear();
}

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
		poll(pollfds.begin().base(), pollfds.size(), 1000);
		for (size_t i = 0 ; i <  pollfds.size() ; i++)
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

void	Server::newClient()
{
	buffer.clear();
	int	addr_len = sizeof(address);
	this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	std::cout << "New socket: " << this->new_socket << std::endl;
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
<<<<<<< HEAD
		close(server_fd);
		exit(1);
	}
	pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
	Client *client = new Client(this->new_socket, ntohs(address.sin_port));
	this->user_count++;
	std::cout << "User connected: " << this->user_count  << "." << std::endl;

	std::map<int, std::string>::iterator it;
	it = cap_ls.begin();
	while (it != cap_ls.end())
	{
		std::string str = "/";
		str += it->second += "\r\n";
		send(this->new_socket, str.c_str(), str.size(), 0);
		++it;
=======
		close(this->new_socket);
		// close(server_fd);
		// exit(1);
>>>>>>> 28184583832779898723191b451770961cc0f9db
	}
	else
	{
		this->pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});

		// Client c(this->new_socket, this->my_port);
		// this->clients_.push_back(c);
		// std::cout << "User connected: " << this->clients_.size() << "." << std::endl;
		// std::cout << "Fds size: " << this->pollfds.size() << "." << std::endl;
	
		std::map<int, std::string>::iterator it;
		it = cap_ls.begin();
		std::string str;
		while (it != cap_ls.end())
		{
			str.append('/' + it->second+"\n");
			++it;
		}
<<<<<<< HEAD
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
=======
		send(this->new_socket, str.c_str(), str.size(), 0);
	}
}
>>>>>>> 28184583832779898723191b451770961cc0f9db
