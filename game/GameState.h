#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState:
	public State 
{
private:
	//variables
	Player* player;
	PauseMenu* pauseMenu;
	TileMap* tileMap;

	//initializers
	void initKeys(const map<str, int>*) override;
	void initVariables() override;
	void initTextures();
	void initTileMap();
	void initPauseMenu();
	void initPlayer();
public:
	//constructors/destructors
	GameState(RenderWindow* window,const map<str,int>* controlKeys, stack<State*>* states);
	~GameState();

	//functions
	void endState() override;
	void updatePlayerInput(const float& dt);
	void render(RenderTarget* target) override;
	void update(const float& dt) override;
	void updateInput(const float& dt) override;
};

#endif