#pragma once
#include "SDLInit.h"
#include <vector>
#include <string>
#include <sstream>

class GameServer
{
public:
	GameServer(int _port, int _maxClients);
	~GameServer();

	bool Init();
	void Update();

private:
	void CheckForConnectionRequests();
	void CheckClientSockets();
	void SendData(TCPsocket& _socket, std::string& _data);

	static const int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];

	int port;
	int maxClients;
	int maxSockets;
	int connectionCount;

	IPaddress serverIP;
	TCPsocket serverSocket;
	SDLNet_SocketSet socketSet;

	std::vector<TCPsocket> clientSockets;

	bool* idList;
};