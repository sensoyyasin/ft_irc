#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::kick(std::string buffer, int fd)
{
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
	// gelen arg kanllarda var mı kontrolü.
	this->channel_ok = 0;

	// Get index of the client to remove (we found index for inside the channels.)
	//düzeltilecek
	unsigned int index = 0;
	while (this->channels_.size() > index)
	{
		if (this->channels_[index].getchannelAdminFd() == fd && this->channels_[index].getchannelName() == my_vec[1])
		{
			this->channel_ok = 1;
			break;
		}
		index++;
	}

	if (this->channel_ok == 0)
	{
		std::cerr << "\033[1;91mError: Böyle bir kanal yok veya oluşmamiş..\033[0m" << std::endl;
		return;
	}

	my_vec[2] = my_vec[2].substr(1, my_vec[2].size() - 1); //-> parsing #berk to berk.
	int kick_fd = 42;
	for (unsigned int s = 0; s < this->clients_.size(); s++)
	{
		if (this->clients_[s].getNickName() == my_vec[2])
		{
			kick_fd = this->clients_[s].getFd();
			break;
		}
	}

	//kanal varsa admin diye mi bak.
	if (this->channel_ok == 1)
	{
			//searching berk to clients.
			std::cout << "***" << std::endl;
			unsigned int m = 0;
			while (this->channels_[index]._clientsFd.size() > m)
			{
				if (this->channels_[index]._clientsFd[m] == kick_fd)
				{
					if (m == 0)
					{
						std::cerr << "Admin kendini atamaz" << std::endl;
						return;
					}
					this->channels_[index]._clientsFd.erase(this->channels_[index]._clientsFd.begin() + m);
					this->channels_[index].setClientCount(this->channels_[index].getchannelUserCount() - 1);
				}
				m++;
			}
	}
	std::string msg = ":" + this->client_ret(fd)->getNickName() + " KICK " + my_vec[1] + " " + my_vec[2] + " :Speaking English \r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	buffer.clear();
}