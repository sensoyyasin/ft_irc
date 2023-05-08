#include "../headers/Channel.hpp"

<<<<<<< HEAD
Channel::Channel() {}

Channel::~Channel() {}
=======
Channel::Channel(std::string channelName)
{
	this->channelName = channelName;
}

Channel::~Channel() {}

std::string Channel::getchannelName()
{
	return (this->channelName);
}
>>>>>>> 28184583832779898723191b451770961cc0f9db
