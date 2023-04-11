#ifndef SERVER_HPP
# define SERVER_HPP

#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <netdb.h> /* struct hostent *server */
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h> 
#include <map>
#include <vector>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 30
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
		//struct pollfd fds[MAX_CLIENTS];
		int	join_key;
		int server_fd;
		int new_socket;
		int addr_len;
		int opt;
		int rv;
		int timeout;
		struct sockaddr_in address;
		std::vector<pollfd> pollfds;
		char *buffer;
		//std::map<std::string, int> mymap;
		//std::map<std::string, int>::iterator my_iterator;

		Server();
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations(Server &server);
		void	socketOperations2(Server &server, char **argv);
		void	parser(Server &server, std::string message);

		/* Getter and setter */
		int	getmyport();
		std::string	getmypassword();
};

#endif