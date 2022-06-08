#include "Header.h"
#include "Game.h"

void Game::initWindow()
{
	std::ifstream ifs("config/window.ini");
	this->videomodes = VideoMode::getFullscreenModes();
	
	str title = "Lol";
	VideoMode windowBounds = VideoMode::getDesktopMode();
	bool fullScreen = false;
	unsigned framerateLimit = 120;
	bool verticalSyncEnabled = false;
	unsigned antialiasingLevel = 0;

	if (ifs.is_open()) 
	{
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> fullScreen;
		ifs >> framerateLimit;
		ifs >> verticalSyncEnabled;
		ifs >> antialiasingLevel;
	}
	ifs.close();

	this->windowSettings.antialiasingLevel = antialiasingLevel;
	if(fullScreen)
		this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	this->window->setFramerateLimit(framerateLimit);
	this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys,&this->states));
}

void Game::initKeys()
{
	ifstream keys("config/supported_keys.ini");

	if (keys.is_open()) 
	{
		str keyName;
		int keyValue;

		while (keys >> keyName >> keyValue) {
			this->supportedKeys[keyName] = keyValue;
		}

		keys.close();
	}
}

Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLevents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLevents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else this->window->close();
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->updateDt();
		this->update();
		this->render();
	}
}
