#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(Server &server, std::string str, int fd)
{
	if(this->client_ret(fd))
	{
		int i = 0;
		std::cout <<"\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m";
		std::string command = "";
		while (i < str.size() && (str[i] != '\r' && str[i] != '\n'))
			command += str[i++];
		std::cout << command << std::endl;
		//delete the node
		std::vector<Client>::iterator it = this->clients_.begin();
		std::vector<Client>::iterator ite = this->clients_.end();
		for (; it != ite; it++)
		{
			if(it->getFd() == fd)
				this->clients_.erase(it);
		}
		//close
		close(fd);
		std::cout << "Şu anki kullanici sayisi  :" << this->clients_.size() << std::endl;
	}
	//this->clients_.erase()
	//std::cout << "Eksildikten sonra " << this->clients_.size() << std::endl;
	//exit(1);
	(void)str;
}
