/********************************************************************************
** Created by: Adam
** Date: 5/24/2020
** Description: Header file for the button class. Used to make buttons with the cards.
********************************************************************************/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum button_states { IDLE = 0, HOVER, PRESSED };

class CardButton {

private:
	sf::Sprite image;
	sf::Texture texture;
	sf::Color hoverColor;

	std::string name;
	sf::Vector2f pos;

	int buttonState;



public:
	CardButton(std::string card, sf::Vector2f b_pos);

	void setButtonPos(sf::Vector2f pos);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void resetPos();
	bool isPressed();
	std::string getName();
};




#endif