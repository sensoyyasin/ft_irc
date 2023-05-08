<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasinsensoy <yasinsensoy@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:42 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/05/03 09:10:18 by yasinsensoy      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
>>>>>>> 28184583832779898723191b451770961cc0f9db
#ifndef SERVER_HPP
# define SERVER_HPP

#include <sstream>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h> /* struct hostent *server */
#include <sys/poll.h>
#include <map>
#include <netinet/tcp.h>
#include "Client.hpp"
#include "Channel.hpp"

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_USR 100

class Channel;
class Client;

class Server
{
	private:
		int my_port;
		int is_nick_first;
		std::string my_password;
	public:
		int					new_socket;
		int					server_fd;
		struct sockaddr_in	address;
		std::string			buffer;
<<<<<<< HEAD
		std::string			my_nick;
		int					user_count;
		std::map<int, std::string> cap_ls;
		std::vector<pollfd>	pollfds;
		//std::vector<Client> clients_;
		//std::vector<Channel> channels_;
=======
		std::string			temp_nick;
		int					user_count;
		std::map<int, std::string> cap_ls;
		std::vector<pollfd>	pollfds;
		std::vector<Client> clients_;
		std::vector<Channel> channels_;
>>>>>>> 28184583832779898723191b451770961cc0f9db

		Server(int, char **);
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations();
		void	socketOperations2(char **argv);
<<<<<<< HEAD
		void	executable(std::string, std::string);
=======
		void	executable(std::string, std::string, int);
>>>>>>> 28184583832779898723191b451770961cc0f9db

		void	newClient();
		void	executeCommand(int fd);
		void	loop();

		/* Getter and setter */
		int	getmyport();
		std::string	getmypassword();

<<<<<<< HEAD
		void add(Server &server, std::string);
		void cap(Server &server, std::string);
		void nick(Server &server, std::string);
		void join(Server &server, std::string);
		void quit(Server &server, std::string);
		void bot(Server &server, std::string);
=======
		void cap(std::string, int);
		void join(std::string, int);
		void quit(std::string, int);
		void ping(std::string, int);
		void pong(std::string, int);
		void privmsg(std::string, int);
		
		void nick_change(std::string, std::string, int);
		void nick_first(std::string, std::string, int);
		
		int client_nick_check(std::string nickname);
		Client *client_ret(std::string nickname);
		Client *client_ret(int fd);

		int getNick_first() {return this->is_nick_first; };
		void setNick_first(int is) {this->is_nick_first = is; };
>>>>>>> 28184583832779898723191b451770961cc0f9db
};

#endif

// void bot(Server &server, std::string, int);