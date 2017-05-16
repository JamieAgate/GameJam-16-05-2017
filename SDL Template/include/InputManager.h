#pragma once
#include "SDLInit.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void UpdateKeyboard();

	bool WasKeyPressed(SDL_Scancode _key);
	bool IsKeyDown(SDL_Scancode _key);
	bool WasKeyReleased(SDL_Scancode _key);

private:
	int numKeys;
	Uint8* currentKeys;
	Uint8* prevFrameKeys;
};