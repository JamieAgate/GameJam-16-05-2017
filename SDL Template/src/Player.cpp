#include "Player.h"

Player::Player(InputManager* _input, SDL_Renderer* _renderer)
{
	this->input = _input;
	renderer = _renderer;

	playerID = 0;

	InitPlayer();

	moveX = playerSprite->GetX();
	moveY = playerSprite->GetY();

	speed = 10;
}

Player::~Player()
{

}

bool Player::InitPlayer()
{
	playerSprite = new AnimSprite(renderer, "resources\\Player\\Player.png", 640, 360, 80, 80);

	if (playerSprite == NULL)
	{
		delete playerSprite;
		return false;
	}
	return true;
}

void Player::Update()
{
	UpdateXMovement();
	UpdateYMovement();
}

void Player::Draw()
{
	playerSprite->Draw();
}

void Player::UpdateXMovement()
{
	bool dKeyPressed = input->IsKeyDown(SDL_SCANCODE_D);
	bool aKeyPressed = input->IsKeyDown(SDL_SCANCODE_A);

	if (dKeyPressed)
	{
		moveX += speed;
	}
	if (aKeyPressed)
	{
		moveX -= speed;
	}
	int i = 0;
	while(i < 11)
	{
		if (dKeyPressed)
		{
			moveX -= i;
		}
		if (aKeyPressed)
		{
			moveX += i;
		}
		if (CheckCollision(playerSprite->GetY(), moveX))
		{
			i = 11;
		}
	}
	playerSprite->SetX(moveX);
}

void Player::UpdateYMovement()
{
	bool wKeyPressed = input->IsKeyDown(SDL_SCANCODE_W);
	bool sKeyPressed = input->IsKeyDown(SDL_SCANCODE_S);

	if (wKeyPressed)
	{
		moveY -= speed;
	}
	if (sKeyPressed)
	{
		moveY += speed;
	}
	int i = 0;
	while (i < 11)
	{
		if (wKeyPressed)
		{
			moveY += i;
		}
		if (sKeyPressed)
		{
			moveY -= i;
		}
		if (CheckCollision(moveY, playerSprite->GetX()))
		{
			i = 11;
		}
	}
	playerSprite->SetY(moveY);
}

bool Player::CheckCollision(int _yOffset, int _xOffset)
{
	
	if (!CheckPixelData(_yOffset, _xOffset)){
			return false;
		}
	return true;
}

bool Player::CheckPixelData(int _yOffset, int _xOffset)
{
	for (int checkY = _yOffset; checkY < _yOffset + playerSprite->GetH(); checkY++)
	{
		for (int checkX = _xOffset; checkX < _xOffset + playerSprite->GetW(); checkX++)
		{
			checkPixel = (checkY * 2560) + checkX;
			col = mapData[checkPixel];

			if (col == 255) {
				return true;
			}
		}
	}
	return false;
}