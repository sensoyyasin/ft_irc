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
	i = 0;
	while(i < channels_.size())
	{
		if (channels_[i].getchannelName() == my_vec[1])
			this->channel_ok = 1;
		i++;
	}

	if (this->channel_ok == 0)
	{
		std::cerr << "\033[1;91mError: Böyle bir kanal yok veya oluşmamiş..\033[0m" << std::endl;
		return;
	}

	my_vec[2] = my_vec[2].substr(1, my_vec[2].size() - 1); //-> parsing #berk to berk.
	// Get index of the client to remove (we found index for inside the channels.)
	//düzeltilecek
	unsigned int index = 0;
	for (; index < this->clients_.size(); ++index)
		if (this->clients_[index].getFd() == fd)
			break;

	//kanal varsa admin diye mi bak.
	if (this->channel_ok == 1)
	{
		if (this->clients_[index].getFd() == fd) //->admin
		{
			//searching berk to clients.
			unsigned int j = 0;
			while (j < this->clients_.size())
			{
				if (this->clients_[j].getNickName() == my_vec[2])
				{
					//bulundu berk
					std::cout << "Berk bulundu" << std::endl;
					// this->channels_[j]._clientsFd.erase(this->channels_[j]._clientsFd.begin() + 1);  // Kanaldan kullanıcıyı sil
					// this->channels_[j].setClientCount(this->channels_[j].getchannelUserCount() - 1);
				}
				j++;
			}
		}
	}
	std::string msg = ":" + this->clients_[index].getPrefixName() + " KICK ";
	send(fd, msg.c_str(), msg.size(), 0);
	this->clients_.erase(this->clients_.begin() + index);
	buffer.clear();
	close (fd);
}