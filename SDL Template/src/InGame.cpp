#include "InGame.h"

InGame::InGame(SDL_Renderer* _renderer, GameStateManager* _manager, InputManager* _input) :
	GameState(_manager, _renderer)
{
	input = NULL;
	this->input = _input;
	mapData = NULL;
	net = NULL;

	LoadCollisionMap("resources\\map\\complex.png", 2560, 1440);
	map = new Sprite(_renderer, "resources\\map\\complex.png",0,0, 2560, 1440);
	cameraRenderBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2560, 1440);

	net = new TCPConnection();

	net->Init();

	players.push_back(new Player(input, renderer, net->GetConnectionID(), false));
	players[0]->LoadMapData(mapData->GetMapData());

	glm::vec2 spawnPoint = respawnPoints[rand() % respawnPoints.size()];
	players[0]->NetworkUpdate(spawnPoint.x, spawnPoint.y, 0);
	players[0]->SetMove(spawnPoint.x, spawnPoint.y);

	networkTimer = 0;

	char* tracks[5];

	int track = -1;
	tracks[++track] = "Resources\\Music\\fantastique.mp3";
	tracks[++track] = "Resources\\Music\\JackADandy.mp3";
	tracks[++track] = "Resources\\Music\\Macintosh.mp3";
	tracks[++track] = "Resources\\Music\\Metalcrush.mp3";
	tracks[++track] = "Resources\\Music\\Grandma.mp3";

	sounds = new SoundManager(1, tracks[rand() % 5]);
	sounds->PlayBGM(-1);
}

InGame::~InGame()
{
	std::stringstream ss;
	ss << "|" << players[0]->GetID() << " ]";
	net->Send(ss.str());

	for (int i = 0; i < players.size(); i++)
	{
		delete players.at(i);
	}

	delete map;
	SDL_DestroyTexture(cameraRenderBuffer);
}

void InGame::Update()
{
	networkTimer++;
	int dataTest = 0;

	std::stringstream mainPacket;

	players[0]->Update(players);
	UpdateCamera();
	players[0]->SetRelativeMousePos(camera.x, camera.y);

	if (input->WasKeyPressed(SDL_SCANCODE_ESCAPE)) {
		std::stringstream ss;
		ss << "|" << " " << players[0]->GetID() << " ]";
		net->Send(ss.str());
	}
	
	mainPacket << players[0]->CreateNetString();

	//Check if player wants to send bullet data to server
	if (players[0]->SpawningBullet()) {
		mainPacket << players[0]->CreateProjectilePacket();
		dataTest++;
	}

	if (players[0]->GetDead()) {
		mainPacket << "-" << " " << players[0]->GetID() << " ";

		if (players[0]->CheckRespawn()) {
			glm::vec2 spawnPoint = respawnPoints[rand() % respawnPoints.size()];
			players[0]->NetworkUpdate(spawnPoint.x, spawnPoint.y, 0);
			players[0]->SetMove(spawnPoint.x, spawnPoint.y);
			players[0]->SetDeath(false);
		}
	}
	else {
		mainPacket << "+" << " " << players[0]->GetID() << " ";
	}

	net->Send(mainPacket.str());

	NetRecv();
}

void InGame::UpdateCamera()
{
	camera.x = players[0]->GetPlayerX() - 640;
	if (camera.x > 1280)
	{
		camera.x = 1280;
	}
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	camera.y = players[0]->GetPlayerY() - 360;
	if (camera.y > 720)
	{
		camera.y = 720;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}

	//std::cout << camera.x << " , " << camera.y << "\n";
}

void InGame::LoadCollisionMap(char* _filePath, int _w, int _h)
{
	if (mapData != NULL) { delete mapData; }
	mapData = new CollisionMap(_filePath, _w, _h);

	std::vector<unsigned char> loadData = mapData->GetMapData();

	for (int i = 0; i < _w * _h; i++) {
		int data = (int)loadData[i];

		if (data == 100) { //RESPAWN POOINTS
			respawnPoints.push_back(glm::vec2(i % 2560, i / 2560));
		}

	}
}

void InGame::Draw()
{
	SDL_SetRenderTarget(renderer, cameraRenderBuffer);
	SDL_RenderClear(renderer);
	map->Draw();
	
	//Draw all players
	for (Player* p : players) {
		if (!p->GetDead()) {
			p->Draw();
		}
	}
	if (players[0]->GetDead())
	{
		players[0]->Draw();
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, cameraRenderBuffer, &camera, &screen);
}

void InGame::NetSend()
{
	std::stringstream ss;

	for (Player* p : players) {
		if (!p->IsRemotePlayer()) {
			ss << p->CreateNetString();
		}
	}

	std::string msg(ss.str());
	net->Send(msg);
}

void InGame::NetRecv()
{
	std::string msg = net->Recv();

	if (msg == "") return;

	std::stringstream ss(msg);

	std::string segment;

	while (ss >> segment) {
		if (segment == "[") { //Movement Data

			int playerID, posX, posY;
			float playerAngle;

			ss >> playerID;
			ss >> posX;
			ss >> posY;
			ss >> playerAngle;

			Player* netPlayer = NULL;
			for (Player* p : players) {
				if (p->GetID() == playerID) {
					netPlayer = p;
				}
			}

			if (netPlayer == NULL) {
				netPlayer = new Player(input, renderer, playerID, true);
				players.push_back(netPlayer);
			}

			netPlayer->NetworkUpdate(posX, posY, playerAngle);
		}

		if (segment == "|") { //Deletion request
			
			int deleteID;
			ss >> deleteID;

			std::cout << "Recieved deletion request for " << deleteID << "\n";

			for (int i = 0; i < players.size(); i++) {
				if (players[i]->GetID() == deleteID) {
					delete players[i];
					players[i] = nullptr;
				}
			}

			players.erase(std::remove(players.begin(), players.end(), nullptr), players.end());
		}

		if (segment == "<") { //Projectile Data
			float pX, pY, pXVel, pYVel;
			int pID, pDamage;

			ss >> pX;
			ss >> pY;
			ss >> pXVel;
			ss >> pYVel;
			ss >> pDamage;
			ss >> pID;

			players[0]->CreateNetBullet(pX, pY, pXVel, pYVel, pDamage, pID);
		}
		if (segment == "-") {
			int pID;
			ss >> pID;

			for (int i = 0; i < players.size(); i++) {
				if (players[i]->GetID() == pID) {
					players[i]->SetDeath(true);
				}
			}
		}
		if (segment == "+") {
			int pID;
			ss >> pID;

			for (int i = 0; i < players.size(); i++) {
				if (players[i]->GetID() == pID) {
					players[i]->SetDeath(false);
				}
			}
		}
	}
}