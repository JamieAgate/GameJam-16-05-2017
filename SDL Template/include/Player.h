#pragma once
#include "AnimSprite.h"
#include "InputManager.h"
#include "CollisionMap.h"
#include "Bullet.h"
#include "TextSprite.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

class Player
{
public:
	Player(InputManager* _input, SDL_Renderer* _renderer, int _playerID, bool _isRemote);
	~Player();

	void Update(std::vector<Player*> _otherPlayers);
	void Draw();

	int GetPlayerX() { return playerSprite->GetX(); }
	int GetPlayerY() { return playerSprite->GetY(); }
	float GetPlayerAng() { return angle; }
	SDL_Rect& GetRect() { return playerSprite->GetRect(); }

	void LoadMapData(std::vector<Uint8> _mapData) { mapData = _mapData; }

	void AssignID(int _playerID) { playerID = _playerID; }

	void SetRelativeMousePos(int _x, int _y) { mouseWorldX = _x; mouseWorldY = _y; }

	void UpdateBullets(std::vector<Player*> _otherPlayers);

	void SetMove(int _x, int _y) { moveX = _x; moveY = _y; }

	//Network functions
	bool IsRemotePlayer() { return isRemote; }
	int GetID() { return playerID; }
	void NetworkUpdate(int _x, int _y, float _angle);

	bool SpawningBullet() { return requestingBullet; }
	std::string CreateProjectilePacket();

	std::string CreateNetString();

	void CreateNetBullet(float _x, float _y, float _xVel, float _yVel, int _damage, int _playerID);

private:
	SDL_Renderer* renderer;
	InputManager* input;
	std::vector<Uint8> mapData;
	AnimSprite* playerSprite;

	AnimSprite* monofont = NULL;
	TextSprite* text = NULL;
	//HUD AF

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

	//Firing variables
	int shotTimer = 0;
	int shotDelay = 20;
	bool canShoot = true;
	bool requestingBullet = false;

	//Projectile Properties
	int damage = 5;

	//Player Properties
	int health;
};