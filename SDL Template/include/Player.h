#pragma once
#include "AnimSprite.h"
#include "InputManager.h"
#include "CollisionMap.h"
#include "Bullet.h"
#include <sstream>
#include <vector>
#include <algorithm>

class Player
{
public:
	Player(InputManager* _input, SDL_Renderer* _renderer, int _playerID, bool _isRemote);
	~Player();

	void Update();
	void Draw();

	int GetPlayerX() { return playerSprite->GetX(); }
	int GetPlayerY() { return playerSprite->GetY(); }
	float GetPlayerAng() { return angle; }

	void LoadMapData(std::vector<Uint8> _mapData) { mapData = _mapData; }

	void AssignID(int _playerID) { playerID = _playerID; }

	void SetRelativeMousePos(int _x, int _y) { mouseWorldX = _x; mouseWorldY = _y; }

	void UpdateBullets();

	//Network functions
	bool IsRemotePlayer() { return isRemote; }
	int GetID() { return playerID; }
	void NetworkUpdate(int _x, int _y, float _angle);

	std::string CreateNetString();

private:
	SDL_Renderer* renderer;
	InputManager* input;
	std::vector<Uint8> mapData;
	AnimSprite* playerSprite;

	//Bullets
	std::vector<Bullet*> bullets;
	AnimSprite* bulletSprite;
	bool isFiring;

	//Private Functions///////////////////////////
	bool InitPlayer();

	//Movement Functions and variables
	void UpdateXMovement();
	void UpdateYMovement();
	void UpdateRotation();

	int moveX;
	int moveY;
	int speed;

	int mouseX;
	int mouseY;
	int mouseWorldX;
	int mouseWorldY;
	float angle;
	//Collision Functions and variables
	bool CheckCollision(int _yOffset, int _xOffset);
	bool CheckPixelData(int _yOffset, int _xOffset);
	bool CheckPixelData(int _yOffset, int _xOffset, int _H, int _W);

	int col;
	int checkPixel;

	//NETWORK PARAMETERS
	int playerID;
	bool isRemote; 
};