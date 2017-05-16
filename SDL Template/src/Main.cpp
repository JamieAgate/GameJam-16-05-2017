#include "SDLInit.h"
#include "CollisionMap.h"
#include <chrono>

#define WINDOWHEIGHT 1280 //Configure values for screen size here
#define WINDOWWIDTH 720

int main(int arc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	//Initialise Everything
	if (!InitSDL()) { return -1; }

	if (!InitExtensions()) {
		SDL_Quit();
		return -2;
	}

	if (!SetupRenderer(window, renderer, WINDOWHEIGHT, WINDOWWIDTH)) {
		CloseSDL(window, renderer);
		return -3;
	}

	system("pause");
	return 0;
}