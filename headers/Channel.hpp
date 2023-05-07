#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../headers/Server.hpp"
#include "../headers/Client.hpp"

class Channel
{
	private:
		int clientCount;
		std::string channelName;
		std::string	k;
		int l;
		bool n;
		//Client *channelAdmin;
	public:
		Channel(std::string channelName);
		~Channel();
		//std::vector<Client *> channelClients;
		//Client *getAdmin();

		//int getchannelCount();
		std::string getchannelName();
};

#endif
