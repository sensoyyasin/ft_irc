#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::who(Server &server, std::string str, int fd)
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
	i = 0;
	while(server.user_count > i)
	{
		/* aynı kanaldaysa veya farklı kanaldaysa da tüm kullanıcıları listeliyor düzeltilecek. 
		 Sadece aynı kanaldaki kullanıcıları göstermeli. */
		std::cout << "You are : " << this->clients_[i].getNickName() << std::endl;
		i++;
	}
	// std::vector<Channel>::iterator it = channels_.begin(); // Loop through all channels
	// if (it != channels_.end()) // finding...
	// {
	// 	std::string b = ":";
	// 	b += " " + clients_[0].getUserName();
	// 	b += " " + clients_[0].getNickName();
	// 	b += " H";
	// 	b += ":0 " + clients_[0].getReelName();
	// 	send(fd, b.c_str(), b.size(), 0);
	// }
}
