#include "SDLInit.h"
#include "CollisionMap.h"
#include <chrono>

#define WINDOWHEIGHT 1280 //Configure values for screen size here
#define WINDOWWIDTH 720

void GameLoop();
void ServerLoop();

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

	char choice = ' ';

	while (choice != '1' && choice != '2') {
		std::cout << "Welcome to Holiday Hell! Please choose an option,\n1. Start Game\n2. Start Server\n";
		std::cin >> choice;
	}

	if (choice == '1') {
		if (!SetupRenderer(window, renderer, WINDOWHEIGHT, WINDOWWIDTH)) {
			CloseSDL(window, renderer);
			return -3;
		}

		GameLoop();
	}
	else {
		ServerLoop();
		CloseSDL(NULL, NULL);
	}

	system("pause");
	return 0;
}

//Game Loop
void GameLoop()
{

}

//Server Loop
void ServerLoop()
{

}