#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::who(Server &server, std::string str, int fd)
{
	std::vector<std::string> my_vec;
	std::string command = "";
	int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() < 2)
	{
		std::cerr << "\033[1;94mError: Not enough arg: [WHO]\033[0m" << std::endl;
		return;
	}
	// std::vector<Channel>::iterator it = channels_.begin(); // Loop through all channels
	// if (it != channels_.end()) // finding...
	// {
	// 	std::string b = ":";
	// 	b += " " + clients_[0].getUserName();
	// 	b += " " + clients_[0].getNickName();
	// 	b += " H";
	// 	b += ":0 " + clients_[0].getReelName();
	// 	send(fd, b.c_str(), b.size(), 0);
	// }
}
