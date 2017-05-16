#pragma once
#include "AnimSprite.h"

class TextSprite
{
public:
	TextSprite(SDL_Renderer* rendererInput, AnimSprite* textSprite, int x, int y);
	~TextSprite();

	void Draw(); //Draw out the whole message at once
	void Type(); //Type out the message one letter at a time (Must be ran as part of update loop)
	void ConfigureType(int _typeDelay, Mix_Chunk* typeSound); //Set the sound for typing and configures the delay
	void SetText(char* text); //Set the message to be typed out

	bool IsDone(); //Returns if the message has been completed (Only applies to typing mode)

private:
	AnimSprite* textData = NULL;
	char* message = NULL;
	int messageLength = 0;
	Mix_Chunk* sound = NULL;

	int xPos, yPos, charWidth, charHeight, typeDelay, typeCount, typeTimer, paragraph, lineReset;

	void DrawMessage(int msgLength); //For decoding the message in varying lengths and drawing it
};