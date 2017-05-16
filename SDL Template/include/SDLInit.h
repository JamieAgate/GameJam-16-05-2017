#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#include <iostream>

//SDL Initialization functions

bool InitSDL(); //Initalise all of base SDL2
bool InitExtensions(); //Initialise Image, Mixer and Net extensions
bool SetupRenderer(SDL_Window* _window, SDL_Renderer* _renderer, int _width, int _height); //Start an SDL Window and Renderer
void CloseSDL(SDL_Window* _window, SDL_Renderer* _renderer); //Destroy the given window and renderer and close SDL and it's extentions*

// * NULL pointers are also valid input in the case that the window and/or renderer didn't create correctly