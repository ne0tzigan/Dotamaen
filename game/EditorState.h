#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "GameState.h"

class EditorState :
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
	EditorState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>*);
	~EditorState();

	void endState();
	void render(sf::RenderTarget* target) override;
//	void renderButtons(RenderTarget& target) override;
	void update(const float& dt) override;
	void updateInput(const float& dt) override;
	void updateGui(const float& dt) override;
};

#endif // !EDITORSTATE_H
