#include "Header.h"
#include "Chunk.h"

void Chunk::initTextures()
{
}

void Chunk::initMap()
{
	this->maxSize = v2u(64, 64);
	this->layers = 5;
	this->playerCoords = v2i(this->maxSize.x / 2, this->maxSize.y / 2);
	int** map = Generation::map(maxSize.x + 1, maxSize.y + 1, this->layers, 8);
	for (size_t x = 0; x < this->maxSize.x; x++) {

		this->map.push_back(vector<vector<Tile>>());

		for (size_t y = 0; y < this->maxSize.y; y++) {

			this->map[x].push_back(vector<Tile>());

			for (size_t z = 0; z <= map[x][y]; z++) {

				this->map[x][y].push_back(Tile(this->textures["grass"], v3i(x, y, z), v2f(960.f, 560.f - ((float)this->maxSize.y) * 15.f)));

			}
		}
	}
	delete map;
}

bool Chunk::checkOverlay(int x, int y, int z)
{
    return false;
}

bool Chunk::checkRight(int x, int y, int z)
{
    return false;
}

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::update(const float& dt, v2f movement, v2i& playerCoords)
{
}

void Chunk::render(RenderTarget& target)
{
}

bool Chunk::checkLeft(int x, int y, int z)
{
    return false;
}

bool Chunk::checkTop(int x, int y, int z)
{
    return false;
}
