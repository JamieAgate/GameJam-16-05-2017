#include "CollisionMap.h"

CollisionMap::CollisionMap(char* _filePath, int _w, int _h)
{
	LoadMap(_filePath, _w, _h);
}

CollisionMap::~CollisionMap()
{
	mapData.clear(); //Clear old map data
}

void CollisionMap::LoadMap(char* _filePath, int _w, int _h)
{
	//Clear old data out
	mapData.clear();

	//Load PNG
	unsigned int error;
	unsigned char* imageData = nullptr;
	unsigned int w = _w;
	unsigned int h = _h;

	error = lodepng_decode32_file(&imageData, &w, &h, _filePath);

	std::cout << error << "\n";

	Uint8 pixel = 0;
	// store each red pixel data in a Int vector
	for (int i = 0; i < w * h; i++) { 
		pixel = (int)imageData[(i * 4)];
		mapData.push_back(pixel);
	}
}