#pragma once
#include "Sprite.h"
#include "GameStates.h"
#include "GSManager.h"
#include "InputManager.h"

class MainMenu : public GameState
{
public:
	MainMenu(SDL_Renderer* renderer, InputManager* _input, GameStateManager* manager);
	~MainMenu() override;

	bool InitMenu();

	void Update() override;
private:
	bool initSuccess;
	int timer;
	
	InputManager* input;

	void Intro();
	void Idle();

	bool jumpToGameLoop;

	void MouseInput();
	int mouseX = 0;
	int mouseY = 0;
	int hover = 0;
	int deltaHover = 0;
	Uint32 mouseState;

	Sprite* title1 = NULL;
	Sprite* title2 = NULL;

	Sprite* newGameButton = NULL;
	Sprite* loadGameButton = NULL;
	Sprite* optionsButton = NULL;
	Sprite* exitButton = NULL;

	Sprite* cursorSprite = NULL;
};