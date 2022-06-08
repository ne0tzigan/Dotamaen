#include "Header.h"
#include "State.h"

void State::initKeys(const map<str, int>* controlKeys)
{
	ifstream keys("config/general_keybinds.ini");

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

void State::initFonts()
{
	if (this->font.loadFromFile("fonts/GALS.ttf")) {
		cout << "Error: Font is not downloaded. Enjoy your boring adventure.";
	}
}

void State::initBackground()
{
}

void State::initVariables()
{
}

void State::initButtons(RenderTarget* target)
{
}

State::State(sf::RenderWindow* window, const map<str,int>* controlKeys, stack<State*>* statesOfGame)
{
	this->window = window;
	this->supportedKeys = controlKeys;
	this->statesOfGame = statesOfGame;
	initFonts();
	initKeys(controlKeys);
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax) 
	{	
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void State::endState()
{
	this->endState();
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime<this->keytimeMax) {
		this->keytime += dt;
	}
}

void State::updateGui(const float& dt)
{
}

void State::renderGui(RenderTarget& target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}
