#include "InputManager.h"

InputManager::InputManager()
{
	const Uint8* keys = SDL_GetKeyboardState(&numKeys);

	currentKeys = new Uint8[numKeys];
	prevFrameKeys = new Uint8[numKeys];
}

InputManager::~InputManager()
{
	delete[] currentKeys;
	delete[] prevFrameKeys;
}

void InputManager::UpdateKeyboard()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	std::memcpy(prevFrameKeys, currentKeys, numKeys);
	std::memcpy(currentKeys, keys, numKeys);
}

bool InputManager::WasKeyPressed(SDL_Scancode _key)
{
	if (currentKeys[_key] && !prevFrameKeys[_key]) { return true; }
	else { return false; }
}

bool InputManager::IsKeyDown(SDL_Scancode _key)
{
	if (currentKeys[_key] && prevFrameKeys[_key]) { return true; }
	else { return false; }
}

bool InputManager::WasKeyReleased(SDL_Scancode _key)
{
	if (!currentKeys[_key] && prevFrameKeys[_key]) { return true; }
	else { return false; }
}