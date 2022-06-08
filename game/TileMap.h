#ifndef TILEMAP_H
#define TILEMAP_H

#include "Chunk.h"

class TileMap
{
private:
	vector<vector<vector<Tile>>> map;
	vector<Chunk> chunks;
	std::map<str, Texture> textures;
	v2u maxSize;
	v2f tileSize;
	v2f center;
	v2f playerCoords;
	IntRect renderingRange;
	unsigned layers;
	unsigned gridSizeU;
	void initTextures();
	void initMap();
	v2i mapCoords(const v2f& coords);
	bool checkOverlay(int x, int y, int z), 
				checkTop(int x, int y, int z), 
				checkLeft(int x, int y, int z), 
				checkRight(int x, int y, int z);
public:
	TileMap();
	~TileMap();

	void update(const float& dt, v2f movement);
	void render(RenderTarget& target);
};

#endif