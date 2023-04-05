#include "server.hpp"

/* A sockaddr_in is a structure containing an internet address. This structure is defined in <netinet/in.h>. Here is the definition:
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
}; */

int main(int argc, char **argv)
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};
	char hello[100] = "Hello from server";

	/* Creating socket file descriptor */
	/* AF_INET : The first is the address domain of the socket.
	SOCK_STREAM : The second argument is the type of socket. */
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}

	/* Forcefully attaching socket to the port 8080 */
	int setsocket = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (setsocket)
	{
		std::cerr << "Setsockopt bekleniyor." << std::endl;
		//exit(1);
	}

	/* Creating socket and checking the address. */
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY; //sin_addr.s_add -> specifying ip address
	address.sin_port = htons(PORT);
	/* 	"htons" işlevi, "host byte order" olarak bilinen yerel bilgisayarın byte sırasını,
	"network byte order" olarak bilinen r.
	"PORT" değişkeni, kullanılacak olan bağlantı noktası numarasını tutar. */

	/* 	Forcefully attaching socket to the port 8080
	bind -> bir socketin belirli bir ağ adresine ve bağlantı noktasına
	bağlanmasını sağlar.
	bind işlevi, soket dosya tanımlayıcısı, bir adres yapısı ve adres yapısının boyutu gibi parametreleri alır. */
	int bind_x = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (bind_x < 0)
	{
		std::cerr << "bind failed" << std::endl;
		exit(1);
	}
	/* The listen system call allows the process to listen on the socket for connections. 
	The first argument is the socket file descriptor, and the second is the size of the backlog queue  */
	int listen_fd = listen(server_fd, 30);
	if (listen_fd < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(1);
	}
	/* The accept() system call causes the process to block until a client connects to the server.
	It returns a new file descriptor, */
	std::string message;
	while (1)
	{
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
			(socklen_t*)&addrlen)) < 0)
		{
			std::cerr << "accept failed" << std::endl;
			exit(1);
		}
		while (!strstr(buffer, "\n\r"))
		{
			memset(buffer, 0, BUFFER_SIZE);
			valread = read(new_socket, buffer, BUFFER_SIZE);
			message.append(buffer);
			if (strstr(message.c_str(), "QUIT"))
			{
				exit(1);
			}
			std::cout << message << std::endl;
		}
	}
	
	//closing the connected socket
	close(new_socket);
	//closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return (0);
}
