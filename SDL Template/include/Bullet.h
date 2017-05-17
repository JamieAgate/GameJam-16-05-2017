#pragma once
#include "AnimSprite.h"

//BULLET DATA STRUCT
struct BulletData
{
	float x, y, xVel, yVel;
};

class Bullet
{
public:
	Bullet(SDL_Renderer* _renderer, AnimSprite* BulletSprite);
	~Bullet();

	void Setup(int _x, int _y, glm::vec2 _velocity);
	bool GetIsActive() { return isActive; }
	bool GetCanBeDestroyed() { return canBeDestroyed; }

	void SetCanBeDestroyed(bool _v) { canBeDestroyed = _v; }
	void SetIsActive(bool _v) { isActive = _v; }

	int GetX() { return sprite->GetX(); }
	int GetY() { return sprite->GetY(); }
	int GetW() { return sprite->GetW(); }
	int GetH() { return sprite->GetH(); }

	void Update();
	void Draw();

	BulletData GetBulletData();

private:
	bool isActive;
	bool canBeDestroyed;
	float angle;
	glm::vec2 velocity;
	SDL_Renderer* renderer;
	AnimSprite* sprite;

	float xPos, yPos;
};
