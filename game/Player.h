#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player
	:public Entity , public IAttacking
{
private:
	void initVariables();
	void initComponents(Texture& textureSheet);
public:
//	Player();
	Player(float x, float y, Texture& texture);
	virtual ~Player();
	void createMovementComponent() override;
	void Attack() override;

	void update(const float& dt, v2f& movement);
};

#endif