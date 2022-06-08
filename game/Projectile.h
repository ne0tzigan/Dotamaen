#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile
	:public Entity
{
private:
	void initVariables();
	void initComponents(Texture& textureSheet);
public:
	//	Player();
	Projectile(float x, float y, Texture& texture);
	virtual ~Projectile();
	void createMovementComponent() override;

	void update(const float& dt) override;
};

#endif