#pragma once
#include "AnimSprite.h"

class PowerUp
{
public:
	PowerUp(AnimSprite* _PowerUp, char _name);
	~PowerUp();

	void Update();
	void Draw();
private:
	int duration;
	char powerUpID;
	AnimSprite*	sprite;
};