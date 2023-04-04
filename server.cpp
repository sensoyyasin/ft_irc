#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <unistd.h>
#define PORT 8080

int main(int argc, char **argv)
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	/* Creating socket file descriptor */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}

	/* Forcefully attaching socket to the port 8080 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		std::cerr << "Setsockopt" << std::endl;
		exit(1);
	}
	/* Creating socket and checking the address. */
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY; //sin_addr.s_add -> specifying ip address
	address.sin_port = htons(PORT);
	/* 	"htons" işlevi, "host byte order" olarak bilinen yerel bilgisayarın byte sırasını,
	"network byte order" olarak bilinen ağ byte sırasına dönüştürür.
	"PORT" değişkeni, kullanılacak olan bağlantı noktası numarasını tutar. */

	/* 	Forcefully attaching socket to the port 8080
	bind -> bir socketin belirli bir ağ adresine ve bağlantı noktasına
	bağlanmasını sağlar.
	bind işlevi, soket dosya tanımlayıcısı, bir adres yapısı ve adres yapısının boyutu gibi parametreleri alır. */
	if (bind(server_fd, (struct sockaddr*)&address,
		sizeof(address)) < 0)
	{
		std::cerr << "bind failed" << std::endl;
		exit(1);
	}
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(1);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
		(socklen_t*)&addrlen)) < 0)
	{
		std::cerr << "accept failed" << std::endl;
		exit(1);
	}
	valread = read(new_socket, buffer, 1024);
	std::cout << buffer << std::endl;
	send(new_socket, hello, strlen(hello), 0);
	std::cout << "Hello message sent" << std::endl;

	//closing the connected socket
	close(new_socket);
	//closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return (0);
}
