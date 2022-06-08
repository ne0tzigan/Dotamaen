#include "Header.h"
#include "Tile.h"

v2f Tile::countPos(v3i pos)
{
	float x = static_cast<float>(pos.x - pos.y)+0.5f;
	float y = static_cast<float>(pos.x + pos.y)+0.5f;
	return v2f(
		x*this->width,
		y*this->length - pos.z * this->height
	);
}

Tile::Tile(Texture& texturesheet, v3i pos, v2f startPos)
{
	int top = rand() % 3;
	this->topSprite.setTexture(texturesheet);
	this->topSprite.setTextureRect(
		IntRect(
			top * 38, 
			0, 
			38, 
			15
		)
	);
	int left = rand() % 2;
	this->leftSprite.setTexture(texturesheet);
	this->leftSprite.setTextureRect(
		IntRect(
			(2*top+left)*19,
			15,
			19,
			15
		)
	);
	int right = rand() % 2;
	this->rightSprite.setTexture(texturesheet);
	this->rightSprite.setTextureRect(
		IntRect(
			(2 * top + right) * 19,
			30,
			19,
			15
		)
	);
	this->width = this->topSprite.getTextureRect().width;
	this->length = this->topSprite.getTextureRect().height;
	this->height = this->leftSprite.getTextureRect().height;
	this->topSprite.setOrigin(v2f(
		this->topSprite.getLocalBounds().width / 2.f,
		this->topSprite.getLocalBounds().height / 2.f));
	this->topSprite.setScale(2.f, 2.f);
	this->topSprite.setPosition(startPos+this->countPos(pos));
	this->leftSprite.setOrigin(v2f(
		this->leftSprite.getLocalBounds().width,
		0
	));
	this->leftSprite.setScale(2.f, 2.f);
	this->leftSprite.setPosition(this->topSprite.getPosition());
	this->rightSprite.setOrigin(v2f(
		0,
		0
	));
	this->rightSprite.setScale(2.f, 2.f);
	this->rightSprite.setPosition(this->topSprite.getPosition());
}

Tile::~Tile()
{
}

void Tile::update(const float& dt, v2f movement)
{
	this->topSprite.move(movement);
	this->leftSprite.move(movement);
	this->rightSprite.move(movement);
}

void Tile::render(RenderTarget& target, const bool topVisible, const bool leftVisible, const bool rightVisible)
{
	if (topVisible)
		target.draw(this->topSprite);
	if (leftVisible)
		target.draw(this->leftSprite);
	if (rightVisible)
		target.draw(this->rightSprite);
}
