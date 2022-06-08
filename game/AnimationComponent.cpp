#include "Header.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& texture) :
	sprite(sprite), textureSheet(texture), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations) {
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const str key, int startX, int startY, int framesX, int framesY, int width, int height, float speed) {
	this->animations[key] = new Animation(this->sprite, this->textureSheet, startX, startY, framesX, framesY, width, height, speed);
}

void AnimationComponent::play(const str key, const float& dt, const bool priority) {
	if (this->animations.count(key)) {
		if (this->priorityAnimation) {
			if (this->priorityAnimation == this->animations[key]) {
				if (!this->lastAnimation) this->lastAnimation = this->animations[key];
				else if (this->lastAnimation != this->animations[key]) {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
				if (this->animations[key]->play(dt)) this->priorityAnimation = NULL;
			}

		}
		else {
			if (!this->lastAnimation) this->lastAnimation = this->animations[key];
			else if (this->lastAnimation != this->animations[key]) {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
			this->animations[key]->play(dt);
		}
	}
	else {
		if (this->lastAnimation) this->lastAnimation->reset();
	}
}

void AnimationComponent::play(const str key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->animations.count(key)) {
		if (this->lastAnimation == NULL) this->lastAnimation = this->animations[key];
		else if (this->lastAnimation != this->animations[key]) {
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
		this->animations[key]->play(dt,modifier/modifier_max);
	}
	else {
		if (this->lastAnimation != NULL) this->lastAnimation->reset();
	}
}