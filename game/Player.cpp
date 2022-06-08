#include "Header.h"
#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponents(Texture& textureSheet)
{
	this->createMovementComponent();
	this->createAnimationComponent(textureSheet);
	this->animation->addAnimation("WalkingForward", 0, 0, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingBack", 0, 90, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingRight", 0, 180, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingLeft", 0, 270, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingForwardRight", 0, 360, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingForwardLeft", 0, 450, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingBackLeft", 0, 540, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("WalkingBackRight", 0, 630, 7, 0, 90, 90, 0.1f);
	this->animation->addAnimation("IdleForward", 0, 0, 0, 0, 90, 90, 1.f);
	this->animation->addAnimation("IdleBack", 0, 90, 0, 0, 90, 90, 1.f);
	this->animation->addAnimation("IdleRight", 0, 180, 0, 0, 90, 90, 1.f);
	this->animation->addAnimation("IdleLeft", 0, 270, 0, 0, 90, 90, 1.f);
	this->animation->addAnimation("IdleForwardRight", 0, 360, 0, 0, 90, 90, 0.1f);
	this->animation->addAnimation("IdleForwardLeft", 0, 450, 0, 0, 90, 90, 0.1f);
	this->animation->addAnimation("IdleBackLeft", 0, 540, 0, 0, 90, 90, 0.1f);
	this->animation->addAnimation("IdleBackRight", 0, 630, 0, 0, 90, 90, 0.1f);
	this->sprite.setScale(2.f, 2.f);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2, this->sprite.getLocalBounds().height-10.f);
	this->createHitboxComponent(-this->sprite.getGlobalBounds().width / 4, -this->sprite.getGlobalBounds().height +20.f, this->sprite.getGlobalBounds().width/2.f, this->sprite.getGlobalBounds().height*0.95f);
	//this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2, this->sprite.getLocalBounds().height / 2);
}

/*Player::Player()
{
	Texture& texture=Texture();
	texture.loadFromFile("textures/player.png");
	this->initVariables();
	this->initComponents();
	this->setTexture(texture);
	this->setPosition(400.f, 300.f);
}*/

Player::Player(float x, float y, Texture& textureSheet)
{
	this->setPosition(x, y);
	this->initComponents(textureSheet);
	this->initVariables();

}

Player::~Player()
{
}

void Player::createMovementComponent()
{
	this->movement = new MovementComponent(0.f, 0.f, 10.f, 10.f, 5.f, 2.f, 1.f, this->sprite);
}

void Player::Attack()
{
	this->attacking = true;
}

void Player::update(const float& dt, v2f& movement)
{
	if (this->movement) {
		movement = -this->movement->movement(); //count the movement of player;
		this->movement->update(dt);//move
	}
	if (this->hitbox) this->hitbox->update();
	str key = this->movementStates.at(this->movement->getState());//"Walking_"+this->movement->direction();
	this->animation->play(key, dt);
}

