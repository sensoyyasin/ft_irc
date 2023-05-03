#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(Server &server, std::string str)
{
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		exit(1);
	(void)str;
}
