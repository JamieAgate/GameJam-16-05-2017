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

	death = false;
	timer = 0;
	speed = 10;
	bulletVelocity = 5;

	deathScreen = new Sprite(renderer, "resources\\DeathScreen\\DeathScreen.png", 0, 0, 1280, 720);
	cursorSprite = new Sprite(renderer, "resources\\MainMenu\\cursor.png", 540, 590, 50, 100);
	cursorX = 540;
	//Base properties
	health = 100;
	frags = 0;

	//LOAD LE HUD
	monofont = new AnimSprite(renderer, "resources\\monofonto.png", 0, 0, 47, 71);
	text = new TextSprite(renderer, monofont, 20, 20);
}

Player::~Player()
{
	delete bulletSprite;
	for (Bullet* b : bullets)
	{
		delete b;
	}
	delete playerSprite;
	delete deathScreen;
}

bool Player::InitPlayer()
{
	//PICK A RANDOM SPRITE
	playerSkin = rand() % 4;

	bulletSkins[0] = "resources\\projectile\\FloraProjectile.png";
	bulletSkins[1] = "resources\\projectile\\BunnyProjectile.png";
	bulletSkins[2] = "resources\\projectile\\PumpkinProjectile.png";
	bulletSkins[3] = "resources\\projectile\\SantaProjectile.png";


	for (int i = 0; i < 4; i++) { bulletSkinSprites[i] = new AnimSprite(renderer, bulletSkins[i], 0, 0, 10, 10); }

	playerSprite = new AnimSprite(renderer, "resources\\player\\players.png", 640, 360, 76, 76);
	playerSprite->SetFrames(0, playerSkin);

	bulletSprite = new AnimSprite(renderer, bulletSkins[playerSkin], 0, 0, 10, 10);

	if (playerSprite == NULL)
	{
		delete playerSprite;
		return false;
	}
	return true;
}

void Player::Update(std::vector<Player*> _otherPlayers)
{
	requestingBullet = false;

	if (!isRemote) {
		if (!death)
		{
			if (input->IsKeyDown(SDL_SCANCODE_M))
			{
				health -= 10;
			}
			UpdateXMovement();
			UpdateYMovement();
			UpdateRotation();
			UpdateAnim();
			CheckDeath();
		}
		else
		{
			DeathUpdate();
		}
			UpdateBullets(_otherPlayers);
	}
}

void Player::DeathUpdate()
{
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

	if ((mouseX > 640 && mouseX < 1280) && (mouseY > 560 && mouseY < 720)) { //New Game Button
		drawCursor = true;
		cursorX = 540 - abs((sin(timer * 0.04) * 15));
		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) || input->IsKeyDown(SDL_SCANCODE_RETURN))
		{
			bulletVelocity = 5;
			speed = 10;
			respawn = true;
		}
	}
	else
	{
		drawCursor = false;
	}
	timer++;
}

void Player::CheckDeath()
{
	if (health <= 0)
	{
		death = true;
		canShoot = false;
		int timer = 0;
	}
}

void Player::UpdateBullets(std::vector<Player*> _otherPlayers)
{
	// fill mouseX/Y in and work out if left mouse if pressed
	isFiring = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);

	// check if we should add a new bullet to the bullets vector
	if (isFiring && canShoot &&!death) {
		shotTimer = 0;
		canShoot = false;
		requestingBullet = true;

		glm::vec2 vel(sin((angle * M_PI / 180)) * -bulletVelocity, cos((angle * M_PI / 180)) * -bulletVelocity);
		int startX = playerSprite->GetX() + (playerSprite->GetW() / 2);
		int startY = playerSprite->GetY() + (playerSprite->GetH() / 2);

		bullets.push_back(new Bullet(renderer, bulletSprite));
		bullets.back()->Setup(startX, startY, vel, damage, playerID);
	}

	//Run timer for shot delay if can't shoot
	if (!canShoot) {
		shotTimer++;
		if (shotTimer >= shotDelay) {
			canShoot = true;
			shotTimer = 0;
		}
	}

	// update all of our bullets...
	for (int i = 0; i < bullets.size(); i++) {

		if (!bullets[i]->GetIsActive()) continue;

		bullets[i]->Update();
		if (CheckPixelData(bullets[i]->GetY(), bullets[i]->GetX(), bullets[i]->GetH(), bullets[i]->GetW()))
		{
			bullets[i]->SetCanBeDestroyed(true);
		}

		//CHECK FOR PLAYER COLLISION
		BulletData data = bullets[i]->GetBulletData(playerSkin);
		if (data.playerID != playerID) { //Check if you are being hit by other players
			if (SDL_HasIntersection(&playerSprite->GetRect(), &bullets[i]->GetRect()) && !death) {
				health -= data.damage;
				std::cout << "YOU GOT HIT! " << health << " health remaining!\n";

				if (health <= 0) { killerID = data.playerID; }

				bullets[i]->SetCanBeDestroyed(true);
			}
		}
		else {
			for (int i2 = 1; i2 < _otherPlayers.size(); i2++) {
				if (SDL_HasIntersection(&_otherPlayers[i2]->GetRect(), &bullets[i]->GetRect())) {
					bullets[i]->SetCanBeDestroyed(true);
				}
			}
		}
		

		//...check if any should be 'destroyed' (deleted and set to nullptr)
		if (bullets[i]->GetCanBeDestroyed())
		{
			delete bullets.at(i);
			bullets[i] = nullptr;
		}
	}
	bullets.erase(std::remove(bullets.begin(), bullets.end(), nullptr), bullets.end());


	
}

void Player::Draw(std::vector<Player*> _otherPlayers)
{
	for (Bullet* b : bullets)
	{
		if (b->GetIsActive())
		{
			b->Draw();
		}
	}
	if (!death)
	{
		playerSprite->Draw(angle);
	}
	else
	{
		int WorldDrawPosX = playerSprite->GetX() - 640;
		if (WorldDrawPosX > 1280)
		{
			WorldDrawPosX = 1280;
		}
		if (WorldDrawPosX < 0)
		{
			WorldDrawPosX = 0;
		}
		int WorldDrawPosY = playerSprite->GetY() - 360;
		if (WorldDrawPosY > 720)
		{
			WorldDrawPosY = 720;
		}
		if (WorldDrawPosY < 0)
		{
			WorldDrawPosY = 0;
		}
		deathScreen->Draw(WorldDrawPosX,WorldDrawPosY, SDL_FLIP_NONE);
		if (drawCursor)
		{
			cursorSprite->Draw(cursorX + WorldDrawPosX, 560 + WorldDrawPosY, SDL_FLIP_NONE);
		}
	}

	std::stringstream strs;
	strs << health;
	std::string temp_str = strs.str();
	char* char_type = (char*)temp_str.c_str();

	if (!isRemote) {
		monofont->SetSize(47, 71);
		text->SetText(char_type);
		text->SetPos(playerSprite->GetX() - 50, playerSprite->GetY() - 80);
		text->Draw();
	}

	//Display the score
	monofont->SetSize(23, 35);

	for (int i = 0; i < _otherPlayers.size(); i++) {
		std::stringstream strs;
		strs << "Player " << _otherPlayers[i]->GetID() << ": ";
		strs << _otherPlayers[i]->GetFrags();

		std::string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		text->SetPos(cameraPosX + (i * 300), cameraPosY);
		text->SetText(char_type);
		text->Draw();
	}
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

bool Player::CheckPixelData(int _yOffset, int _xOffset, int _H, int _W)
{
	for (int checkY = _yOffset; checkY < _yOffset + _H; checkY++)
	{
		for (int checkX = _xOffset; checkX < _xOffset + _W; checkX++)
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
		<< "]" <<  " ";

	return ss.str();
}

void Player::NetworkUpdate(int _x, int _y, float _angle)
{
	playerSprite->SetX(_x);
	playerSprite->SetY(_y);
	angle = _angle;

	UpdateAnim();
}

std::string Player::CreateProjectilePacket()
{
	std::stringstream ss;
	BulletData data;

	//Convert projectile data into a string
	data = bullets.back()->GetBulletData(playerSkin);

	ss << "<" << " " << data.x << " " << data.y << " " << data.xVel << " " << data.yVel << " " <<
		data.damage << " " << data.playerID << " " << data.skin << " " <<
		">" << " ";

	return ss.str();
}

void Player::CreateNetBullet(float _x, float _y, float _xVel, float _yVel, int _damage, int _playerID, int _skin, std::vector<Player*> _playerData)
{
	bullets.push_back(new Bullet(renderer, bulletSkinSprites[_skin]));
	bullets.back()->Setup(_x, _y, glm::vec2(_xVel, _yVel), _damage, _playerID);

	for (Player* p : _playerData) {
		if (p->GetID() == _playerID && p->GetSkin() != _skin) {
			p->SetSkin(_skin);
		}
	}
}


bool Player::CheckRespawn()
{
	if (respawn == true) {
		health = 100;
		respawn = false;
		return true;
	}

	return false;
}

void Player::UpdateAnim()
{
	frameTimer++;

	if (frameTimer % frameDelay == 0) frameTick++;

	playerSprite->SetFrames(frameTick % 8, playerSkin);
}