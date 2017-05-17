#pragma once
#include "SDLInit.h"
#include "GameStates.h"
#include "GSManager.h"
#include "InputManager.h"
#include "CollisionMap.h"
#include "Player.h"

class InGame : public GameState
{
public:
	InGame(SDL_Renderer* _renderer, GameStateManager* _manager, InputManager* _input);
	~InGame();

	void Update() override;
	void Draw() override;

	void LoadCollisionMap(char* _filePath, int _w, int _h);

private:
	InputManager* input;
	CollisionMap* mapData;
	Sprite* map;

	//camera
	void UpdateCamera();
	SDL_Rect camera{ 0,0,1280,720 };
	SDL_Rect screen{ 0,0,1280,720 };
	SDL_Texture* cameraRenderBuffer;

	std::vector<Player*> players;
};