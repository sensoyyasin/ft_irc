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
	Server server;
	server.appointment(argc, argv);

	std::cout << "Starting IRC server on port " << std::endl;

	server.socketOperations(server);
	server.socketOperations2(server, argv);

	std::string message;
	int i = 0;
	while (1)
	{
		memset(server.buffer, 0, BUFFER_SIZE);
		std::cout << "1" << "\n";
		if ((server.client_fd[i] = accept(server.server_fd, (struct sockaddr*)&server.address, (socklen_t *)&server.addr_len)) < 0)
		{
			std::cerr << "Accept failed" << std::endl;
			return (1);
		}
		while (1)
		{
			memset(server.buffer, 0, BUFFER_SIZE);
			int bytes_received = recv(server.client_fd[i], server.buffer, BUFFER_SIZE, 0); //very similar to read.
			if (bytes_received < 0)
			{
				std::cerr << "Receive failed" << std::endl;
				close(server.client_fd[i]);
				break;
			}
			message.append(server.buffer);
			if (strstr(message.c_str(), "QUIT"))
			{
				std::cout << "\033[1;93mLeaving...\033[0m" << std::endl;
				for(int i = 0; i < MAX_USR; i++)
					if(is_client_active(server.client_fd[i]))
						close(server.client_fd[i]);
				return(0);
			}
			std::cout << message << std::endl;
		}
		//closing the connected socket
		for(int i = 0; i < MAX_USR; i++)
			if(is_client_active(server.client_fd[i]))
				close(server.client_fd[i]);
		i++;
	}		

	//closing the listening socket
	shutdown(server.server_fd, SHUT_RDWR);
	return (0);
}
