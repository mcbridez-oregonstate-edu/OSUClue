/********************************************************************
 * Program Name: SimpleButton.hpp
 * Date: 5/25/2020
 * Author: Abigail Minchella
 * Description: The header file for the SimpleButton class
********************************************************************/
#ifndef SIMPLEBUTTON_HPP
#define SIMPLEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum button_state { IDLE, HOVER, PRESSED };

class SimpleButton {

	private:
		sf::RectangleShape buttonBox;
		sf::Text buttonLabel;
		sf::Font font;
		sf::Color boxHoverColor;
		sf::Color textHoverColor;
		sf::Vector2f pos;
		int buttonState;

	public:
		SimpleButton(std::string, sf::Vector2f);
		void setButtonPos(sf::Vector2f);
		void update(const sf::Vector2f);
		void render(sf::RenderTarget*);
		bool isPressed();
};

#endif