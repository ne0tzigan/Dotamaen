#include "Header.h"
#include "Entity.h"

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movement;
}

void Entity::setTexture(Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::setPosition(float x, float y)
{
	this->sprite.setPosition(v2f(x, y));
}

void Entity::createMovementComponent()
{
	this->movement = new MovementComponent(this->sprite);
}

void Entity::createAnimationComponent(Texture& textureSheet)
{
	this->animation = new AnimationComponent(this->sprite,textureSheet);
}

void Entity::createHitboxComponent(float offset_x, float offset_y, float width, float height)
{
	this->hitbox = new HitboxComponent(this->sprite, width, height, offset_x, offset_y);
}

void Entity::initVariables()
{
	//this->sprite->setSize(v2f(50.f, 50.f));
	//this->sprite->setFillColor(Color::White);
	this->movementStates[MovementState::IdleBack] = "IdleBack";
	this->movementStates[MovementState::IdleBackLeft] = "IdleBackLeft";
	this->movementStates[MovementState::IdleBackRight] = "IdleBackRight";
	this->movementStates[MovementState::IdleForward] = "IdleForward";
	this->movementStates[MovementState::IdleForwardLeft] = "IdleForwardLeft";
	this->movementStates[MovementState::IdleForwardRight] = "IdleForwardRight";
	this->movementStates[MovementState::IdleLeft] = "IdleLeft";
	this->movementStates[MovementState::IdleRight] = "IdleRight";
	this->movementStates[MovementState::WalkingBack] = "WalkingBack";
	this->movementStates[MovementState::WalkingBackLeft] = "WalkingBackLeft";
	this->movementStates[MovementState::WalkingBackRight] = "WalkingBackRight";
	this->movementStates[MovementState::WalkingForward] = "WalkingForward";
	this->movementStates[MovementState::WalkingForwardLeft] = "WalkingForwardLeft";
	this->movementStates[MovementState::WalkingForwardRight] = "WalkingForwardRight";
	this->movementStates[MovementState::WalkingLeft] = "WalkingLeft";
	this->movementStates[MovementState::WalkingRight] = "WalkingRight";
}

void Entity::move(v2f movement)
{
	this->sprite.move(movement);
}

void Entity::update(const float& dt)
{
	if (this->movement) {
		this->move(this->movement->movement());
		this->movement->update(dt);
	}
	if (this->hitbox) this->hitbox->update();
}

void Entity::render(RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->hitbox) this->hitbox->render(target);
}



