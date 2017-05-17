#include "Player.h"

Player::Player(InputManager* _input, SDL_Renderer* _renderer, int _playerID, bool _isRemote)
{
	this->input = _input;
	renderer = _renderer;

	playerID = _playerID;
	isRemote = _isRemote;

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
	if (!isRemote) {
		UpdateXMovement();
		UpdateYMovement();
		UpdateRotation();
	}
}

void Player::Draw()
{
	playerSprite->Draw(angle);
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
	while(i < 10)
	{
		if (dKeyPressed)
		{
			moveX -= i;
		}
		if (aKeyPressed)
		{
			moveX += i;
		}
		if (!CheckCollision(playerSprite->GetY(), moveX))
		{
			i = 11;
		}
		i++;
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
	while (i < 10)
	{
		if (wKeyPressed)
		{
			moveY += i;
		}
		if (sKeyPressed)
		{
			moveY -= i;
		}
		if (!CheckCollision(moveY, playerSprite->GetX()))
		{
			i = 11;
		}
		i++;
	}
	playerSprite->SetY(moveY);
}

void Player::UpdateRotation()
{
	bool mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	glm::vec2 mouseVec(mouseX +mouseWorldX, mouseY + mouseWorldY);
	glm::vec2 playerCenter(playerSprite->GetX() + 40, playerSprite->GetY() + 40);
	angle = glm::degrees(acos(glm::dot(glm::normalize(mouseVec - playerCenter), glm::vec2(1, 0)))) - 90;

	if ((playerSprite->GetY() + 40) < mouseY + mouseWorldY)
	{
		angle = 180 - angle;
	}
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

//NETWORK FUNCTIONS

std::string Player::CreateNetString()
{
	std::stringstream ss;

	ss << "[" << " "
		<< playerID << " "
		<< GetPlayerX() << " " << GetPlayerY() << " " << GetPlayerAng() << " "
		<< "]";

	return ss.str();
}

void Player::NetworkUpdate(int _x, int _y, float _angle)
{
	playerSprite->SetX(_x);
	playerSprite->SetY(_y);
	angle = _angle;
}