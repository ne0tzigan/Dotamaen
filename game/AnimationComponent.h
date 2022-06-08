#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "Define.h"

class AnimationComponent {
private:
	class Animation {
	private:
		Sprite& sprite;
		Texture& textureSheet;
		float animationTime;
		float timer;
		IntRect startRect;
		IntRect currentRect;
		IntRect endRect;
	public:
		Animation(Sprite& sprite,Texture& textureSheet, int startX, int startY, int framesX, int framesY, int width, int height, float speed):
			sprite(sprite),
			textureSheet(textureSheet),
			animationTime(speed),
			startRect(IntRect(startX,startY,width,height)),
			endRect(IntRect(framesX*width,framesY*height,width,height))
		{
			this->currentRect = this->startRect;
			this->timer = 0.f;
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->currentRect);
		}
		
		bool play(const float& dt) 
		{
			bool done = false;
			this->timer += dt;
			if (timer >= animationTime) {
				timer = 0.f;
				if (this->currentRect.left < this->endRect.left) {
					this->currentRect.left += this->currentRect.width;
				}
				else {
					if (this->currentRect.top < this->endRect.top) {
						this->currentRect.left = this->startRect.left;
						this->currentRect.top += this->currentRect.height;
						done = true;
					}
					else
						this->reset();
				}
			}
			this->sprite.setTextureRect(this->currentRect);
			return done;
		}
		
		bool play(const float& dt, float modifier)
		{
			if (modifier < 0.5f) modifier = 0.5f;
			bool done = false;
			this->timer += dt*modifier;
			if (timer >= animationTime) {
				timer = 0.f;
				if (this->currentRect.left < this->endRect.left) {
					this->currentRect.left += this->currentRect.width;
				}
				else {
					if (this->currentRect.top < this->endRect.top) {
						this->currentRect.left = this->startRect.left;
						this->currentRect.top += this->currentRect.height;
						done = true;
					}
					else
						this->reset();
				}
			}
			this->sprite.setTextureRect(this->currentRect);
			return done;
		}
		void reset() {
			this->timer = animationTime;
			this->currentRect = this->startRect;
			this->sprite.setTextureRect(this->currentRect);
		}

	};

	Sprite& sprite;
	Texture& textureSheet;
	map<str, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;
public:
	AnimationComponent(Sprite& sprite, Texture& texture); 
	~AnimationComponent();

	void addAnimation(const str key, int startX, int startY, int framesX, int framesY, int width, int height, float speed = 0.3f);

	/*void startAnimation(const str animation);
	void pauseAnimation(const str animation);
	void resetAnimation(const str animation);
	*/
	void play(const str key,const float& dt, const bool priority=false);
	void play(const str key, const float& dt, const float& modifier, const float& modifier_max, const bool priority=false);
};

#endif