#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::nick_change(std::string command_n, std::string buffer)
{
	(void)command_n;
	std::string command = "";
	int i = 0;
	while (i < buffer.size() && (buffer[i] > 32))
		command += buffer[i++]; //first ->command
	std::string b = ":" + this->my_nick + "!localhost NICK " + command + "\r\n";
	send(this->new_socket, b.c_str(), b.size(), 0);
	this->my_nick.clear();
	this->my_nick = command;
	buffer.clear();
}


void Server::nick_first(std::string command_n, std::string buffer)
{
	std::cout<<"nick_first_command:*"<<command_n<<"*"<<std::endl;
	std::vector<std::string> my_vec;
	my_vec.push_back(command_n);
	int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		std::string args = "";
		while (i < buffer.size() && (buffer[i] > 32))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] < 33))
			i++;
		my_vec.push_back(command);
	}
	std::cout << "----------------_nick_first_vec_size--------------:*" << my_vec.size() << "*" << std::endl;
	if (my_vec.size() < 3)
		this->is_nick_first = 1;
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "NICK")
			this->temp_nick = my_vec[i + 1];
		else if (my_vec[i] == "USER")
		{
			Client c(this->new_socket,my_vec[i+1],my_vec[i+2],my_vec[i+3],my_vec[i+4],this->temp_nick);
			this->clients_.push_back(c);
		}
		std::cout << "vector:" << my_vec[i] << std::endl; 
		i++;
	}
	my_vec.clear();
	this->is_nick_first = 0;
}