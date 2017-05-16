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

	void LoadMapData(std::vector<Uint8> _mapData) { mapData = _mapData; }
private:
	SDL_Renderer* renderer;
	InputManager* input;
	std::vector<Uint8> mapData;
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