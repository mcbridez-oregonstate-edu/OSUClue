/********************************************************************************
** Created by: Adam
** Date: 5/24/2020
** Description: Header file for the button class. Used to make buttons with the cards.
********************************************************************************/

#ifndef CARDBUTTON_HPP
#define CARDBUTTON_HPP

<<<<<<< HEAD
#include <SFML/Graphics.hpp>
#include <string>

enum button_states { IDLE = 0, HOVER, PRESSED };
=======
#include "buttonStates.hpp"
#include <SFML/Graphics.hpp>
#include <string>

>>>>>>> minchellaWork2

class CardButton {

private:
	sf::Sprite image;
	sf::Texture texture;
	sf::Color hoverColor;

	std::string name;
	sf::Vector2f pos;
<<<<<<< HEAD
	
	int buttonState;
=======

	button_states buttonState;
>>>>>>> minchellaWork2



public:
	CardButton(std::string card, sf::Vector2f b_pos);

	void setButtonPos(sf::Vector2f pos);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void resetPos();
	bool isPressed();
	std::string getName();
<<<<<<< HEAD

=======
	void setIdle();
>>>>>>> minchellaWork2


};




<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> minchellaWork2
