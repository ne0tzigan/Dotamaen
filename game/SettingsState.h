#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "EditorState.h"

class SettingsState
	:public State 
{
private:
	Texture backgroundTexture;
	RectangleShape background;
	map<str, DropDownList*> dropDownLists;
	Text optionsText;
	vector<VideoMode> modes;

	void initKeys(const map<str, int>*);
	void initButtons(RenderTarget* target) override;
	void initFonts() override;
	void initBackground();
	void initVariables();
	void initText();
public:
	SettingsState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>*);
	~SettingsState();

	void endState();
	void render(RenderTarget* target) override;
	void renderGui(RenderTarget& target) override;
	void update(const float& dt) override;
	void updateInput(const float& dt) override;
	void updateGui(const float& dt) override;
	void updateRenderMode(RenderTarget* target);
};

#endif