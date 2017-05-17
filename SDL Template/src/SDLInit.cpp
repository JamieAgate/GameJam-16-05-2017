#include "SDLInit.h"

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL Has failed to initialise: " << SDL_GetError() << "\n";
		system("pause");
		return false;
	}

	return true;
}

bool InitExtensions()
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { //Load SDL_Image with PNG Support
		std::cout << "SDL Image failed to initialise: " << IMG_GetError() << "\n";
		system("pause");
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) { //Start the mixer
		std::cout << "SDL Mixer failed to initialise: " << Mix_GetError() << "\n";
		system("pause");
		return false;
	}

	Mix_Volume(-1, 64);

	if (SDLNet_Init() == -1) {
		std::cout << "SDLNet failed to initialise: " << SDLNet_GetError() << "\n";
		system("pause");
		return false;
	}

	return true;
}

bool SetupRenderer(SDL_Window* _window, SDL_Renderer* _renderer, int _width, int _height)
{
	_window = SDL_CreateWindow("Holiday Hell", 20, 12, _width, _height, SDL_WINDOW_SHOWN);

	if (_window == NULL) {
		std::cout << "Window failed to start: " << SDL_GetError() << "\n";
		system("pause");
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == NULL) {
		std::cout << "Renderer failed to start: " << SDL_GetError() << "\n";
		system("pause");
		return false;
	}

	return true;
}

void CloseSDL(SDL_Window* _window, SDL_Renderer* _renderer)
{
	if(_renderer != NULL) { SDL_DestroyRenderer(_renderer); } //Check if valid pointers
	if (_window != NULL) { SDL_DestroyWindow(_window); }

	SDLNet_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

