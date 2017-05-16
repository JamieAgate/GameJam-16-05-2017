#pragma once
#include "SDLInit.h"
#include <LodePNG.h>
#include <vector>

class CollisionMap
{
public:
	CollisionMap(char* _filePath, int _w, int _h);
	~CollisionMap();

	void LoadMap(char* _filePath, int _w, int _h);
	std::vector<int> GetMapData() { return mapData; }

private:

	std::vector<int> mapData;
};