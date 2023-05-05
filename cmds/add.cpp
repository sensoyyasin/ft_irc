#include "../headers/Server.hpp"

void Server::add(Server &server, std::string buffer)
{
	// std::vector<std::string> my_vec;
	// std::string command = "";
	// int i = 0;
	// while (buffer.size() > i)
	// {
	// 	std::string command = "";
	// 	while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
	// 		command += buffer[i++]; //first ->command
	// 	while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
	// 		i++;
	// 	my_vec.push_back(command);
	// }

	// Client new_client(this->user_count, this->my_port);
	// new_client.setNickName(my_vec[1]);
	// new_client.setRealName(my_vec[2]);

	// this->clients_.push_back(new_client);
	// this->user_count++;

	// std::string b = ":" + this->my_nick + "!localhost ADD " + my_vec[1] + "\r\n";
	// for (std::vector<Client>::iterator it = this->clients_.begin(); it != this->clients_.end(); ++it)
	// {
	// 	send(this->new_socket, b.c_str(), b.length(), 0);
	// }
}
