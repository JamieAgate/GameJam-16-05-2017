#pragma once
#include "SDLInit.h"
#include "GameStates.h"
#include "GSManager.h"
#include "InputManager.h"
#include "CollisionMap.h"

class InGame : public GameState
{
public:
	InGame(SDL_Renderer* _renderer, GameStateManager* _manager, InputManager* _input);
	~InGame();

	void LoadCollisionMap(char* _filePath, int _w, int _h);

private:
	InputManager* input;
	CollisionMap* mapData;
};