#include "Header.h"
#include "TileMap.h"


void TileMap::initTextures()
{
	if (!this->textures["grass"].loadFromFile("resources/images/textures/tiles/grass.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_GRASS_TEXTURE";
	}
}

void TileMap::initMap()
{
	this->gridSizeU = 50;
	this->maxSize = v2u(80, 80);
	this->layers = 5; 
	this->center = v2f((this->maxSize.x / 2 - this->maxSize.y / 2)*this->tileSize.x, this->maxSize.x / 2 + this->maxSize.y / 2)* this->tileSize.y;
	this->playerCoords = v2f(0,0);
	int** map = Generation::map(maxSize.x+1,maxSize.y+1,this->layers, 8);
	for (size_t x = 0; x < this->maxSize.x; x++) {

		this->map.push_back(vector<vector<Tile>>());

		for (size_t y = 0; y < this->maxSize.y; y++) {

			this->map[x].push_back(vector<Tile>());

			for (size_t z = 0; z <= map[x][y]; z++) {

				this->map[x][y].push_back(Tile(this->textures["grass"],v3i(x,y,z),v2f(960.f,560.f-((float)this->maxSize.y)*15.f)));

			}
		}
	}
	delete map;
}

v2i TileMap::mapCoords(const v2f& coords)
{
	v2i res(static_cast<int>(floor(coords.x / this->tileSize.x)), static_cast<int>(floor(coords.x / this->tileSize.x)));
	return res;
}

bool TileMap::checkOverlay(int x, int y, int z)
{
	x++;
	y++;
	z+=2;
	while (x < this->map.size() && y < this->map[x].size()) {

		if (this->map[x][y].size() > z) return true;

		x++;
		y++;
		z+=2;
	}
	return false;
}

bool TileMap::checkRight(int x, int y, int z)
{
	if (this->map.size() > x + 1)
		return this->map[x + 1][y].size() <= z;
	return true;
}

bool TileMap::checkLeft(int x, int y, int z)
{
	if (this->map[x].size() > y + 1)
		return this->map[x][y + 1].size() <= z;
	return true;
}

bool TileMap::checkTop(int x, int y, int z)
{
	return this->map[x][y].size() == z+1;
}

TileMap::TileMap()
{
	this->initTextures();
	this->initMap();
}

TileMap::~TileMap()
{
}

void TileMap::update(const float& dt, v2f movement)
{
	this->playerCoords += movement;
	v2i c = mapCoords(this->playerCoords);
	cout << c.x << " " << c.y << "\n";
	//size_t x = trunc((this->playerCoords.x / this->tileSize.x));
	//movement.y += map[x][y].size() * tileSize.y;
	for (auto& itx : this->map) {
		for (auto& ity : itx) {
			for (auto& itz : ity) {
				itz.update(dt, movement);
			}
		}
	}
}

void TileMap::render(RenderTarget& target)
{
	for (int x = 0; x < this->map.size(); x++) {
		for (int y = 0; y < this->map[x].size(); y++ ) {
			for (int z = 0; z < this->map[x][y].size(); z++) {
				//if (!checkOverlay(x, y, z))
				this->map[x][y][z].render(target,checkTop(x,y,z),checkLeft(x,y,z),checkRight(x,y,z));
			}
		}
	}
}
