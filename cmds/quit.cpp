#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(std::string str, int fd)
{
	if (this->flag == 0)
	{
		std::cout <<"\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m ";
		exit(1);
	}
	if (this->client_ret(fd))
	{
		std::cout <<"\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m ";

		//Get the message from the command string
		unsigned int i = 0;
		std::string command = "";
		while (i < str.size() && (str[i] != '\r' && str[i] != '\n'))
			command += str[i++];

		std::cout << command << std::endl;

		//Find the index of the client to remove
		unsigned int index = 0;
		for (; index < this->clients_.size(); ++index)
		{
			if (this->clients_[index].getFd() == fd)
				break;
		}
		// Set the admin to the previous client if the current admin quits
		if (this->clients_[index].getFd() == this->channels_[index].getchannelAdminFd())
		{
			if (index == 0 && this->clients_.size() > 1)
				this->channels_[index].setchannelAdminFd(this->clients_[1].getFd());
			else if (index == 1 && this->clients_.size() > 2)
				this->channels_[index].setchannelAdminFd(this->clients_[2].getFd());
			else if (index > 1)
				this->channels_[index].setchannelAdminFd(this->clients_[index - 1].getFd());
			else
			{
				// No other clients left in the channel
				this->channels_[index].setchannelAdminFd(42);
			}
		}
		//we have to check
		std::cout << "\033[1;92mLastAdmin_fd : \033[0m" << this->channels_[index].getchannelAdminFd() << std::endl;

		// Remove the client from the vector and close the connection
		this->clients_.erase(this->clients_.begin() + index);
		close(fd);

		std::cout << "Current number of clients: " << this->clients_.size() << std::endl;

		if (this->clients_.empty())
		{
			std::cout << "No clients left, closing the channel." << std::endl;
			this->channels_[index].setchannelAdminFd(-1);
		}
	}
	(void)str;
}
