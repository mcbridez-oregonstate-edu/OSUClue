/****************************************************************************
 * Program Name: CharacterButton.hpp
 * Date: 5/25/2020
 * Author: Abigail Minchella (heavily adapted from CardButton by Adam Pham)
 * Description: The header file for the CharacterButton class
****************************************************************************/
#ifndef CHARACTERBUTTON_HPP
#define CHARACTERBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum character_button_state { IDLE, HOVER, PRESSED, DISABLED };

class CharacterButton {

private:
	sf::Sprite image;
	sf::Texture texture;
	sf::Color hoverColor;

	std::string name;
	sf::Vector2f pos;

	int buttonState;

public:
	CharacterButton(std::string, sf::Vector2f);

	void setButtonPos(sf::Vector2f);
	void update(const sf::Vector2f);
	void render(sf::RenderTarget*);
	void resetPos();
	bool isPressed();
	std::string getName();
	void setDisabled();
};

#endif