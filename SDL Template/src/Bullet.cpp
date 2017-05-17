#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* _renderer, AnimSprite* BulletSprite)
{
	renderer = _renderer;
	sprite = BulletSprite;
	isActive = false;
}

void Bullet::Setup(int _x, int _y, glm::vec2 _velocity, int _damage, int _playerID)
{
	sprite->SetX(_x);
	sprite->SetY(_y);
	velocity = _velocity;
	isActive = true;
	canBeDestroyed = false;

	damage = _damage;
	playerID = _playerID;

	xPos = _x;
	yPos = _y;

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
	sprite->SetX(xPos += velocity.x);
	sprite->SetY(yPos += velocity.y);
	if (sprite->GetX() <= 0 || sprite->GetX() >= 2560 || sprite->GetY() <= 0 || sprite->GetY() >= 1440)
	{
		canBeDestroyed = true;
		if (xPos <= 0)
		{
			sprite->SetX(0);
		}
		if (xPos >= 2560)
		{
			sprite->SetX(2560);
		}
		if (yPos <= 0)
		{
			sprite->SetY(0);
		}
		if (yPos >= 1440)
		{
			sprite->SetY(1440);
		}
	}
}

void Bullet::Draw()
{
	sprite->Draw(xPos, yPos, angle);
}

BulletData Bullet::GetBulletData()
{
	BulletData data;

	data.x = xPos;
	data.y = yPos;
	data.xVel = velocity.x;
	data.yVel = velocity.y;

	data.playerID = playerID;
	data.damage = damage;

	return data;
}