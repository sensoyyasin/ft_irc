#include "server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char **argv)
{
	Server server = Server(argc, argv);

	server.loop();
	shutdown(server.server_fd, SHUT_RDWR);
	return (0);
}
