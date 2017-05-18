#include "TCPConnection.h"

TCPConnection::TCPConnection()
{
	std::cout << "Enter server IP: ";
	std::cin >> serverIP;

	std::cout << "Enter server port: ";
	std::cin >> port;

	connectionID = -1;
}

TCPConnection::~TCPConnection()
{
	SDLNet_TCP_Close(clientSocket);
}

bool TCPConnection::Init()
{
	socketSet = SDLNet_AllocSocketSet(1); //Allocate the socket
	if (socketSet == NULL) {
		std::cout << "Socket set failed to allocate: " << SDLNet_GetError() << "\n";
		return false;
	}

	if (SDLNet_ResolveHost(&server, serverIP, port) == -1) { //Find the server
		std::cout << "Couldn't connect to the server: " << SDLNet_GetError() << "\n";
		return false;
	}

	clientSocket = SDLNet_TCP_Open(&server); //Open a connection
	if (!clientSocket) {
		std::cout << "Couldn't establish server socket: " << SDLNet_GetError() << "\n";
		return false;
	}

	SDLNet_TCP_AddSocket(socketSet, clientSocket); //Add the socket to the set

	SDLNet_CheckSockets(socketSet, 5000); //Give the server 5 seconds to return a status

	int response = SDLNet_SocketReady(clientSocket); //Check servers response

	if (response != 0) { //Has the server responded?
		int bytesRecieved = SDLNet_TCP_Recv(clientSocket, buffer, BUFFER_SIZE);

		if (strncmp(buffer, "OK:", 3) == 0) { // You can join!
			connectionID = std::strtol(&buffer[3], NULL, 10);
			std::cout << "Joining server as player " << connectionID << "\n";
		}
		else {
			std::cout << "Server is full!\n";
			return false;
		}
	}
	else {
		std::cout << "No response from server\n";
		return false;
	}

	return true;
}

void TCPConnection::Send(std::string _data)
{
	strcpy_s(buffer, _data.c_str()); //Copy data to buffer

	int len = strlen(buffer) + 1; //Specify length as one greater than the buffer to allow for \0 terminator

	 SDLNet_TCP_Send(clientSocket, (void *)buffer, len); //Send data to server
}

std::string TCPConnection::Recv()
{
	if (SDLNet_CheckSockets(socketSet, 0) != 0) { //Has any data been recieved?
		if (SDLNet_SocketReady(clientSocket)) {
			SDLNet_TCP_Recv(clientSocket, buffer, BUFFER_SIZE); //Recieve data into buffer
			return std::string(buffer); //return buffer to calling function
		}
	}

	return ""; //No data recieved, return empty string
}