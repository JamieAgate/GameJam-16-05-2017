#include "UDPConnection.h"

UDPConnection::UDPConnection()
{
	std::cout << "Enter IP: ";
	std::cin >> ipAddress;

	std::cout << "Enter port to use: ";
	std::cin >> port;
}

UDPConnection::~UDPConnection()
{
	SDLNet_FreePacket(packet); //Free up packet memory
}

bool UDPConnection::Init()
{
	socket = SDLNet_UDP_Open(port);

	SDLNet_ResolveHost(&remoteIP, ipAddress, port);

	packet = SDLNet_AllocPacket(512);

	packet->address.host = remoteIP.host;
	packet->address.port = remoteIP.port;

	return true;
}

void UDPConnection::Send(std::string _data)
{
	memcpy(packet->data, _data.c_str(), _data.length());
	packet->len = _data.length();

	SDLNet_UDP_Send(socket, -1, packet);
}

std::string UDPConnection::Recv()
{
	if (SDLNet_UDP_Recv(socket, packet)) { return std::string((char*)packet->data); }
	else { return ""; }
}