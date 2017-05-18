#include "PowerUps.h"

PowerUp::PowerUp(AnimSprite* _PowerUp, int _name, glm::vec2 spawn)
{
	sprite = _PowerUp;
	powerUpID = _name;
	sprite->SetX(spawn.x);
	sprite->SetY(spawn.y);
}

PowerUp::~PowerUp()
{

}

void PowerUp::Update()
{

}

void PowerUp::Draw()
{
	sprite->Draw();
}