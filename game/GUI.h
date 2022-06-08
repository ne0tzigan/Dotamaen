#ifndef GUI_H
#define GUI_H

#include "Define.h"

enum ButtonStates {
	Default=0,
	Hover,
	Pressed
};

namespace gui {

	class Button {
	private:
		short unsigned buttonState;
		bool pressed;
		bool hover;

		RectangleShape shape;
		Font* font;
		Text text;
		Color mainColor;
		Color hoverColor;
		Color activeColor;
		Color textMainColor;
		Color textHoverColor;
		Color textActiveColor;
		Color outlineMainColor;
		Color outlineHoverColor;
		Color outlineActiveColor;
	public:
		Button(float x, float y, float xlength, float yheight,
			Font* font, str text, int fontSize, 
			Color mainColor = Color::Transparent, Color hoverColor = Color::Transparent, Color activeColor = Color::Transparent,
			Color textMainColor = Color::Color(255, 255, 255), Color textHoverColor = Color::Color(224,224,224), Color textActiveColor = Color::Color(192,192,192),
			Color outlineMainColor = Color::Color(255, 255, 255), Color outlineHoverColor = Color::Color(224, 224, 224), Color outlineActiveColor = Color::Color(192, 192, 192));
		Button(v2f position, v2f size,
			Font* font, str text, int fontSize, 
			Color mainColor = Color::Transparent,  Color hoverColor = Color::Transparent, Color activeColor=Color::Transparent,
			Color textMainColor = Color::Color(255, 255, 255), Color textHoverColor = Color::Color(224, 224, 224), Color textActiveColor = Color::Color(192, 192, 192),
			Color outlineMainColor = Color::Color(255, 255, 255), Color outlineHoverColor = Color::Color(224, 224, 224), Color outlineActiveColor = Color::Color(192, 192, 192));
		~Button();

		//Accessors
		const bool isPressed() const;
		const str getText() const;
		void setText(const str text);

		void render(RenderTarget& target);
		void update(const v2f&);
	};

	class DropDownList {
	private:
		Font& font;
		Button* activeElement;
		vector<Button*> list;
		bool showList;
		float keytime = 0.f;
		float keytimeMax = 0.3f;
		unsigned selectedIndex;
	public:
		DropDownList(Font& font, str list[], float xpos, float ypos, float button_width, float button_height, size_t numOfElements, unsigned default_index=0);
		~DropDownList();

		//Accessors
		const bool getKeytime();
		const unsigned getSelectedIndex();
		const str getSelectedValue();

		void update(const v2f& mousePos, const float& dt);
		void updateKeytime(const float& dt);
		void render(RenderTarget& target);
	};
}

using gui::Button;
using gui::DropDownList;

#endif