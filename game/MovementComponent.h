#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Define.h"

enum MovementState
{
	IdleForward = 0,
	IdleForwardRight,
	IdleRight,
	IdleBackRight,
	IdleBack,
	IdleBackLeft,
	IdleLeft,
	IdleForwardLeft,
	WalkingForward,
	WalkingForwardRight,
	WalkingRight,
	WalkingBackRight,
	WalkingBack,
	WalkingBackLeft,
	WalkingLeft,
	WalkingForwardLeft,
	RunningForward,
	RunningForwardRight,
	RunningRight,
	RunningBackRight,
	RunningBack,
	RunningBackLeft,
	RunningLeft,
	RunningForwardLeft,
	JumpingForward,
	JumpingForwardRight,
	JumpingRight,
	JumpingBackRight,
	JumpingBack,
	JumpingBackLeft,
	JumpingLeft,
	JumpingForwardLeft
};

class MovementComponent {
private:
	//variables
	Sprite& sprite;
	float dt;
	float dir;
	float turningSpeed;
	float movementSpeed;
	float maxMovementSpeed;
	float maxBackingSpeed;
	float accelerationSpeed;
	float decelerationSpeed;

	//functions
	virtual void turn(float dir);
	virtual void turn(float dir, float movementSpeed);
	static float normalizeAngle(float& dir);
	virtual float normalizeSpeed(float& movementSpeed);
	float countTurnAngle(float dir);
	float accelerate(float movementSpeed);
	float dirRadian();
public:
	//constructors/destructors
	MovementComponent(Sprite& sprite);
	MovementComponent(float dir,
		float movementSpeed,
		float turningSpeed,
		float maxMovementSpeed,
		float maxBackingSpeed,
		float accelerationSpeed,
		float decelerationSpeed,
		Sprite& sprite);
	~MovementComponent();

	virtual void turnLeft();
	virtual void turnRight();
	virtual void moveForward();
	virtual void moveBack();
	virtual void slowDown();
	virtual void moveToPoint(v2f point);
	v2f movement();
	unsigned short direction();
	unsigned short getState();
	static float radian(float dir);
	static float degrees(float dir);

	void update(const float& dt);
};

#endif // !MOVEMENT_COMPONENT_H
