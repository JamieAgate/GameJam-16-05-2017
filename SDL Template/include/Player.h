#pragma once
#include "AnimSprite.h"
#include "InputManager.h"
#include "CollisionMap.h"

class Player
{
public:
	Player(InputManager* _input, SDL_Renderer* _renderer);
	~Player();

	void Update();
	void Draw();

	void LoadMapData(std::vector<int> _mapData) { mapData = _mapData; }
private:
	SDL_Renderer* renderer;
	InputManager* input = NULL;
	std::vector<int> mapData;
	AnimSprite* playerSprite;


	//Private Functions///////////////////////////
	bool InitPlayer();

	//Movement Functions and variables
	void UpdateXMovement();
	void UpdateYMovement();

	int moveX;
	int moveY;

	int speed;

	//Collision Functions and variables
	bool CheckCollision(int _yOffset, int _xOffset);
	bool CheckPixelData(int _yOffset, int _xOffset);

	int col;
	int checkPixel;
};