/********************************************************************************
** Created by: Adam
** Date: 5/24/2020
** Description: Header file for the button class. Used to make buttons with the cards.
********************************************************************************/

#ifndef NOTEBOOKBUTTON_HPP
#define NOTEBOOKBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "CardButton.hpp"
#include "buttonStates.hpp"
#include <string>


class NotebookButton {

private:
	sf::RectangleShape shape;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	int notebookPos;

	int buttonState;
	int colorFlag;


public:
	NotebookButton(int pos, sf::Vector2f b_pos);

	void setButtonPos(sf::Vector2f pos);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void flipColor();
	bool isPressed();




};
#endif