#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::mode(std::string buffer, int fd)
{
	std::cout<<"\033[1;93mMode func received buff: *"<<buffer<<"*\033[0m\n";
	(void)fd;
	std::vector<std::string> my_vec;
	std::string command = "";
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
	i = 0;
	bool channel_exists_admin = false;
	while (i < my_vec.size())
	{
		unsigned int j = 0;
		while (j < this->channels_.size())
		{
			if (this->channels_[j].getchannelName() == my_vec[i] && this->channels_[j].getchannelAdminFd() == fd)//&& ekle fd
			{
				channel_exists_admin = true;
				break;
			}
			j++;
		}
		if (channel_exists_admin)
			break;
		i++;
	}
	if (!channel_exists_admin)
	{
		std::cout<<"\033[1;91mNo such channel adn/or not channel admin!\033[0m\n";
		return;
	}

}