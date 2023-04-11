#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **av) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int server_port = atoi(av[1]);

    // create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket to port" << std::endl;
        return 1;
    }

    // listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Error listening for incoming connections" << std::endl;
        return 1;
    }

    // accept incoming connection
    socklen_t client_addr_size = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_fd < 0) {
        std::cerr << "Error accepting incoming connection" << std::endl;
        return 1;
    }
    socklen_t client_addr_size1 = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_fd < 0) {
        std::cerr << "Error accepting incoming connection" << std::endl;
        return 1;
    }

    // connection accepted, do something with client_fd
    char a[10000];
    while(1)
    {
        memset(a, 0, 10000);
        recv(client_fd, a, 10000, 0);
        std::cout << a << std::endl;
    }
    // close sockets
    close(client_fd);
    close(server_fd);

    return 0;
}
