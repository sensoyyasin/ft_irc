#include "../headers/Server.hpp"

void Server::nick(Server &server, std::string buffer)
{
	/* :yasin!localhost NICK :ali */
	std::string command = "";
	int i = 0;
	while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
		command += buffer[i++]; //first ->command
	std::string b = ":" + this->my_nick + "!localhost NICK " + command + "\r\n";
	send(this->new_socket, b.c_str(), b.size(), 0);
	this->my_nick.clear();
	this->my_nick = command;
	buffer.clear();
}