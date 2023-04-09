#include "Server.hpp"

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
	int rv;
	int timeout = (3 * 60 * 1000);

	std::string message;
	while (1)
	{
    	rv = poll(server.fds, 1, timeout);
    	if (rv < 0)
    	{
        	std::cerr << "Poll error" << std::endl;
        	return (1);
    	}
		else if (rv == 0)
		{
			std::cout << "poll() timed out. End program." << std::endl;
			return (1);
		}
    	if (server.fds[0].revents & POLLIN) 
    	{
        	memset(server.buffer, 0, sizeof(server.fds));
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
            	if (strstr(message.c_str(), "QUIT") || strstr(message.c_str(), "EXIT"))
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
