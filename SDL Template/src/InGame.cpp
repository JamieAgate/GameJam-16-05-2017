#include "InGame.h"

InGame::InGame(SDL_Renderer* _renderer, GameStateManager* _manager, InputManager* _input) :
	GameState(_manager, _renderer)
{
	input = NULL;
	this->input = _input;
	mapData = NULL;
	net = NULL;

	LoadCollisionMap("resources\\map\\map.png", 2560, 1440);

 	players.push_back(new Player(input, renderer));
	players[0]->LoadMapData(mapData->GetMapData());

	net = new TCPConnection();

	net->Init();
}

InGame::~InGame()
{

}

void InGame::Update()
{
	players[0]->Update();

	players[0]->Draw();
}

void InGame::LoadCollisionMap(char* _filePath, int _w, int _h)
{
	if (mapData != NULL) { delete mapData; }
	mapData = new CollisionMap(_filePath, _w, _h);
}