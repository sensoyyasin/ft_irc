#ifndef SERVER_HPP
# define SERVER_HPP

#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h> /* struct hostent *server */
#include <sys/poll.h>
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
	private:
		int my_port;
		std::string my_password;
	public:
		int					opt;
		int					addr_len;
		int					server_fd;
		int					client_fd[MAX_USR];
		char				buffer[BUFFER_SIZE];
		struct sockaddr_in	address;
		struct pollfd		polls[3];

		Server();
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations(Server &server);
		void	socketOperations2(Server &server, char **argv);

		/* Getter and setter */
		int	getmyport();
		std::string	getmypassword();
};

#endif