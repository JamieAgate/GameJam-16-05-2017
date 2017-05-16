#include "GSManager.h"

GameStateManager::~GameStateManager()
{
	for (unsigned int i = 0; i < gameStatesVector.size(); i++)//deletes all game states on the vector
	{
		delete gameStatesVector.at(i);
	}
}

void GameStateManager::AddState(GameState* _gState)
{
	gameStatesVector.push_back(_gState); //add game state to the top of the vector
}

void GameStateManager::ChangeState(GameState* _gState)
{
	for (unsigned int i = 0; i < gameStatesVector.size(); i++) { //delete all current States on the vector
		delete gameStatesVector.at(i);
	}
	gameStatesVector.clear(); //clears the vector
	AddState(_gState); //adds new state to the vector
}

void GameStateManager::RemoveLastState()
{
	delete gameStatesVector.back(); //delete game state at top of vector
	gameStatesVector.pop_back(); //pops deleted game state off of vector
}

void GameStateManager::UpdateState()
{
	gameStatesVector.back()->Update(); //updates current game state
}

void GameStateManager::DrawStates()
{
	for (unsigned int i = 0; i < gameStatesVector.size(); i++) { //draws all states in the vector
		gameStatesVector.at(i)->Draw();
	}
}

