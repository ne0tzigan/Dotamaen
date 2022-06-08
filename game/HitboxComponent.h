#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#include"Define.h"

class HitboxComponent {
private:
	Sprite& sprite;
	RectangleShape hitbox;
	float offset_x;
	float offset_y;
public:
	HitboxComponent(Sprite& sprite,float width, float height, float offset_x, float offset_y);
	~HitboxComponent();

	bool checkIntersect(const FloatRect& frect);

	void update();
	void render(RenderTarget& target);
};

#endif
