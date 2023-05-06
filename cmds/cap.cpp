#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::cap(Server &server, std::string line)
{
	std::vector<std::string> my_vec;
	int i = 0;
	while (line.size() > i)
	{
		std::string command = "";
		std::string args = "";
		while (i < buffer.size() && (buffer[i] > 32))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] < 33))
			i++;
		my_vec.push_back(command);
	}
	std::cout << "----------------vec_size--------------:*" << my_vec.size() << "*" << std::endl;
	if (my_vec.size() < 3)
		this->is_nick_first = 1;
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "NICK")
			this->nick_first(my_vec[i], my_vec[i + 1]);
		else if (my_vec[i] == "USER")
		{
			Client c(this->new_socket,my_vec[i+1],my_vec[i+2],my_vec[i+3],my_vec[i+4],this->temp_nick);
			this->clients_.push_back(c);
		}
		std::cout << "vector:" << my_vec[i] << std::endl;
		i++;
	}
	my_vec.clear();
}