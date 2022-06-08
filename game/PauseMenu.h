#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "GUI.h"

class PauseMenu {
private:
	Font& font;
	Text menuText;

	RectangleShape background;
	RectangleShape container;

	map<str, Button*> buttons;
public:
	PauseMenu(RenderWindow& window, Font& font, str text);
	~PauseMenu();

	void addButton(const str key, float x, float y, const str text);
	bool isButtonPressed(const str key);
	void update(const v2f& mousePos);
	void render(RenderTarget& target);
};

#endif