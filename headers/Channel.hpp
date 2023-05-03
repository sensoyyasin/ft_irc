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
		Channel();
		~Channel();
		//std::vector<Client *> channelClients;
		//Client *getAdmin();

		int getclientCount();
		std::string getchannelName();
};

#endif
