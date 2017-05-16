#include "SoundManager.h"

SoundManager::SoundManager(int _soundCount)
{
	soundCount = _soundCount;
	sounds = NULL;
	bgm = NULL;

	sounds = new Mix_Chunk[soundCount]{ NULL };
	hasBGM = false;
}

SoundManager::SoundManager(int _soundCount, char* _bgmFile)
{
	soundCount = _soundCount;
	sounds = NULL;
	bgm = NULL;

	sounds = new Mix_Chunk[soundCount]{ NULL };
	bgm = Mix_LoadMUS(_bgmFile);

	hasBGM = (bgm != NULL);
}

SoundManager::~SoundManager()
{
	if (hasBGM) { Mix_FreeMusic(bgm); }

	for (int i = 0; i < soundCount; i++) {
		if (&sounds[i] != NULL) { Mix_FreeChunk(&sounds[i]); }
		delete &sounds[i];
	}
}

void SoundManager::LoadSound(int _soundID, char* _filePath)
{
	if (_soundID >= soundCount || _soundID < 0) {
		std::cout << "Invalid soundID \n";
		return;
	}

	if (&sounds[_soundID] != NULL) { Mix_FreeChunk(&sounds[_soundID]); }
	sounds[_soundID] = *Mix_LoadWAV(_filePath);
}

void SoundManager::LoadBGM(char* _filePath)
{
	if (hasBGM) { Mix_FreeMusic(bgm); }
	bgm = Mix_LoadMUS(_filePath);

	hasBGM = (bgm != NULL);
}

void SoundManager::PlaySound(int _soundID)
{
	if (_soundID >= soundCount || _soundID < 0) {
		std::cout << "Invalid soundID \n";
		return;
	}

	if (&sounds[_soundID] == NULL) {
		std::cout << "Sound not loaded\n";
		return;
	}

	Mix_PlayChannel(-1, &sounds[_soundID], 0);
}

void SoundManager::PlayBGM(int _loops)
{
	if (hasBGM) { Mix_PlayMusic(bgm, _loops); }
}