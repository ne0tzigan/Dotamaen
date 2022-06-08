#include "Header.h"
#include "PauseMenu.h"


PauseMenu::PauseMenu(RenderWindow& window, Font& font, str text):
	font(font)
{
	this->background.setSize(v2f(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y)
	));
	this->background.setFillColor(Color::Color(20, 20, 20, 100));
	this->container.setSize(v2f(
		static_cast<float>(window.getSize().x/2),
		static_cast<float>(window.getSize().y)
	));
	this->container.setFillColor(Color::Color(20,20,128,100));
	this->container.setPosition(v2f(
		static_cast<float>(window.getSize().x / 4),
		0.f
	));
	this->menuText.setFont(this->font);
	this->menuText.setString(text);
	this->menuText.setOrigin(v2f(
		this->menuText.getLocalBounds().width / 2.f,
		this->menuText.getLocalBounds().height / 2.f
	));
	this->menuText.setPosition(v2f(
		static_cast<float>(window.getSize().x)/2,
		static_cast<float>(window.getSize().y)/4
	));
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin();it!=this->buttons.end();++it) {
		delete it->second;
	}
}

void PauseMenu::addButton(const str key, float x, float y, const str text)
{
	x += this->container.getPosition().x+this->container.getSize().x/2;
	y += this->menuText.getGlobalBounds().top+this->menuText.getGlobalBounds().height;
	this->buttons[key] = new Button(x, y,
		this->container.getGlobalBounds().width / 2.f, this->container.getGlobalBounds().height / 10.f,
		&this->font, text, 30,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200)
	);
}

bool PauseMenu::isButtonPressed(const str key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::update(const v2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->update(mousePos);
	}
}

void PauseMenu::render(RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->menuText);
	
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}
