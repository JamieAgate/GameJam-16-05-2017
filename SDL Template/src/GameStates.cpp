#include "GameStates.h"

GameState::GameState(GameStateManager* _gsManager, SDL_Renderer* _renderer)
{
	GS_Manager = _gsManager;
	renderer = _renderer;
	exit = false;
}

GameState::~GameState()
{
	
}

void GameState::Update()
{
	//will be filled in the real states
}

void GameState::Draw()
{
	//will be filled in the real states
}