#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../headers/Server.hpp"
#include "../headers/Client.hpp"

class Client;

class Server;

class Channel
{
	private:
		int clientCount;
		std::string channelName;
		std::string channelAdmin;
		//std::string	k;
		//int l;
		//bool n;
	public:
		Channel(std::string channelName);
		~Channel();

		std::string getchannelAdmin();
		std::string getchannelName();

		void addUser(Server &server,Client c);

		// std::vector<Client> getUsers();

		// bool findUser(std::string nickName);
};

#endif
