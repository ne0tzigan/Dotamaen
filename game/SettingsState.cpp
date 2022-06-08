#include "Header.h"
#include "SettingsState.h"

void SettingsState::initKeys(const map<str, int>*)
{
}

void SettingsState::initButtons(RenderTarget* target)
{
	float height = static_cast<float>(target->getSize().y);
	float width = static_cast<float>(target->getSize().x);
	float button_width = width / 6;
	float button_height = button_width / 3;
	int character_size = (int)width / 50;
	this->buttons["Exit"] = new Button(width / 2.f, height * 0.4f,
		button_width, button_height,
		&this->font, "[<-] Go Back", character_size,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
	); this->buttons["Submit"] = new Button(width / 2.f, height * 0.9f,
		button_width, button_height,
		&this->font, "Submit", character_size,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
	);
	vector<str> modes_str{ "1920x1680","800x600","640x480" };
	for (auto& it : this->modes) {
		modes_str.push_back(std::to_string(it.width) + "x" + std::to_string(it.height));
	}
	this->dropDownLists["Resolution"] = new DropDownList(this->font, modes_str.data(), width / 2.f, height * 0.6f, button_width, button_height, modes_str.size());
}

void SettingsState::initFonts()
{
}

void SettingsState::initBackground()
{
	this->backgroundTexture.loadFromFile("resources/images/backgrounds/MenuBackground.jpeg");
	this->background.setSize(v2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initVariables()
{
	this->modes = VideoMode::getFullscreenModes();
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(v2f(100.f, 100.f));

	this->optionsText.setString(
	"Resolution\nFulscreen\nVsync\nAnti-aliasing\n"
	); 
}

SettingsState::SettingsState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>* statesOfGame)
	:State(window, controlKeys, statesOfGame)
{
	this->initKeys(controlKeys);
	this->initButtons(window);
	this->initFonts();
	this->initBackground();
	this->initVariables();
}

SettingsState::~SettingsState()
{
	for (auto& it : this->buttons)
		delete it.second;
	for (auto& it : this->dropDownLists)
		delete it.second;
}

void SettingsState::endState()
{
	//cout << "Ending SettingsState!";
	this->quit = true;
}

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::updateGui(const float& dt)
{
	str pressedButton;
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
		if (it.second->isPressed() && this->getKeytime()) pressedButton = it.first;
	}
	if (pressedButton == "Exit") {
		this->endState();
	}
	if (pressedButton == "Submit") {
		this->window->create(this->modes.at(this->dropDownLists["Resolution"]->getSelectedIndex()),"test",sf::Style::Default);
	}
	for (auto& it : this->dropDownLists) {
		it.second->update(this->mousePosView, dt);
	}
}

void SettingsState::updateRenderMode(RenderTarget* target)
{
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	target->draw(this->background);

	this->renderGui(*target);
}

void SettingsState::renderGui(RenderTarget& target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
	for (auto& it : this->dropDownLists)
		it.second->render(target);
}

void SettingsState::update(const float& dt)
{
	//cout << "SettingsState running\n" << dt << "\n"<< mousePosWindow.x << " " << mousePosWindow.y;
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateGui(dt);
	this->updateInput(dt);
	system("cls");
}
