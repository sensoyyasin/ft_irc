#ifndef SERVER_HPP
# define SERVER_HPP

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h> /* struct hostent *server */
#include <sys/poll.h>
#include <map>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_USR 100

/* A sockaddr_in is a structure containing an internet address. This structure is defined in <netinet/in.h>. Here is the definition:
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
}; */

/* --System args--
   argv[0] = filename
   argv[1] = localhost
   argv[2] = port */


class Server
{
	public:
		typedef void (Server::*func_ptr)(std::string);
	private:
		int my_port;
		std::string my_password;
		Server();
	public:
		int					new_socket;
		int					server_fd;
		struct sockaddr_in	address;
		std::string			buffer;
		std::vector<pollfd>	pollfds;
		std::map<std::string, func_ptr> capls_map;

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

		void add(std::string);
		void cap(std::string);
		void nick(std::string);
		void join(std::string);
		void quit(std::string);
};

#endif
