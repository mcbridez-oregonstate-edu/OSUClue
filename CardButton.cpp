/********************************************************************************
** Created by: Adam
** Date: 5/24/2020
** Description: Implementation file for the button class. Used to make buttons with the cards.
********************************************************************************/
#include "CardButton.hpp"


/********************************************************************************
** Name: CardButton::CardButton(std::string cardName)
** Description: Constructor for the CardButton class. Takes a string of the name
**				of the card to be made into a button
********************************************************************************/
CardButton::CardButton(std::string cardName, sf::Vector2f b_pos)
{
	if (cardName == "Miss Scarlet") {
		texture.loadFromFile("res/images/suspects/scarlett.jpg");
	}
	else if (cardName == "Mr. Green") {
		texture.loadFromFile("res/images/suspects/green.jpg");
	}
	else if (cardName == "Colonel Mustard") {
		texture.loadFromFile("res/images/suspects/mustard.jpg");
	}
	else if (cardName == "Mrs. White") {
		texture.loadFromFile("res/images/suspects/white.jpg");
	}
	else if (cardName == "Mrs. Peacock") {
		texture.loadFromFile("res/images/suspects/peacock.jpg");
	}
	else if (cardName == "Professor Plum")
	{
		texture.loadFromFile("res/images/suspects/plum.jpg");
	}
	else if (cardName == "Rope")
	{
		texture.loadFromFile("res/images/weapons/rope.jpg");
	}
	else if (cardName == "Wrench") {
		texture.loadFromFile("res/images/weapons/wrench.jpg");
	}
	else if (cardName == "Lead Pipe") {
		texture.loadFromFile("res/images/weapons/leadpipe.jpg");
	}
	else if (cardName == "Knife") {
		texture.loadFromFile("res/images/weapons/knife.jpg");
	}
	else if (cardName == "Candlestick") {
		texture.loadFromFile("res/images/weapons/candlestick.jpg");
	}
	else if (cardName == "Revolver") {
		texture.loadFromFile("res/images/weapons/revolver.jpg");
	}
	else if (cardName == "Lounge") {
		texture.loadFromFile("res/images/locations/lounge.jpg");
	}
	else if (cardName == "Library") {
		texture.loadFromFile("res/images/locations/library.jpg");;
	}
	else if (cardName == "Ballroom") {
		texture.loadFromFile("res/images/locations/ballroom.jpg");
	}
	else if (cardName == "Billiard Room") {
		texture.loadFromFile("res/images/locations/billiard.jpg");
	}
	else if (cardName == "Kitchen") {
		texture.loadFromFile("res/images/locations/kitchen.jpg");
	}
	else if (cardName == "Conservatory") {
		texture.loadFromFile("res/images/locations/conservatory.jpg");
	}
	else if (cardName == "Hall") {
		texture.loadFromFile("res/images/locations/hall.jpg");
	}
	else if (cardName == "Study") {
		texture.loadFromFile("res/images/locations/study.jpg");
	}
	else if (cardName == "Dining Room") {
		texture.loadFromFile("res/images/locations/dining.jpg");
	}

	image.setTexture(texture);
	image.move(b_pos);
	pos = b_pos;
	hoverColor = sf::Color(255, 255, 255, 128);
	buttonState = IDLE;
	name = cardName;
}


/********************************************************************************
** Name: void CardButton::setBottonPos(std::Vector2f pos)
** Description: Function to set the position of the button.
********************************************************************************/
void CardButton::setButtonPos(sf::Vector2f targetPos)
{
	image.setPosition(targetPos);
}

/********************************************************************************
** Name: void CardButton::update(sf::Vector2f mousePos)
** Description: Function that updates the button when hovered and pressed
********************************************************************************/
void CardButton::update(const sf::Vector2f mousePos)
{
	buttonState = IDLE;
	

	if (image.getGlobalBounds().contains(mousePos)) {
		buttonState = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = PRESSED;
		}
	}

	switch (buttonState) {
		case IDLE:
			// set color to original
			image.setColor(sf::Color(255, 255, 255));
			break;
		case HOVER:
			image.setColor(hoverColor);
			break;
		default:
			// turn yellow on click
			image.setColor(sf::Color::Yellow);
			break;

	}
}

/********************************************************************************
** Name: void CardButton::render(sf::RenderTarget* target)
** Description: Function that draws the button
********************************************************************************/
void CardButton::render(sf::RenderTarget* target)
{
	target->draw(image);
}

/********************************************************************************
** Name: void CardButton::resetPos()
** Description: Function to reset the button to it's original position
********************************************************************************/
void CardButton::resetPos()
{
	image.setPosition(pos);
}

/********************************************************************************
** Name: bool CardButton::isPressed()
** Description: Function that returns true if button is pressed
********************************************************************************/
bool CardButton::isPressed()
{
	if (buttonState == PRESSED) {
		return true;
	}
	return false;
}


/********************************************************************************
** Name: std::string CardButton::getName()
** Description: Function that returns the buttons name
********************************************************************************/
std::string CardButton::getName()
{
	return name;
}
