#pragma once
#include "AnimSprite.h"

class Bullet
{
public:
	Bullet(SDL_Renderer* _renderer);
	~Bullet();

	void Setup(int _x, int _y, glm::vec2 _velocity);

	void Update();
	void Draw();
private:
	bool isActive;
	bool canBeDestroyed;
	float angle;
	glm::vec2 velocity;
	SDL_Renderer* renderer;
	AnimSprite* sprite;
};