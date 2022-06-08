#ifndef STATE_H
#define STATE_H

#include "Entity.h"
#include "GUI.h"

class State {
protected:
	RenderWindow* window;
	Font font;
	map<str, Texture> textures;
	const map<str, int>* supportedKeys;
	map<str, int> controlKeys;
	map<str, Button*> buttons;
	stack<State*>* statesOfGame;
	bool quit;
	bool paused;
	float keytime = 0.f;
	float keytimeMax = 0.3f;

	v2i mousePosScreen;
	v2i mousePosWindow;
	v2f mousePosView;

	//Initializers
	virtual void initKeys(const map<str, int>*);
	virtual void initFonts();
	virtual void initBackground();
	virtual void initVariables();
	virtual void initButtons(RenderTarget* target);
public:
	State(RenderWindow*, const map<str, int>*, stack<State*>*);
	~State();
	
	//Acccessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions
	virtual void endState();
	void pauseState();
	void unpauseState();
	virtual void render(RenderTarget* target=nullptr) = 0;
	virtual void renderGui(RenderTarget& target);
	virtual void update(const float& dt) = 0;
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void updateKeytime(const float& dt);
	virtual void updateGui(const float& dt);
};

#endif