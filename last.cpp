
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
		struct pollfd fds[MAX_CLIENTS];
		int	join_key;
		int client_socket[30];
		int server_fd;
		int new_socket;
		int addr_len;
		int opt;
		int rv;
		int timeout;
		struct sockaddr_in address;
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

Server::Server()
{
	this->opt = 1;
	this->rv = 0;
	this->timeout = (3 * 60 * 1000);
	this->join_key = 0;
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
	this->addr_len = sizeof(this->address);
	this->buffer[BUFFER_SIZE] = 0;
}

void	Server::socketOperations(Server &server)
{
	/* Create a master socket */
	if ((server.server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}

	/* Set master socket to allow multiple connections */
	if (setsockopt(server.server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server.opt, sizeof(server.opt)) != 0)
		std::cout << "Setsockopt set up and connecting to server..." << std::endl;
	else
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2(Server &server, char **argv)
{
	/* Creating socket and checking the address. */
	server.address.sin_family = AF_INET; //IPV4
	server.address.sin_addr.s_addr = INADDR_ANY;
	server.address.sin_port = htons(atoi(argv[1]));

	if (bind(server.server_fd, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		exit(1);
	}

	if (listen(server.server_fd, MAX_CLIENTS) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(1);
	}
}

void	Server::parser(Server &server, std::string message)
{
    std::string str = server.buffer;
	int	del_place = str.find(" ");
	std::string token = str.substr(0, del_place);
	std::string args = str.substr(del_place + 1); 
	if (token == "JOIN")
	{
		//server.join_key = std::stoi(str);
		std::cout << "Args: -" << args << std::endl;
	}
	if (token ==  "QUIT" || token == "EXIT")
	{
		std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		close(server.new_socket);
		exit(1);
	}
}

/* GETTER AND SETTER ON THE WAY -_- */
int	Server::getmyport()
{
	return(this->my_port);
}

std::string	Server::getmypassword()
{
	return (this->my_password);
}

int main(int argc, char **argv)
{
	Server server;
	server.appointment(argc, argv);

	std::cout << "Starting IRC server on port " << std::endl;

	server.socketOperations(server);
	server.socketOperations2(server, argv);

	std::cout << "Waiting for connections..." << std::endl;
	std::cout << "Port : " << ntohs(server.address.sin_port) << std::endl;

	server.fds[0].fd = server.server_fd;
	server.fds[0].events = POLLIN;

	std::string message;
	while (1)
	{
    	server.rv = poll(server.fds, 1, server.timeout);
    	if (server.rv < 0)
    	{
        	std::cerr << "Poll error" << std::endl;
        	return (1);
    	}
		else if (server.rv == 0)
		{
			std::cout << "poll() timed out. End program." << std::endl;
			return (1);
		}
    	if (server.fds[0].revents & POLLIN) 
    	{
        	memset(server.buffer, 0, sizeof(server.fds));
			message.clear();
        	if ((server.new_socket = accept(server.server_fd, (struct sockaddr*)&server.address, (socklen_t *)&server.addr_len)) < 0)
        	{
            	std::cerr << "Accept failed" << std::endl;
            	return (1);
        	}
        	while (!strstr(server.buffer, "\n\r"))
        	{
            	memset(server.buffer, 0, BUFFER_SIZE);
            	int bytes_received = recv(server.new_socket, server.buffer, BUFFER_SIZE, 0); 
            	if (bytes_received < 0)
            	{
                	std::cerr << "Receive failed" << std::endl;
                	close(server.new_socket);
                	break;
            	}
            	message.append(server.buffer);
				server.parser(server, message);
				std::cout << message << std::endl;
        	}
        	//closing the connected socket
        	close(server.new_socket);
    	}
	}
	//closing the listening socket
	shutdown(server.server_fd, SHUT_RDWR);
	return (0);
}


	// while (1)
	// {
	// 	memset(server.buffer, 0, BUFFER_SIZE);
	// 	if ((server.new_socket = accept(server.server_fd, (struct sockaddr*)&server.address, (socklen_t *)&server.addr_len)) < 0)
	// 	{
	// 		std::cerr << "Accept failed" << std::endl;
	// 		return (1);
	// 	}
	// 	rv = poll(server.fds, 1, -1);
	// 	if (rv == -1)
	// 	{
	// 		std::cerr << "Poll error" << std::endl;
	// 		return 1;
	// 	}
	// 	while (!strstr(server.buffer, "\n\r"))
	// 	{
	// 		memset(server.buffer, 0, BUFFER_SIZE);
	// 		int bytes_received = recv(server.new_socket, server.buffer, BUFFER_SIZE, 0); //very similar to read.
	// 		if (bytes_received < 0)
	// 		{
	// 			std::cerr << "Receive failed" << std::endl;
	// 			close(server.new_socket);
	// 			break;
	// 		}
	// 		message.append(server.buffer);
	// 		if (strstr(message.c_str(), "QUIT") || strstr(message.c_str(), "EXIT"))
	// 		{
	// 			std::cout << "\033[1;93mLeaving...\033[0m" << std::endl;
	// 			close(server.new_socket);
	// 			return(0);
	// 		}
	// 		std::cout << message << std::endl;
	// 	}
	// 	//closing the connected socket
	// 	close(server.new_socket);
	// }
	// //closing the listening socket
	// shutdown(server.server_fd, SHUT_RDWR);
	// return (0);
//}
