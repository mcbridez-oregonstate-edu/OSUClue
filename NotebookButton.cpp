
/********************************************************************************
** Created by: Adam
** Date: 5/31/2020
** Description: Implementation file for the notebookButton class. Used to make buttons for
				the notebook.
********************************************************************************/
#include "NotebookButton.hpp"


/********************************************************************************
** Name: CardButton::CardButton(std::string cardName)
** Description: Constructor for the CardButton class. Takes a string of the name
**				of the card to be made into a button
********************************************************************************/
NotebookButton::NotebookButton(int arrayPos, sf::Vector2f b_pos)
{
	shape.setSize(sf::Vector2f(10, 10));
	shape.move(b_pos);

	hoverColor = sf::Color(192, 192, 192);
	activeColor = sf::Color::Red;
	idleColor = sf::Color::White;

	shape.setFillColor(idleColor);

	buttonState = IDLE;
	notebookPos = arrayPos;



	colorFlag = 0;
}


/********************************************************************************
** Name: void CardButton::setBottonPos(std::Vector2f pos)
** Description: Function to set the position of the button.
********************************************************************************/
void NotebookButton::setButtonPos(sf::Vector2f targetPos)
{
	shape.setPosition(targetPos);
}

/********************************************************************************
** Name: void CardButton::update(sf::Vector2f mousePos)
** Description: Function that updates the button when hovered and pressed
********************************************************************************/
void NotebookButton::update(const sf::Vector2f mousePos)
{
	buttonState = IDLE;


	buttonState = IDLE;

	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonState = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = PRESSED;
		}
	}

	switch (buttonState)
	{

	case PRESSED:
		flipColor();
		break;

	default:
		break;
	}
}

/********************************************************************************
** Name: void CardButton::render(sf::RenderTarget* target)
** Description: Function that draws the button
********************************************************************************/
void NotebookButton::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

/********************************************************************************
** Name: void NotebookButton::flipColor()
** Description: Function that flips the button's color
********************************************************************************/
void NotebookButton::flipColor()
{
	if (colorFlag == 0) {
		colorFlag = 1;
		shape.setFillColor(activeColor);
	}
	else if (colorFlag == 1) {
		colorFlag = 0;
		shape.setFillColor(idleColor);
	}
}



/********************************************************************************
** Name: bool CardButton::isPressed()
** Description: Function that returns true if button is pressed
********************************************************************************/
bool NotebookButton::isPressed()
{
	if (buttonState == PRESSED) {
		return true;
	}
	return false;
}