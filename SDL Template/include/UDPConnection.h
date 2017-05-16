#pragma once
#include "SDLInit.h"
#include <string>

class UDPConnection
{
public:
	UDPConnection();	// constructor
	~UDPConnection();	// destructor

	bool Init(); // get everything going

	void Send(std::string _data);

	std::string Recv();

private:

	char ipAddress[20];
	int port;

	UDPsocket socket;
	IPaddress remoteIP;
	UDPpacket* packet;
};
