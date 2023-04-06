#include "server.hpp"

/* A sockaddr_in is a structure containing an internet address. This structure is defined in <netinet/in.h>. Here is the definition:
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
}; */

/* argv[0] = filename
   argv[1] = port
   argv[2] = passwd */

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Arg Error." << std::endl;
		exit(1);
	}
	int server_fd, new_socket, n, setsocket, bind_x;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};
	struct hostent *server;

	const int port = std::stoi(argv[1]);
	const std::string password = argv[2];
	std::cout << "Starting IRC server on port " << std::endl;

	/* Create a socket */
	server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		return (1);
	}

	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		std::cerr << "Error, no such host" << std::endl;
		return (1);
	}

	/* Forcefully attaching socket to the port 8080 */
	setsocket = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (setsocket != 0)
		std::cout << "Setsockopt bekleniyor." << std::endl;
	else
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		return (1);
	}

	/* Creating socket and checking the address. */
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY; //sin_addr.s_add -> specifying ip address
	address.sin_port = htons(atoi(argv[1]));
	/* 	"htons" işlevi, "host byte order" olarak bilinen yerel bilgisayarın byte sırasını,
	"network byte order" olarak bilinen r.
	"PORT" değişkeni, kullanılacak olan bağlantı noktası numarasını tutar. */

	/* 	Forcefully attaching socket to the port 8080
	bind -> bir socketin belirli bir ağ adresine ve bağlantı noktasına
	bağlanmasını sağlar.
	bind işlevi, soket dosya tanımlayıcısı, bir adres yapısı ve adres yapısının boyutu gibi parametreleri alır. */
	bind_x = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (bind_x < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		return (1);
	}
	/* The listen system call allows the process to listen on the socket for connections.
	The first argument is the socket file descriptor, and the second is the size of the backlog queue  */
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		return (1);
	}
	/* The accept() system call causes the process to block until a client connects to the server.
	It returns a new file descriptor, */
	std::string message;
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
			(socklen_t*)&addrlen)) < 0)
		{
			std::cerr << "Accept failed" << std::endl;
			return (1);
		}
		while (!strstr(buffer, "\n\r"))
		{
			memset(buffer, 0, BUFFER_SIZE);
			n = recv(new_socket, buffer, BUFFER_SIZE, 0); //very similar to read.
			if (n < 0)
			{
				std::cerr << "Error on reading." << std::endl;
				return (1);
			}
			message.append(buffer);
			if (strstr(message.c_str(), "QUIT"))
			{
				std::cout << "\033[1;93mLeaving...\033[0m" << std::endl;
				exit(1);
			}
			// else if (strstr(message.c_str(), "USER"))
			// {

			// }
			// else if (strstr(message.c_str(), "JOIN"))
			// {

			// }
			std::cout << message << std::endl;
		}
	}

	//closing the connected socket
	close(new_socket);
	//closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return (0);
}
