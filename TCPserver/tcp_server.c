#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
	
	// Initalize a message for the connecting clients
	char server_message[256] = "You have reached the server!\n";

	// Create a socket on teh server
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//Bind teh socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	// The second parameter is used to speify how many people can be waiting to use
	// the socket at any given time
	listen(server_socket, 5);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// Send the message to the client
	send(client_socket, server_message, sizeof(server_message), 0);

	// Close the socket
	close(server_socket);

	return 0;
}
