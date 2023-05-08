#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::privmsg(Server& server, std::string buffer, int fd)
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
	i = 0;

	std::cout << my_vec[0] << std::endl;
	std::cout << my_vec[1] << std::endl;
	std::cout << my_vec[2] << std::endl;

	size_t found = my_vec[1].find("PING");
	if (found == std::string::npos)
		std::cerr << "There is no Ping command" << std::endl;
	else
	{
		std::string b = ":" + this->temp_nick + "!localhost PONG " + my_vec[2] + "\r\n";
		send(fd, b.c_str(), b.size(), 0);
	}
}
