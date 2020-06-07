/********************************************************************************
** Created by: Adam
** Date: 5/24/2020
** Description: Header file for the button class. Used to make buttons with the cards.
********************************************************************************/

#ifndef NOTEBOOKBUTTON_HPP
#define NOTEBOOKBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "CardButton.hpp"
<<<<<<< HEAD
#include <string>


//enum button_states { IDLE = 0, HOVER, PRESSED };

=======
#include "buttonStates.hpp"
#include <string>


>>>>>>> minchellaWork2
class NotebookButton {

private:
	sf::RectangleShape shape;
<<<<<<< HEAD
	
=======
>>>>>>> minchellaWork2

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	int notebookPos;
<<<<<<< HEAD
	
=======
>>>>>>> minchellaWork2

	int buttonState;
	int colorFlag;


public:
	NotebookButton(int pos, sf::Vector2f b_pos);
<<<<<<< HEAD
	
	void setButtonPos(sf::Vector2f pos);
	int update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target, int notebookValue);
=======

	void setButtonPos(sf::Vector2f pos);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
>>>>>>> minchellaWork2
	void flipColor();
	bool isPressed();




};
<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> minchellaWork2
