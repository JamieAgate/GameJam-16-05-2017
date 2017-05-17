#pragma once
#include "Sprite.h"

//Enhanced version of sprite designed for spritesheets (Animation Sprite)

class AnimSprite : public Sprite
{
public:
	AnimSprite(SDL_Renderer* _renderer, char* _fileName, int _x, int _y, int _w, int _h);
	~AnimSprite();

	void Draw(); //Draw sprite with previous parameters
	void Draw(int _x, int _y); //Draw sprite at set position
	void Draw(int _x, int _y, SDL_RendererFlip _flip); //Draw sprite at set position with a flip
	void Draw(int _x, int _y, int _angle, SDL_RendererFlip _flip);//Draw with position, flip and rotation
	void Draw(float _angle);
	void Draw(int _x, int _y, float _angle); 

	void SetFrames(int _xFrame, int _yFrame);

private:
	int xFrame, yFrame; //Current frames
	int xMaxFrame, yMaxFrame; //Frame caps

	void UpdateBlit(); //Updates the blit to current frames, in case a sprite is shared among objects

	SDL_Rect blit; //SDL Rect for blitting
};