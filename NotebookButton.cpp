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
<<<<<<< HEAD
	
	hoverColor = sf::Color(192,192,192);
=======

	hoverColor = sf::Color(192, 192, 192);
>>>>>>> minchellaWork2
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
<<<<<<< HEAD
int NotebookButton::update(const sf::Vector2f mousePos)
=======
void NotebookButton::update(const sf::Vector2f mousePos)
>>>>>>> minchellaWork2
{
	buttonState = IDLE;


<<<<<<< HEAD
	if (shape.getGlobalBounds().contains(mousePos)) {
			buttonState = PRESSED;
	}

	switch (buttonState) {
	
	case PRESSED:
		//flipColor();
		return 1;
	default:
		return 0;
		break;

=======
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
>>>>>>> minchellaWork2
	}
}

/********************************************************************************
** Name: void CardButton::render(sf::RenderTarget* target)
** Description: Function that draws the button
********************************************************************************/
<<<<<<< HEAD
void NotebookButton::render(sf::RenderTarget* target, int notebookValue)
{
	if (notebookValue == 1) {
		shape.setFillColor(activeColor);
		
	}
	else {
		shape.setFillColor(idleColor);
		
	}
	target->draw(shape);	
=======
void NotebookButton::render(sf::RenderTarget* target)
{
	target->draw(shape);
>>>>>>> minchellaWork2
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
<<<<<<< HEAD


=======
>>>>>>> minchellaWork2
