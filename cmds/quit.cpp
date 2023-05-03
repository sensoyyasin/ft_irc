#include "../headers/Server.hpp"

void Server::quit(Server &server, std::string str)
{
	(void)str;
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
	close(this->new_socket);
	// std::string b = ":" + this->my_nick + "!localhost QUIT " + "\r\n";
	// send(this->new_socket, b.c_str(), b.size(), 0);
}