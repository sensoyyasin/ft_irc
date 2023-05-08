#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

// void Server::bot(Server &server, std::string buffer, int fd)
// {
// 	std::string command = "";
// 	int i = 0;
// 	while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
// 		command += buffer[i++];
// 	std::string b = "Arog Merhaba Efendim : " + command + "\r\n";
// 	std::cout << command << std::endl;
// 	send(fd, b.c_str(), b.size(), 0);
// 	buffer.clear();
// }
