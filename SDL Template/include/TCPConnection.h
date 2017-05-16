#pragma once
#include "SDLInit.h"
#include <string>

class TCPConnection
{
public:

	TCPConnection();
	~TCPConnection();

	bool Init(); //Initialise connection to server
	void Send(std::string _data);
	std::string Recv();

	int GetConnectionID() { return connectionID; }

private:

	IPaddress server;
	TCPsocket clientSocket;
	SDLNet_SocketSet socketSet;
	int connectionID;

	char serverIP[20];
	int port;

	static const int BUFFER_SIZE = 512;
	char buffer[512];

};