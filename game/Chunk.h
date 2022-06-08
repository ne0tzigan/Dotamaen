#ifndef CHUNK_H
#define CHUNK_H

#include "Tile.h"
#include "Generation.h"

class Chunk
{
private:
	vector<vector<vector<Tile>>> map;
	std::map<str, Texture> textures;
	v2u maxSize;
	v2f tileSize;
	v2i playerCoords;
	IntRect renderingRange;
	unsigned layers;
	void initTextures();
	void initMap();
	bool checkOverlay(int x, int y, int z),
		checkTop(int x, int y, int z),
		checkLeft(int x, int y, int z),
		checkRight(int x, int y, int z);
public:
	Chunk();
	~Chunk();

	void update(const float& dt, v2f movement, v2i& playerCoords);
	void render(RenderTarget& target);
};

#endif