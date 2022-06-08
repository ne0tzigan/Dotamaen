#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity {
private:
	void initVariables();
protected:
	Sprite sprite;
	map<int,str> movementStates;
public:
	MovementComponent* movement;
	AnimationComponent* animation;
	HitboxComponent* hitbox;

	//Constructors
	Entity();
	virtual ~Entity();

	void setTexture(Texture& texture);
	void setPosition(float x, float y);
	virtual void createMovementComponent();
	virtual void createAnimationComponent(Texture& textureSheet);
	virtual void createHitboxComponent(float offset_x, float offset_y, float width, float height);

	virtual void move(v2f movement);
	virtual void update(const float& dt);
	virtual void render(RenderTarget& target);
};

#endif // !ENTITY_H
