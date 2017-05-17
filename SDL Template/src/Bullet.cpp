#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	sprite = new AnimSprite(renderer, "resources\\Projectile\\Bullet.png", 0, 0, 60, 60);
	isActive = false;
}

void Bullet::Setup(int _x, int _y, glm::vec2 _velocity)
{
	sprite->SetX(_x);
	sprite->SetY(_y);
	velocity = _velocity;
	isActive = true;
	canBeDestroyed = false;

	angle = glm::degrees(acos(glm::dot(glm::normalize(velocity), glm::vec2(1, 0)))) - 90;

	if (velocity.y + sprite->GetY() < sprite->GetY()) 
	{
		angle = 180 - angle;
	}
}

Bullet::~Bullet()
{
	delete sprite;
}

void Bullet::Update()
{
	sprite->SetX(sprite->GetX() + velocity.x);
	sprite->SetY(sprite->GetY() + velocity.y);
}

void Bullet::Draw()
{
	sprite->Draw(angle);
}