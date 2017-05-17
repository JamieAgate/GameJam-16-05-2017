#include "GameServer.h"

GameServer::GameServer(int _port, int _maxClients)
{
	port = _port;
	maxClients = _maxClients;

	maxSockets = maxClients + 1;
	connectionCount = 0;

	idList = new bool[maxSockets] { false };
	idList[0] = true;
}

GameServer::~GameServer()
{
	delete idList;
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_TCP_Close(serverSocket);
}

bool GameServer::Init()
{
	socketSet = SDLNet_AllocSocketSet(maxSockets);
	if (socketSet == NULL) {
		std::cout << "Server failed to create socket set: " << SDLNet_GetError() << "\n";
		return false;
	}

	if (SDLNet_ResolveHost(&serverIP, NULL, port)) {
		std::cout << "Failed to resolve server host: " << SDLNet_GetError() << "\n";
		return false;
	}

	serverSocket = SDLNet_TCP_Open(&serverIP);
	if (!serverSocket) {
		std::cout << "Unable to open server socket: " << SDLNet_GetError() << "\n";
		return false;
	}

	std::cout << "Server listening on port: " << SDLNet_Read16(&serverIP.port) << "\n\n";

	SDLNet_TCP_AddSocket(socketSet, serverSocket);
	return true;
}

void GameServer::Update()
{
	CheckForConnectionRequests();
	CheckClientSockets();
}

//PRIVATE FUNCTIONS
void GameServer::CheckForConnectionRequests()
{
	SDLNet_CheckSockets(socketSet, 0);
	if (SDLNet_SocketReady(serverSocket) != 0) {
		if (clientSockets.size() < maxClients) {
			clientSockets.push_back(SDLNet_TCP_Accept(serverSocket));
			SDLNet_TCP_AddSocket(socketSet, clientSockets.back());

			std::stringstream msg;

			for (int i = 0; i < maxSockets; i++) {

				if (!idList[i]) {
					msg << "OK:" << i;
					SendData(clientSockets.back(), msg.str());
					idList[i] = true;

					break;
				}
			}

			std::cout << "Client connected: (" << clientSockets.size() << "/" << maxClients << ")\n";
		}
		else {
			std::cout << "Player is trying to join full server!\n";

			TCPsocket tempSocket = SDLNet_TCP_Accept(serverSocket);
			SendData(tempSocket, std::string("Rejected, server full"));
			SDLNet_TCP_Close(tempSocket);
		}
	}
}

void GameServer::CheckClientSockets()
{
	for (int client = 0; client < clientSockets.size(); client++) {
		if (SDLNet_SocketReady(clientSockets[client]) != 0) {
			if (SDLNet_TCP_Recv(clientSockets[client], buffer, BUFFER_SIZE) <= 0) {
				SDLNet_TCP_DelSocket(socketSet, clientSockets[client]);
				SDLNet_TCP_Close(clientSockets[client]);
				clientSockets.erase(clientSockets.begin());
				std::cout << "Server has " << clientSockets.size() << " client(s) \n";
				idList[client + 1] = false;
			}
			else {
				for (int i = 0; i < clientSockets.size(); i++) {
					int msgLength = strlen(buffer) + 1;
					if (i != client) {
						SDLNet_TCP_Send(clientSockets[i], (void *)buffer, msgLength);
					}

					if (buffer[0] == '|') {
						SDLNet_TCP_Send(clientSockets[i], (void *)buffer, msgLength);
						std::cout << buffer << "\n";
					}
				}

				if (buffer[0] == '|') {
					std::cout << "Recieved a deletion request for ID number: " << buffer[1] << "\n";
				}
			}
		}
	}
}

void GameServer::SendData(TCPsocket& _socket, std::string& _data)
{
	strcpy_s(buffer, _data.c_str());
	int msgLength = strlen(buffer) + 1;
	SDLNet_TCP_Send(_socket, buffer, msgLength);
}