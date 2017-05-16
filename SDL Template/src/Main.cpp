#include "SDLInit.h"
#include <chrono>
#include <windows.h>
#include "CollisionMap.h"
#include "InputManager.h"
#include "GSManager.h"
#include "GameStates.h"
#include "MainMenu.h"
#include "GameServer.h"
#include "Player.h"

#define WINDOWHEIGHT 1280 //Configure values for screen size here
#define WINDOWWIDTH 720

void GameLoop(SDL_Renderer* renderer);
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
		/*if (!SetupRenderer(window, renderer, WINDOWHEIGHT, WINDOWWIDTH)) {
			CloseSDL(window, renderer);
			return -3;
		}*/

		window = SDL_CreateWindow("Holiday Hell", 20, 12, WINDOWHEIGHT, WINDOWWIDTH, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		GameLoop(renderer);
		CloseSDL(window, renderer);
	}
	else {
		ServerLoop();
		CloseSDL(NULL, NULL);
	}

	system("pause");
	return 0;
}

//Game Loop
void GameLoop(SDL_Renderer* renderer)
{
	InputManager* input = new InputManager();
	GameStateManager* gsManager = new GameStateManager();

	gsManager->AddState(new MainMenu(renderer, input, gsManager));

	while (!input->WasKeyPressed(SDL_SCANCODE_ESCAPE) && !gsManager->CheckStateExit())
	{
		SDL_PumpEvents();

		SDL_RenderClear(renderer);

		input->UpdateKeyboard();
		gsManager->UpdateState();
		gsManager->DrawStates();

		SDL_RenderPresent(renderer);
	}
	delete gsManager;
	delete input;
}

//Server Loop
void ServerLoop()
{
	bool quit = false;
	SDL_Event e;

	int maxPlayers = 0;
	int port = 0;

	std::cout << "Enter port to use: ";
	std::cin >> port;

	std::cout << "Enter max player count: ";
	std::cin >> maxPlayers;

	GameServer* server = new GameServer(port, maxPlayers);
	InputManager* serverInput = new InputManager();
	SDL_Window* serverWin = NULL;
	serverWin = SDL_CreateWindow("Holiday Hell Server", 30, 30, 300, 1, SDL_WINDOW_SHOWN);

	server->Init();

	std::cout << "Server running, press escape to quit\n";

	while (!quit) { // this is the main game loop

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		SDL_PumpEvents();
		serverInput->UpdateKeyboard();
		if (serverInput->IsKeyDown(SDL_SCANCODE_ESCAPE)) { quit = true; }

		server->Update();

		Sleep(10);
	}

	SDL_DestroyWindow(serverWin);
	system("pause");

	delete serverInput;
	delete server;
}