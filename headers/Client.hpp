#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../headers/Server.hpp"
#include "../headers/Channel.hpp"

class Client
{
	private:
		int fd;
		int port;
		int status;

		std::string username;
		std::string nickname;
<<<<<<< HEAD
		std::string reelname;
		std::string hostname;
		std::string password;
	public:
		Client(int fd, int port);
=======
		std::string realname;
		std::string hostname;
		std::string servername;
	public:
		Client(int fd, std::string username,std::string hostname, std::string servername, std::string realname, std::string nickname);
>>>>>>> 28184583832779898723191b451770961cc0f9db
		~Client();

		//std::vector<Channel *> channels;

		// Getter
		int getFd() const { return (this->fd); }
		int getPort() const { return (this->port); }
		int	getStatus() const { return (this->status); }
		std::string getUserName() const { return (this->username); }
		std::string getNickName() const { return (this->nickname); }
<<<<<<< HEAD
		std::string getReelName() const { return (this->reelname); }
		std::string getHostName() const { return (this->hostname); }
		std::string getPassword() const { return (this->password); }

		// Setter
		void setStatus(int status);
		void setUserName(std::string const &Username) { this->username = Username; }
		void setNickName(std::string const &Nickname) { this->nickname = Nickname; }
		void setRealName(std::string const &Reelname) { this->reelname = Reelname; }
		void setHostName(std::string const &Hostname) { this->hostname = Hostname; }
		void setPassword(std::string const &Password) { this->password = Password; }
=======
		std::string getReelName() const { return (this->realname); }
		std::string getHostName() const { return (this->hostname); }
		std::string getServername() const { return (this->servername); }

		// Setter
		void setStatus(int status) {this->status = status; };
		void setUserName(std::string const &Username) { this->username = Username; }
		void setNickName(std::string const &Nickname) { this->nickname = Nickname; }
		void setRealName(std::string const &Realname) { this->realname = Realname; }
		void setHostName(std::string const &Hostname) { this->hostname = Hostname; }
		void setServername(std::string const &Servername) { this->servername = Servername; }
>>>>>>> 28184583832779898723191b451770961cc0f9db

		void leave();
};

#endif
