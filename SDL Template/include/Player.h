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
	void Draw(std::vector<Player*> _otherPlayers);

	int GetPlayerX() { return playerSprite->GetX(); }
	int GetPlayerY() { return playerSprite->GetY(); }
	float GetPlayerAng() { return angle; }
	SDL_Rect& GetRect() { return playerSprite->GetRect(); }

	void LoadMapData(std::vector<Uint8> _mapData) { mapData = _mapData; }

	void AssignID(int _playerID) { playerID = _playerID; }

	void SetRelativeMousePos(int _x, int _y) { mouseWorldX = _x; mouseWorldY = _y; }

	void UpdateBullets(std::vector<Player*> _otherPlayers);

	void SetMove(int _x, int _y) { moveX = _x; moveY = _y; }

	bool GetDead() { return death; }

	//Network functions
	bool IsRemotePlayer() { return isRemote; }
	int GetID() { return playerID; }
	void NetworkUpdate(int _x, int _y, float _angle);

	bool SpawningBullet() { return requestingBullet; }
	std::string CreateProjectilePacket();

	std::string CreateNetString();
	
	void SetDeath(bool _death) { death = _death; }

	bool CheckRespawn();

	void CreateNetBullet(float _x, float _y, float _xVel, float _yVel, int _damage, int _playerID);

	int GetKillerID() { int killer = killerID; killerID = -1; return killer; }

	void GiveCameraPos(int _x, int _y) { cameraPosX = _x; cameraPosY = _y; }
	int GetFrags() { return frags; }

	void GiveFrag() { frags++; }

private:
	SDL_Renderer* renderer;
	InputManager* input;
	std::vector<Uint8> mapData;
	AnimSprite* playerSprite;
	Sprite* deathScreen;
	Sprite* cursorSprite;

	AnimSprite* monofont = NULL;
	TextSprite* text = NULL;
	//HUD AF

	bool respawn = false;

	//Bullets
	std::vector<Bullet*> bullets;
	AnimSprite* bulletSprite;
	bool isFiring;

	//Private Functions///////////////////////////
	bool InitPlayer();
	void CheckDeath();
	void DeathUpdate();
	void UpdateAnim();
	int timer;
	int cursorX;
	bool drawCursor;

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

	int killerID;

	//Firing variables
	int shotTimer = 0;
	int shotDelay = 10;
	bool canShoot = true;
	bool requestingBullet = false;

	//Projectile Properties
	int damage = 7;

	//Player Properties
	int health;
	bool death;
	int frags;
	float bulletVelocity;

	//HUD PARAMS
	int cameraPosX;
	int cameraPosY;

	//Animatin Parameters
	int frameTimer = 0;
	int frameTick = 0;
	int frameDelay = 5;
};