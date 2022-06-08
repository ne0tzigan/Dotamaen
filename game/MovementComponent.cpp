#include "Header.h"
#include "MovementComponent.h"


MovementComponent::MovementComponent(Sprite& sprite)
	: sprite(sprite),
	dir(0.f),
	movementSpeed(0.f),
	turningSpeed(10.f),
	maxMovementSpeed(50.f),
	maxBackingSpeed(50.f),
	accelerationSpeed(5.f),
	decelerationSpeed(5.f)
{}

MovementComponent::MovementComponent(float dir, float movementSpeed, float turningSpeed, float maxMovementSpeed, float maxBackingSpeed, float accelerationSpeed, float decelerationSpeed, Sprite& sprite)
	: sprite(sprite),
	dir(dir),
	movementSpeed(movementSpeed),
	turningSpeed(turningSpeed),
	maxMovementSpeed(maxMovementSpeed),
	maxBackingSpeed(maxBackingSpeed),
	accelerationSpeed(accelerationSpeed),
	decelerationSpeed(decelerationSpeed)
{
}

MovementComponent::~MovementComponent(){

}

float MovementComponent::countTurnAngle(float dir)
{
	if (dir < this->dir) dir += 360.f;
	float counterclockturn = dir - this->dir;
	float clockturn = this->dir + 360.f - dir;
	normalizeAngle(clockturn);
	if (counterclockturn < clockturn) {
		if (counterclockturn > this->turningSpeed*this->dt)
			return this->turningSpeed * this->dt;
		else return counterclockturn;
	}
	else {
		if (clockturn > this->turningSpeed * this->dt)
			return -this->turningSpeed * this->dt;
		else return -clockturn;
	}
}

float MovementComponent::accelerate(float movementSpeed)
{
	normalizeSpeed(movementSpeed);
	normalizeSpeed(this->movementSpeed);
	float deltaSpeed = movementSpeed - this->movementSpeed;
	if (deltaSpeed > 0) {
		if (deltaSpeed > this->accelerationSpeed * this->dt) return this->accelerationSpeed * this->dt;
		else return deltaSpeed;
	}
	else {
		if (abs(deltaSpeed) > this->decelerationSpeed * this->dt) return -this->decelerationSpeed * this->dt;
		else return deltaSpeed;
	}
}

float MovementComponent::dirRadian()
{
	return radian(this->dir);
}

void MovementComponent::turnLeft()
{
	this->turn(this->dir + 90.f);
}

void MovementComponent::turnRight()
{
	this->turn(this->dir - 90.f);
}

void MovementComponent::moveForward()
{
	this->turn(this->dir, this->maxMovementSpeed*this->dt);
}

void MovementComponent::moveBack()
{
	this->turn(this->dir, -this->maxBackingSpeed*this->dt);
}

void MovementComponent::slowDown()
{
	this->turn(this->dir, 0);
}


void MovementComponent::moveToPoint(v2f point)
{
	float x = point.x - this->sprite.getPosition().x;
	float y = point.y - this->sprite.getPosition().y;
	this->turn(MovementComponent::degrees(atan2f(-y, x)),this->maxMovementSpeed*this->dt);
}

v2f MovementComponent::movement()
{
	return v2f(
		this->movementSpeed * cos(this->dirRadian()),
		-this->movementSpeed * sin(this->dirRadian())
	);
	//this->sprite.setRotation(-this->dir);
}


void MovementComponent::turn(float dir)
{
	normalizeAngle(dir);
	normalizeAngle(this->dir);
	this->dir += this->countTurnAngle(dir);
	normalizeSpeed(this->movementSpeed);
}

void MovementComponent::turn(float dir, float movementSpeed)
{
	normalizeAngle(dir);
	normalizeAngle(this->dir);
	this->dir += this->countTurnAngle(dir);
	this->movementSpeed += this->accelerate(movementSpeed * cos(radian(abs(dir - this->dir))));
}

void MovementComponent::update(const float& dt)
{
	this->movementSpeed /= this->dt;
	this->dt = dt/0.03f;
	this->movementSpeed *= this->dt;
	/*cout << this->movementSpeed << "\n"
		<< this->maxMovementSpeed * this->dt << "\n"
		<< this->maxBackingSpeed * this->dt << "\n"
		<< this->accelerationSpeed * this->dt << "\n"
		<< this->decelerationSpeed * this->dt << "\n"
	<< this->direction();*/
}

unsigned short MovementComponent::direction()
{
	float dir = this->dir - 247.5f;
	return trunc(normalizeAngle(dir) / 45.f);
}

unsigned short MovementComponent::getState()
{
	unsigned short res = this->direction();
	if (this->movementSpeed != 0) res += 8;
	return res;
}

float MovementComponent::radian(float dir)
{
	return dir * PI / 180.f;
}

float MovementComponent::degrees(float dir)
{
	return (dir / PI) * 180.f;
}

float MovementComponent::normalizeAngle(float& dir)
{
	while (dir < 0.f) dir += 360.f;
	while (dir >= 360.f) dir -= 360.f;
	return dir;
}

float MovementComponent::normalizeSpeed(float& movementSpeed)
{
	if (movementSpeed < -this->maxBackingSpeed * dt) movementSpeed = -this->maxBackingSpeed * dt;
	if (movementSpeed > this->maxMovementSpeed * dt) movementSpeed = this->maxMovementSpeed * dt;
	return movementSpeed;
}