#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game {
private:
	vector<VideoMode> videomodes;
	ContextSettings windowSettings;
	RenderWindow *window;
	Event event;
	stack<State*> states;
	Clock dtClock;
	map<str, int> supportedKeys;
	float dt;
	//Initializer functions
	void initWindow();
	void initStates();
	void initKeys();
public:

	//Constructors
	Game();
	~Game();

	//Constants

	//Functions
	void updateDt();
	void updateSFMLevents();
	void update();
	void render();
	void run();


};

#endif
