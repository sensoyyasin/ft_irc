#include "server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int	is_client_active(int client_fd)
{
	if (fcntl(client_fd, F_GETFD) == -1)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	Server server = Server(argc, argv);

	server.loop();		
/* 
	for(int i = 0; i < MAX_USR; i++)
		if(is_client_active(server.client_fd[i]))
			close(server.client_fd[i]); */
	//closing the listening socket
	shutdown(server.server_fd, SHUT_RDWR);
	return (0);
}
