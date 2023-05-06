#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(Server &server, std::string str)
{
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
	close(this->new_socket);
	std::cout << "Şu anki kullanici sayisi  :" << this->clients_.size() << std::endl;
	//this->clients_.erase()
	//std::cout << "Eksildikten sonra " << this->clients_.size() << std::endl;
	//exit(1);
	(void)str;
}
