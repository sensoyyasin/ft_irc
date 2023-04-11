#include "server.hpp"

void cap(std::string str)
{
	(void)str;
}

void add(std::string str)
{
    (void)str;
}

void nick(std::string str)
{
    (void)str;
}

void join(std::string str)
{
    (void)str;
}

void quit(std::string str)
{
    (void)str;
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		exit(1);
}