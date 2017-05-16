#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer, InputManager* _input, GameStateManager* manager) :
	GameState(manager, renderer)
{
	initSuccess = false;
	timer = 0;
	exit = false;
	input = _input;
	jumpToGameLoop = false;

	stateName = "Main Menu";

	if (!InitMenu())
	{
		exit = true;
	}
}

MainMenu::~MainMenu()
{
	if (initSuccess) {
		delete title1;
		delete title2;

		delete newGameButton;
		delete loadGameButton;
		delete optionsButton;
		delete exitButton;

		delete cursorSprite;
	}
}

bool MainMenu::InitMenu()
{
	title1 = new Sprite(renderer, "resources\\MainMenu\\title1.png", 2000, 0, 550, 200);
	title2 = new Sprite(renderer, "resources\\MainMenu\\title2.png", 2000, 0, 670, 200);

	newGameButton = new Sprite(renderer, "resources\\MainMenu\\newgame.png", 1000, 0, 420, 100);
	loadGameButton = new Sprite(renderer, "resources\\MainMenu\\Loadgame.png", 1000, 0, 440, 100);
	optionsButton = new Sprite(renderer, "resources\\MainMenu\\Options.png", 1000, 0, 305, 100);
	exitButton = new Sprite(renderer, "resources\\MainMenu\\Exit.png", 1000, 0, 400, 100);

	cursorSprite = new Sprite(renderer, "resources\\MainMenu\\cursor.png", 1000, 0, 50, 100); //CURSOR

	if (title1 == NULL || title2 == NULL)
	{
		std::cout << "Main Menu Failed to load!\n";
		delete title1;
		delete title2;
		return false;
	}
	initSuccess = true;
	return true;
}

void MainMenu::Update()
{
	if (timer < 150)
	{
		timer++;
		Intro();
	}
	else
	{
		Idle();
	}

	if (jumpToGameLoop)
	{
		std::cout << "Will Jump to game Loop\n";
	}
}

void MainMenu::Intro()
{
		if (timer < 60) { //TITLE APPEARS!
			title1->Draw(1280 - ((timer) * 15), 20);
		}
		else if (timer < 120) {
			title1->Draw(380, 20);
			title2->Draw(1280 - ((timer-60) * 16), 180);
		}
		else if (timer < 150) { //Buttons appear on screen
			newGameButton->Draw(200, 720 - ((timer - 120) * (370 / 30)));
			loadGameButton->Draw(650, 720 - ((timer - 120) * (370 / 30)));
			optionsButton->Draw(200, 720 - ((timer - 120) * (270 / 30)));
			exitButton->Draw(650, 720 - ((timer - 120) * (270 / 30)));
		}

		if (timer >= 120) {
			title1->Draw(380, 20);
			title2->Draw(320, 180);
		}

}

void MainMenu::MouseInput()
{
	mouseState = SDL_GetMouseState(&mouseX, &mouseY); //Get the current position of the cursor and button state

													  //SDL_PumpEvents();
	if ((mouseX > 200 && mouseX < 620) && (mouseY > 350 && mouseY < 450)) { //New Game Button
		cursorSprite->Draw(155 - abs((sin(timer * 0.04) * 15)), 350, SDL_FLIP_NONE);
		hover = 0;
		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) || input->IsKeyDown(SDL_SCANCODE_RETURN))
		{
			Mix_HaltMusic();

			jumpToGameLoop = true;
		}
	}
	else if ((mouseX > 200 && mouseX < 620) && (mouseY > 450 && mouseY < 550)) { //Options Button
		cursorSprite->Draw(155 - abs((sin(timer * 0.04) * 15)), 450, SDL_FLIP_NONE);
		hover = 2;
	}
	else if ((mouseX > 650 && mouseX < 1090) && (mouseY > 350 && mouseY < 450)) { //Load game button
		cursorSprite->Draw(1090 + abs((sin(timer * 0.04) * 15)), 350, SDL_FLIP_HORIZONTAL);
		hover = 3;
	}
	else if ((mouseX > 650 && mouseX < 1090) && (mouseY > 450 && mouseY < 550)) { //Exit game button
		cursorSprite->Draw(1090 + abs((sin(timer * 0.04) * 15)), 450, SDL_FLIP_HORIZONTAL);
		hover = 4;

		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) || input->IsKeyDown(SDL_SCANCODE_RETURN)) { //Check for Click
			exit = true;
		}
	}
	else {
		hover = 0;
		deltaHover = 0;
	}

	if (hover != deltaHover) {
		deltaHover = hover;
	}
}

void MainMenu::Idle()
{
	MouseInput();

	title1->Draw(380, 20);
	title2->Draw(320, 180);
	newGameButton->Draw(200, 350);
	loadGameButton->Draw(650, 350);
	optionsButton->Draw(200, 450);
	exitButton->Draw(650, 450);
}
