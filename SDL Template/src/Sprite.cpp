#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, char* _fileName, int _x, int _y, int _w, int _h)
{
	//Initialise all pointers as NULL to prevent errors
	renderer = NULL;
	tex = NULL;

	//Setup the SDL Rect
	posRect.x = _x;
	posRect.y = _y;
	posRect.h = _h;
	posRect.w = _w;

	flip = SDL_FLIP_NONE; //Set flipping to none by default
	angle = 0; //Set rotation to none by default

	renderer = _renderer; //Assign parameters into values
	tex = IMG_LoadTexture(renderer, _fileName);

	if (renderer == NULL || tex == NULL) {
		std::cout << "Sprite failed to load: " << IMG_GetError() << "\n";
		isValid = false; //Renderer or filepath was invalid, sprite is now invalidated
		return;
	}

	isValid = true; //All checks came back fine, sprite is now safe to use
}

Sprite::~Sprite()
{
	if (tex != NULL) { SDL_DestroyTexture(tex); }
}

//Draw Functions
void Sprite::Draw()
{
	if (isValid) { //Check if sprite is valid before drawing
		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, angle, NULL, flip);
	}
}

void Sprite::Draw(int _x, int _y)
{
	if (isValid) { //Check if sprite is valid before drawing
		posRect.x = _x; //Update Position
		posRect.y = _y;

		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, angle, NULL, flip);
	}
}

void Sprite::Draw(int _x, int _y, SDL_RendererFlip _flip)
{
	if (isValid) { //Check if sprite is valid before drawing
		posRect.x = _x; //Update Position and flip parameter
		posRect.y = _y;
		flip = _flip;

		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, angle, NULL, flip);
	}
}

void Sprite::Draw(int _x, int _y, int _angle, SDL_RendererFlip _flip)
{
	if (isValid) { //Check if sprite is valid before drawing
		posRect.x = _x; //Update Position and flip parameter
		posRect.y = _y;
		flip = _flip;
		angle = _angle;

		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, angle, NULL, flip);
	}
}

void Sprite::SetSize(int _w, int _h)
{
	posRect.w = _w;
	posRect.h = _h;
}