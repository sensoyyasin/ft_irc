#include "../headers/Server.hpp"

void Server::join(Server &server, std::string buffer)
{
	std::vector<std::string> my_vec;
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
	i = -1;
	while (my_vec.size() > ++i)
	{
		if (my_vec[i][0] != '#' && my_vec[i][0] != '&')
		{
			std::cerr << "Error couldn't connect the channel" << std::endl;
			continue;
		}
		my_vec[i] = my_vec[i].substr(1, my_vec[i].size() - 1);
		std::string b = ":" + this->my_nick + "!localhost JOIN " + my_vec[i] + "\r\n";
		send(this->new_socket, b.c_str(), b.size(), 0);
		b.clear();
	}
	buffer.clear();
}