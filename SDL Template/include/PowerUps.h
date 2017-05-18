#pragma once
#include "AnimSprite.h"
#include <glm.hpp>

class PowerUp
{
public:
	PowerUp(AnimSprite* _PowerUp, int _name, glm::vec2 spawn);
	~PowerUp();

	void Update();

	glm::vec2 GetUsedSpawnPoint() { return glm::vec2(sprite->GetX(), sprite->GetY()); }
	SDL_Rect GetHitbox() { return hitbox; }

	void Draw();
private:
	SDL_Rect hitbox;
	int duration;
	char powerUpID;
	AnimSprite*	sprite;
};