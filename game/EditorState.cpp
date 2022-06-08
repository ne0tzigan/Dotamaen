#include "Header.h"
#include "EditorState.h"

void EditorState::initKeys(const map<str, int>* controlKeys)
{
	ifstream keys("config/editorstate_keybinds.ini");

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

void EditorState::initButtons(RenderTarget* target)
{
	float height = static_cast<float>(target->getSize().y);
	float width = static_cast<float>(target->getSize().x);
	float button_width = width / 6;
	float button_height = button_width / 3;
}

void EditorState::initFonts()
{
}

void EditorState::initBackground()
{
	/*this->backgroundTexture.loadFromFile("resources/images/backgrounds/MenuBackground.jpeg");
	this->background.setSize(v2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setTexture(&this->backgroundTexture);*/
}

void EditorState::initVariables()
{
}

EditorState::EditorState(RenderWindow* window, const map<str, int>* controlKeys, stack<State*>* statesOfGame)
	:State(window, controlKeys, statesOfGame)
{
	this->initKeys(controlKeys);
	this->initButtons(window);
	this->initFonts();
	this->initBackground();
	this->initVariables();
}

EditorState::~EditorState()
{
	for (auto& it : this->buttons)
		delete it.second;
}

void EditorState::endState()
{
	//cout << "Ending EditorState!";
	this->quit = true;
}

void EditorState::updateInput(const float& dt)
{
	if (key::isKeyPressed(key::Key(this->controlKeys.at("Quit"))))
		this->endState();
}

void EditorState::updateGui(const float& dt)
{
	str pressedButton;
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
		if (it.second->isPressed()) pressedButton = it.first;
	}
	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	target->draw(this->background);

	this->renderGui(*target);
}

void EditorState::update(const float& dt)
{
	//cout << "EditorState running\n" << dt << "\n"<< mousePosWindow.x << " " << mousePosWindow.y;
	this->updateMousePositions();
	this->updateGui(dt);
	this->updateInput(dt);
	system("cls");
}
