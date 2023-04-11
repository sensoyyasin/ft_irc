#ifndef SERVER_HPP
# define SERVER_HPP

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
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_USR 100

class Server
{
	private:
		int my_port;
		std::string my_password;
	public:
		int					new_socket;
		int					server_fd;
		struct sockaddr_in	address;
		std::string			buffer;
		std::map<int, std::string> cap_ls;
		std::vector<pollfd>	pollfds;
		std::vector<Client> clients_;
		//std::vector<Channel> channels_;

		Server(){} //We have to use for inheritance
		Server(int, char **);
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations();
		void	socketOperations2(char **argv);
		void	parser();

		void	newClient();
		void	executeCommand(int fd);
		void	loop();

		/* Getter and setter */
		int	getmyport();
		std::string	getmypassword();

		void add(Server &server, std::string);
		void cap(Server &server, std::string);
		void nick(Server &server, std::string);
		void join(Server &server, std::string);
		void quit(Server &server, std::string);
};

#endif