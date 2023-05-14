#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::bot(std::string buffer, int fd)
{
	// /bot 1
	// /bot 2
	// /bot 3
	std::vector<std::string> my_vec;
	unsigned int i = 0;

	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() != 1){
		std::cerr << "\033[1;91mError.\033[0m" << std::endl;
		return;
	}
	// /bot 1
	if (my_vec[0] == "1")
	{
		std::string command = "open https://www.youtube.com/watch?v=ETxmCCsMoD0";
		system(command.c_str());
	}
	// /bot 2
	else if (my_vec[0] == "2")
	{
		std::string command = "open https://www.youtube.com/watch?v=lyWqQ4KzlzQ";
		system(command.c_str());
	}
	// /bot 3
	else if (my_vec[0] == "3")
	{
		std::string command = "open https://www.youtube.com/watch?v=h_D3VFfhvs4";
		system(command.c_str());
	}
	std::string msg = "Currently Playing: " + my_vec[0] + ". video\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
}
