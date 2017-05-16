#include "TextSprite.h"

TextSprite::TextSprite(SDL_Renderer* rendererInput, AnimSprite* textSprite, int x, int y)
{
	textData = textSprite;
	xPos = x;
	yPos = y;

	typeDelay = 5; //Default delay
}

TextSprite::~TextSprite()
{

}

void TextSprite::Draw()
{
	//Update character height and width incase the sprite has been resized
	charWidth = textData->GetW();
	charHeight = textData->GetH();

	//DRAW OUT WHOLE MESSAGE IN ONE
	//Chars are converted to ints according to ASCII, see here for more info: http://www.asciitable.com/

	DrawMessage(messageLength);
}

void TextSprite::SetText(char* text)
{
	message = text;
	messageLength = strlen(message); //Gets the message length
	typeCount = 0; //Resets the typing counter
	typeTimer = 0;
}

void TextSprite::Type()
{
	//Update character height and width incase the sprite has been resized
	charWidth = textData->GetW();
	charHeight = textData->GetH();

	typeTimer++;

	if (typeTimer % typeDelay == 0 && typeCount < messageLength) {
		typeCount++;

		if (sound != NULL && message[typeCount - 1] != 32) { //Play sound as new character is displayed (Provided it isn't a space)

			//Since the mixer keeps dropping sound data if you play sounds too fast, a delay has been implemented for fast text
			if (typeDelay >= 30) { //If the sound delay is greater than 30, play on each character
				Mix_PlayChannel(-1, sound, 0);
			}
			else if (typeCount % (30 / typeDelay) == 0) { //Play sounds at a delayed pace, increasing as the delay gets smaller
				Mix_PlayChannel(-1, sound, 0);
			}
		}
	}

	DrawMessage(typeCount); //Write out message
}

void TextSprite::ConfigureType(int _typeDelay, Mix_Chunk* typeSound)
{
	if (typeSound != NULL) {
		sound = typeSound;
	}

	typeDelay = _typeDelay;
}

void TextSprite::DrawMessage(int msgLength)
{
	paragraph = 0; //Reset paragraph to 0
	lineReset = 0; //Variable used to return the drawing position to the start upon new paragraph

	for (int i = 0; i < msgLength; i++) {
		if (message[i] > 64 && message[i] < 91) { //CAPITAL LETTERS
			textData->SetFrames(message[i] - 65, 0);
		}
		else if (message[i] > 96 && message[i] < 123) { //LOWER CASE LETTERS
			textData->SetFrames(message[i] - 97, 1);
		}
		else if (message[i] > 38 && message[i] < 59) { //PUNCTUATION AND NUMBERS
			textData->SetFrames(message[i] - 39, 2);
		}
		else if (message[i] == 126) { //PARAGRAPHS (Paragraphs are added using ~)
			textData->SetFrames(0, 3);
			paragraph++;
			lineReset = i + 1;
		}
		else { textData->SetFrames(0, 3); } //SPACES (Also any invalid characters will register as spaces)

		textData->Draw(xPos + ((i - lineReset) * charWidth), yPos + (paragraph * charHeight));
	}
}

bool TextSprite::IsDone()
{
	if (typeCount == messageLength) {
		return true;
	}
	
	return false;
}