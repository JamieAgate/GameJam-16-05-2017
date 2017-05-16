#pragma once
#include "SDLInit.h"

class SoundManager
{
public:
	SoundManager(int _soundCount);
	SoundManager(int _soundCount, char* _bgmFile);
	~SoundManager();

	//Load file commands
	void LoadSound(int _soundID, char* _filePath);
	void LoadBGM(char* _filePath);

	void PlaySound(int _soundID);
	void PlayBGM(int _loops); //Play music with loops specified (-1 means infinite loop)

private:
	int soundCount;
	bool hasBGM;

	Mix_Chunk* sounds;
	Mix_Music* bgm;
};