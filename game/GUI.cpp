#include "Header.h"
#include "GUI.h"


gui::Button::Button(float x, float y, float xlength, float yheight, Font* font, str text, int fontSize,
	Color mainColor, Color hoverColor, Color activeColor,
	Color textMainColor, Color textHoverColor, Color textActiveColor,
	Color outlineMainColor, Color outlineHoverColor, Color outlineActiveColor)
	:gui::Button(v2f(x, y), v2f(xlength, yheight), font, text, fontSize, 
		mainColor, hoverColor, activeColor,
		textMainColor, textHoverColor, textActiveColor,
		outlineMainColor, outlineHoverColor, outlineActiveColor)
{
}

gui::Button::Button(v2f position, v2f size, Font* font, str text, int fontSize, 
	Color mainColor, Color hoverColor, Color activeColor,
	Color textMainColor, Color textHoverColor, Color textActiveColor,
	Color outlineMainColor, Color outlineHoverColor, Color outlineActiveColor):
	mainColor(mainColor),
	hoverColor(hoverColor),
	activeColor(activeColor),
	textMainColor(textMainColor),
	textHoverColor(textHoverColor),
	textActiveColor(textActiveColor),
	outlineMainColor(outlineMainColor),
	outlineHoverColor(outlineHoverColor),
	outlineActiveColor(outlineActiveColor)
{
	this->buttonState = Default;

	this->shape.setPosition(position);
	this->shape.setSize(size);
	this->shape.setOrigin(
		this->shape.getLocalBounds().width/2,
		this->shape.getLocalBounds().height /2
	);
	this->shape.setOutlineThickness(2.f);
	
	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->textMainColor);
	this->text.setCharacterSize(fontSize);
	this->text.setOrigin(v2f(
		this->text.getLocalBounds().width / 2, 
		this->text.getLocalBounds().height / 2
	));
	this->text.setPosition(this->shape.getPosition());
}

gui::Button::~Button()
{
}

void gui::Button::render(RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

const bool gui::Button::isPressed() const
{
	return buttonState==Pressed;
}

const str gui::Button::getText() const
{
	return this->text.getString();
}

void gui::Button::setText(const str text)
{
	this->text.setString(text);
	this->text.setOrigin(v2f(
		this->text.getLocalBounds().width / 2,
		this->text.getLocalBounds().height / 2
	));
}

void gui::Button::update(const v2f& mousePos)
{
	buttonState = Default;
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
			buttonState = Pressed;
		else
			buttonState = Hover;
	}
	
	switch (this->buttonState) {
	case Default:
		this->shape.setFillColor(this->mainColor);
		this->shape.setOutlineColor(this->outlineMainColor);
		this->text.setFillColor(this->textMainColor);
		break;
	case Hover:
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case Pressed:
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(Color::Black);
		this->shape.setOutlineColor(Color::Red);
		this->text.setFillColor(Color::Red);
		break;
	}
}

gui::DropDownList::DropDownList(Font& font, str list[], float xpos, float ypos, float button_width, float button_height, size_t numOfElements, unsigned defaultIndex)
	:font(font), selectedIndex(defaultIndex)
{
	for (size_t i = 0; i < numOfElements; i++) {
		this->list.push_back(new Button(xpos, ypos + (i + 1) * button_height,
			button_width, button_height,
			&this->font, list[i], 20,
			Color::Color(30, 30, 100), Color::Color(30, 30, 100), Color::Color(30, 30, 100),
			Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
			Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
		));
	}
	this->activeElement = new Button(xpos, ypos,
		button_width, button_height,
		&this->font, list[defaultIndex], 20,
		Color::Color(30, 30, 100, 100), Color::Color(30, 30, 100, 150), Color::Color(30, 30, 100, 200),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30),
		Color::Color(0, 0, 0), Color::Color(20, 20, 20), Color::Color(30, 30, 30)
	);
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (auto& it : this->list) {
		delete it;
	}
}

const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const unsigned gui::DropDownList::getSelectedIndex()
{
	return this->selectedIndex;
}

const str gui::DropDownList::getSelectedValue()
{
	return this->list[this->selectedIndex]->getText();
}

void gui::DropDownList::update(const v2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);
	this->activeElement->update(mousePos);
	if (this->activeElement->isPressed() && this->getKeytime()) this->showList=!this->showList;
	
	if (this->showList) {
		unsigned index=0;
		for (auto& it : this->list) {
			it->update(mousePos);

			if (it->isPressed() && this->getKeytime()) {
				this->showList = false;
				this->activeElement->setText(it->getText());
				this->selectedIndex = index;
			}
			index++;
		}
	}
}

void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax) {
		this->keytime += dt;
	}
}

void gui::DropDownList::render(RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList) {
		for (auto& it : this->list) {
			it->render(target);
		}
	}
}
