#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "SettingsState.h"

class MainMenuState:
	public State 
{
private:
	Texture backgroundTexture;
	RectangleShape background;
	void initKeys(const map<str, int>*);
	void initButtons(RenderTarget* target) override;
	void initFonts() override;
	void initBackground();
	void initVariables();
public:
	MainMenuState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>*);
	~MainMenuState();

	void endState();
	void render(RenderTarget* target) override;
	//void renderGui(RenderTarget& target) override;
	void update(const float& dt) override;
	void updateInput(const float& dt) override;
	void updateGui(const float& dt) override;
};

#endif