#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::join(Server &server, std::string buffer, int fd)
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
	
	i = -1;
	while (my_vec.size() > ++i)
	{
		if (my_vec[i][0] != '#' && my_vec[i][0] != '&')
		{
			std::cerr << "\033[1;91mError couldn't connect the channel..\033[0m" << std::endl;
			continue;
		}
		/* Channel olusturma channel size kadar while icinde.*/
		
		int kanalVarMi = 0;
		int	idx = -1;
		while(++idx < channels_.size())
			if (channels_[idx].getchannelName() == my_vec[i])
				kanalVarMi = 1;
		
		if (kanalVarMi == 0)
		{
			Channel c(my_vec[i]);
			
			c.setchannelAdminFd(this->client_ret(fd)->getFd());
			c._clientsFd.push_back(fd);
			this->channels_.push_back(c);

			std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[i] + "\r\n";
			send(fd, b.c_str(), b.size(), 0);
		}
		else
		{
			idx = -1;
			while(++idx < channels_.size())
				if (channels_[idx].getchannelName() == my_vec[i])
					channels_[idx]._clientsFd.push_back(fd);

			std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[i] + "\r\n";
			send(fd, b.c_str(), b.size(), 0);
		}

		// std::cout << "Channel_Size : " << this->channels_.size() << std::endl;
		int j = -1;
		int	fdTemp;

		while (channels_.size() > 0 && channels_[++j].getchannelName() == my_vec[0])
		{
			int k = -1;
			while (++k < channels_[j]._clientsFd.size())
			{
				if (channels_[j]._clientsFd[k] != fd)
				{
					fdTemp = channels_[j]._clientsFd[k];
					std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[i] + "\r\n";
					send(fdTemp, b.c_str(), b.size(), 0);
					b.clear();
				}
			}
		}
	}
	std::cerr << "\033[1;96mNumber of channel:\033[0m" << this->channels_.size() << std::endl;
	buffer.clear();
}
