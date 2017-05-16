#pragma once
#include "SDLInit.h"

class Sprite
{
public:
	Sprite(SDL_Renderer* _renderer, char* _fileName, int _x, int _y, int _w, int _h);
	~Sprite();

	virtual void Draw(); //Draw sprite with previous parameters
	virtual void Draw(int _x, int _y); //Draw sprite at set position
	virtual void Draw(int _x, int _y, SDL_RendererFlip _flip); //Draw sprite at set position with a flip
	virtual void Draw(int _x, int _y, int _angle, SDL_RendererFlip _flip); //Draw with position, flip and rotation

	void SetSize(int _w, int _h); //Set the sprite size

	//Data Retrieval Commands
	SDL_Rect& GetRect() { return posRect; } //Returns positional rectangle of the sprite
	
	//Position and size values
	int GetX() { return posRect.x; }
	int GetY() { return posRect.y; }
	int GetW() { return posRect.w; }
	int GetH() { return posRect.h; }

protected:
	SDL_Renderer* renderer;
	SDL_Texture* tex;
	SDL_Rect posRect;

	SDL_RendererFlip flip; //flip variable

	int angle; //Angle of rotation

	bool isValid; //Control variable that prevents memory access violations
};