#ifndef TILE_H
#define TILE_H

#include "Define.h"

class Tile
{
private:
	float width = 40.f;
	float length = 15.f;
	float height = 15.f;
	Sprite topSprite;
	Sprite leftSprite;
	Sprite rightSprite;
	v2f countPos(v3i);
public:
	Tile(Texture& texturesheet, v3i pos, v2f startPos=v2f(0.f,0.f));
	~Tile();

	void update(const float& dt, v2f movement);
	void render(RenderTarget& target, const bool topVisible = true, const bool leftVisible = true, const bool rightVisible = true);
};

#endif