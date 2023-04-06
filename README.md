# Introduction to SocketProgramming

Sockets are commonly used for client and server interaction. 
Typical system configuration places the server on one machine, with the clients on other machines. 
The clients connect to the server, exchange information, and then disconnect.

A socket has a typical flow of events.
In a connection-oriented client-to-server model, the socket on the server process waits for requests from a client. To do this, 
the server first establishes (binds) an address that clients can use to find the server. When the address is established, 
the server waits for clients to request a service. 
The client-to-server data exchange takes place when a client connects to the server through a socket. 
The server performs the client's request and sends the reply back to the client.

![socket](https://user-images.githubusercontent.com/73845925/230378632-a7e795d3-e6e4-406a-a50d-5f37f4883da1.png)
