#include "../headers/Server.hpp"

void Server::add(Server &server, std::string line)
{
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string token;

	while (std::getline(iss, token, ' ')) //Space parsing
		tokens.push_back(token);
	//1 tane kullanicidan azsa patlat.
	if (tokens.size() <= 1)
		return;
	Client new_client;
	//Bircok kullanıcıysa [add] [a b c] ekle hepsini 2 argtan daha fazla olabilir.
	for (int i = 0; i < tokens.size(); i++)
	{
		new_client.client_name = tokens[i];
		clients_.push_back(new_client);
	}
}