#pragma once
#include<string>

class Map {
public:
	Map(std::string tID,int ms, int ts);
	~Map();

	void AddTile(int srcX, int srcY, int x, int y);
	void LoadMap(std::string path, int sizeX, int sizeY);

	

private:
	std::string texID;
//	const char* mapFilePath;
	int mapScale, tileSize;
	int scaledSize;
};