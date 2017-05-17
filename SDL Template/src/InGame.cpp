#include "InGame.h"

InGame::InGame(SDL_Renderer* _renderer, GameStateManager* _manager, InputManager* _input) :
	GameState(_manager, _renderer)
{
	input = NULL;
	this->input = _input;
	mapData = NULL;

	LoadCollisionMap("resources\\map\\map.png", 2560, 1440);
	map = new Sprite(_renderer, "resources\\map\\map.png",0,0, 2560, 1440);
 	players.push_back(new Player(input, renderer));
	players[0]->LoadMapData(mapData->GetMapData());
	cameraRenderBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2560, 1440);
}

InGame::~InGame()
{
	for (int i = 0; i < players.size(); i++)
	{
		delete players.at(i);
	}
}

void InGame::Update()
{
	players[0]->Update();
	UpdateCamera();
}

void InGame::UpdateCamera()
{
	camera.x = players[0]->GetPlayerX() - 600;
	if (camera.x > 1280)
	{
		camera.x = 1280;
	}
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	camera.y = players[0]->GetPlayerY() - 320;
	if (camera.y > 720)
	{
		camera.y = 720;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
}

void InGame::LoadCollisionMap(char* _filePath, int _w, int _h)
{
	if (mapData != NULL) { delete mapData; }
	mapData = new CollisionMap(_filePath, _w, _h);
}

void InGame::Draw()
{
	SDL_SetRenderTarget(renderer, cameraRenderBuffer);
	SDL_RenderClear(renderer);
	map->Draw();
	players[0]->Draw();
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, cameraRenderBuffer, &camera, &screen);
}