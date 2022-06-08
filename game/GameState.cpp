#include "Header.h"
#include "GameState.h"

void GameState::initKeys(const map<str, int>* controlKeys)
{
	ifstream keys("config/gamestate_keybinds.ini");

	if (keys.is_open())
	{
		str name;
		str key;

		while (keys >> name >> key) {
			this->controlKeys.emplace(name, controlKeys->at(key));
		}

		keys.close();
	}
}

void GameState::initVariables()
{
}

void GameState::initTextures()
{
	if (!this->textures["Player_Idle"].loadFromFile("resources/images/textures/sprites/player/playeranimation.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}
}

void GameState::initTileMap()
{
	tileMap = new TileMap();
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*window, this->font,"Game paused");
	this->pauseMenu->addButton("Quit", 0.f, 600.f, "Exit");
}

void GameState::initPlayer()
{
	if (this->window)
		this->player = new Player(this->window->getView().getSize().x / 2, this->window->getView().getSize().y / 2, this->textures["Player_Idle"]);
}

GameState::GameState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>* statesOfGame)
	:State(window, controlKeys, statesOfGame)
{
	this->initKeys(controlKeys);
	this->initVariables();
	this->initTextures();
	this->initFonts();
	this->initPlayer();
	this->initTileMap();
	this->initPauseMenu();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pauseMenu;
	delete this->tileMap;
}


void GameState::endState()
{//ending this state
	//cout << "Ending GameState!";
	this->quit = true;
}

void GameState::updatePlayerInput(const float& dt)
{
	/*if (key::isKeyPressed(key::W))
		this->player.turn(90, this->player.maxMovementSpeed);
	else if (key::isKeyPressed(key::A))
		this->player.turn(180, this->player.maxMovementSpeed);
	else if (key::isKeyPressed(key::S))
		this->player.turn(270, this->player.maxMovementSpeed);
	else if (key::isKeyPressed(key::D))
		this->player.turn(0, this->player.maxMovementSpeed);*/
	bool inputFlag=false;
	if (key::isKeyPressed(key::Key(this->controlKeys.at("Turn_Left")))) 
	{
		this->player->movement->turnLeft();
		inputFlag = true;
	}
	else {
		if (key::isKeyPressed(key::Key(this->controlKeys.at("Turn_Right")))) {
			this->player->movement->turnRight();
			inputFlag = true;
		}
	}
	if (key::isKeyPressed(key::Key(this->controlKeys.at("Move_Forward"))))
	{
		this->player->movement->moveForward();
		inputFlag = true;
	}
	else {
		if (key::isKeyPressed(key::Key(this->controlKeys.at("Move_Back"))))
		{
			this->player->movement->moveBack();
			inputFlag = true;
		}
	}
	if (Mouse::isButtonPressed(Mouse::Right)) {
		this->player->movement->moveToPoint(mousePosView);
		bool inputFlag = true;
	}
	if(!inputFlag)
	this->player->movement->slowDown();
}

void GameState::render(RenderTarget* target)
{
	if (!target) target = this->window;
	this->tileMap->render(*target);
	this->player->render(*target);
	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}
}

void GameState::update(const float& dt)
{
	//cout << "GameState running\n" << dt << "\n"	<<this->mousePosView.x<<" "<<this->mousePosView.y<<"\n";
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this->paused)
	{
		v2f movement;
		this->player->update(dt, movement);
		this->tileMap->update(dt, movement);
		this->updatePlayerInput(dt);
	}
	else 
	{
		this->pauseMenu->update(mousePosView);
	}
	system("cls");
}

void GameState::updateInput(const float& dt)
{
	if (key::isKeyPressed(key::Key(this->controlKeys.at("Quit"))) && this->getKeytime()) {
		this->paused = !this->paused;
	}
	if (this->pauseMenu->isButtonPressed("Quit") && this->getKeytime()) {
		this->endState();
	}
}
