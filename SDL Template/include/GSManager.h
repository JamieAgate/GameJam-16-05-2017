#pragma once
#include "GameStates.h"
#include <vector>

class GameStateManager
{
public:
	~GameStateManager();//Game State Manager Destructor

	void AddState(GameState* _gState); //adds a game state to the Game states Vector
	void ChangeState(GameState* _gState); //changes to a new game state
	void RemoveLastState(); //removes last state from the vector

	void UpdateState(); //updates most recent Game State on the vector
	void DrawState(); //draws the most recent Game State on the vector

	bool CheckStateExit() { return gameStatesVector.back()->CheckExit(); }
private:
	std::vector<GameState*> gameStatesVector; //vector that holds all Game states
};