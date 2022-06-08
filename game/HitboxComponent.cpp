#include "Header.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(Sprite& sprite, 
	float width, float height, 
	float offset_x, float offset_y):
	sprite(sprite), offset_x(offset_x), offset_y(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offset_x, this->sprite.getPosition().y + this->offset_y);
	this->hitbox.setSize(v2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(Color::Red);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkIntersect(const FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
}

void HitboxComponent::render(RenderTarget& target)
{
	target.draw(this->hitbox);
}
