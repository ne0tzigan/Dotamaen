#include "Header.h"
#include "MainMenuState.h"


void MainMenuState::initKeys(const map<str, int>*)
{
}

void MainMenuState::initButtons(RenderTarget* target)
{
	float height = static_cast<float>(target->getSize().y);
	float width = static_cast<float>(target->getSize().x);
	float button_width = width/6;
	float button_height = button_width/3;
	int character_size = (int)width/50.f;
	this->buttons["Game_Start"] = new Button(width / 2.f, height * 0.4f,
		button_width, button_height,
		&this->font, "New Game", character_size,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
	);

	this->buttons["Editor_State"] = new Button(width / 2.f, height * 0.45f + button_height,
		button_width, button_height,
		&this->font, "Edit Levels", character_size,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
	);

	this->buttons["Settings"] = new Button(width / 2.f, height * 0.5f + button_height*2.f,
		button_width, button_height,
		&this->font, "Settings", character_size,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
	);

	this->buttons["Exit"] = new Button(width / 2.f, height * 0.55f + button_height*3.f,
		button_width, button_height,
		&this->font, "Quit", character_size,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(100, 100, 100), Color::Color(150, 150, 150), Color::Color(200, 200, 200),
		Color::Color(100, 100, 100), Color::Color(150, 150, 150), Color::Color(200, 200, 200)
	);
}

void MainMenuState::initFonts()
{
}

void MainMenuState::initBackground()
{
	this->backgroundTexture.loadFromFile("resources/images/backgrounds/MenuBackground.jpeg");
	this->background.setSize(v2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initVariables()
{
}

MainMenuState::MainMenuState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>* statesOfGame)
	:State(window, controlKeys, statesOfGame)
{
	this->initKeys(controlKeys);
	this->initButtons(window);
	this->initFonts();
	this->initBackground();
	this->initVariables();
}

MainMenuState::~MainMenuState()
{
	for (auto& it : this->buttons)
		delete it.second;
}

void MainMenuState::endState()
{
	//cout << "Ending MainMenuState!";
	this->quit = true;
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateGui(const float& dt)
{
	str pressedButton;
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
		if (it.second->isPressed() && this->getKeytime()) pressedButton = it.first;
	}
	if (pressedButton == "Game_Start") {
		statesOfGame->push(new GameState(this->window, this->supportedKeys, this->statesOfGame));
	}
	if (pressedButton == "Editor_State") {
		statesOfGame->push(new EditorState(this->window, this->supportedKeys, this->statesOfGame));
	}
	if (pressedButton == "Settings") {
		statesOfGame->push(new SettingsState(this->window, this->supportedKeys, this->statesOfGame));
	}
	else if (pressedButton == "Exit") {
		this->endState();
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	
	target->draw(this->background);
	
	this->renderGui(*target);
}

void MainMenuState::update(const float& dt)
{
	//cout << "MainMenuState running\n" << dt << "\n"<< mousePosWindow.x<<" "<<mousePosWindow.y;
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateGui(dt);
	this->updateInput(dt);
	system("cls");
}
