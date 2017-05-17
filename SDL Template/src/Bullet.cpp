#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* _renderer, AnimSprite* BulletSprite)
{
	renderer = _renderer;
	sprite = BulletSprite;
	isActive = false;
}

void Bullet::Setup(int _x, int _y, glm::vec2 _velocity)
{
	sprite->SetX(_x);
	sprite->SetY(_y);
	velocity = _velocity;
	isActive = true;
	canBeDestroyed = false;

	angle = glm::degrees(acos(glm::dot(glm::normalize(velocity), glm::vec2(1, 0))));

	if (velocity.y + sprite->GetY() < sprite->GetY()) 
	{
		angle = 360 - angle;
	}
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	sprite->SetX(sprite->GetX() + velocity.x);
	sprite->SetY(sprite->GetY() + velocity.y);
	if (sprite->GetX() <= 0 || sprite->GetX() >= 2560 || sprite->GetY() <= 0 || sprite->GetY() >= 1440)
	{
		canBeDestroyed = true;
		if (sprite->GetX() <= 0)
		{
			sprite->SetX(0);
		}
		if (sprite->GetX() >= 2560)
		{
			sprite->SetX(2560);
		}
		if (sprite->GetY() <= 0)
		{
			sprite->SetY(0);
		}
		if (sprite->GetY() >= 1440)
		{
			sprite->SetY(1440);
		}
	}
}

void Bullet::Draw()
{
	sprite->Draw(angle);
}