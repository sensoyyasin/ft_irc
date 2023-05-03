#include "../headers/Server.hpp"

void Server::add(Server &server, std::string line)
{
	this->user_count++;
	// std::vector<std::string> tokens;
	// std::istringstream iss(line);
	// std::string token;

	// while (std::getline(iss, token, ' ')) // boşlukları parselleme
	// 	tokens.push_back(token);

	// // Eğer sadece bir tane kullanıcı varsa, işlem yapma
	// if (tokens.size() <= 1)
	// 	return;

	// // Birden fazla kullanıcı varsa vektöre ekle
	// for (int i = 1; i < tokens.size(); i++)
	// {
	// 	Client new_client;
	// 	new_client.client_name = tokens[i];
	// 	clients_.push_back(new_client);
	// }
	std::cout << "User sayisi:" << this->user_count << std::endl;
}
