#include "server.hpp"

int main(int argc, char **argv)
{
	Server server;
	server.appointment(argc, argv);

	std::cout << "Starting IRC server on port " << std::endl;

	server.socketOperations(server);
	server.socketOperations2(server, argv);

	std::string message;
	while (1)
	{
		memset(server.buffer, 0, BUFFER_SIZE);
		if ((server.new_socket = accept(server.server_fd, (struct sockaddr*)&server.address, (socklen_t *)&server.addr_len)) < 0)
		{
			std::cerr << "Accept failed" << std::endl;
			return (1);
		}
		// int client_port = ntohs(server.address.sin_port);
		// if (client_port != )
		while (!strstr(server.buffer, "\n\r"))
		{
			memset(server.buffer, 0, BUFFER_SIZE);
			int bytes_received = recv(server.new_socket, server.buffer, BUFFER_SIZE, 0); //very similar to read.
			if (bytes_received < 0)
			{
				std::cerr << "Receive failed" << std::endl;
				close(server.new_socket);
				break;
			}
			message.append(server.buffer);
			if (strstr(message.c_str(), "QUIT"))
			{
				std::cout << "\033[1;93mLeaving...\033[0m" << std::endl;
				close(server.new_socket);
				return(0);
			}
			std::cout << message << std::endl;
		}
		//closing the connected socket
		close(server.new_socket);
	}

	//closing the listening socket
	shutdown(server.server_fd, SHUT_RDWR);
	return (0);
}
