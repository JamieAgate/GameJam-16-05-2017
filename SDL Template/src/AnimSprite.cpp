#include "AnimSprite.h"

AnimSprite::AnimSprite(SDL_Renderer* _renderer, char* _fileName, int _x, int _y, int _w, int _h) :
	Sprite(_renderer, _fileName, _x, _y, _w, _h)
{
	//Configure blit
	blit.x = 0;
	blit.y = 0;
	blit.w = _w;
	blit.h = _h;

	xFrame = 0; //Animsprite defaults to top left frame
	yFrame = 0; 
}

AnimSprite::~AnimSprite()
{

}

//Draw Functions
void AnimSprite::Draw()
{
	if (isValid) { //Check if sprite is valid before drawing
		UpdateBlit();
		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, -angle, NULL, flip);
	}
}

void AnimSprite::Draw(int _x, int _y)
{
	if (isValid) { //Check if sprite is valid before drawing
		UpdateBlit();
		posRect.x = _x; //Update Position
		posRect.y = _y;

		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, -angle, NULL, flip);
	}
}

void AnimSprite::Draw(int _x, int _y, SDL_RendererFlip _flip)
{
	if (isValid) { //Check if sprite is valid before drawing
		UpdateBlit();
		posRect.x = _x; //Update Position and flip parameter
		posRect.y = _y;
		flip = _flip;

		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, -angle, NULL, flip);
	}
}

void AnimSprite::Draw(int _x, int _y, int _angle, SDL_RendererFlip _flip)
{
	if (isValid) { //Check if sprite is valid before drawing
		UpdateBlit();
		posRect.x = _x; //Update Position and flip parameter
		posRect.y = _y;
		flip = _flip;
		angle = _angle;

		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, -angle, NULL, flip);
	}
}

void AnimSprite::Draw(float _angle)
{
	if (isValid) { //Check if sprite is valid before drawing
		UpdateBlit();
		angle = _angle;

		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, -angle, NULL, flip);
	}
}

void AnimSprite::SetFrames(int _xFrame, int _yFrame)
{
	xFrame = _xFrame;
	yFrame = _yFrame;
}

void AnimSprite::UpdateBlit()
{
	blit.x = xFrame * blit.w; //Using blit width to ensure propper blitting while
	blit.y = yFrame * blit.h; //Still allowing scaling
}