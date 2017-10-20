#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

// Contains a structre to hold the remote port and ip we want
#include <netinet/in.h>

int main() {
	// Cerate a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	// htons() converts an integer into a port value that can be made sense
	// of by the included libraries
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// This returns an integer that cna be used to debug connection errors
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// Check for error with the connection
	if (connection_status == -1) {
		printf("There was an error making a connection with teh remote socket\n\n");
	}
	
	// Recive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// Print our the server's response
	printf("The server sent the data: %s", server_response);

	//Closes the socket for when we are done
	close(network_socket);

	return 0;
}
