/****************************************************************************
 * Program Name: CharacterButton.cpp
 * Date: 5/25/2020
 * Author: Abigail Minchella (heavily adapted from CardButton by Adam Pham)
 * Description: Creates buttons for the character selection screen
****************************************************************************/
#include "CharacterButton.hpp"

/********************************************************************************
** CharacterButton::CharacterButton(std::string characterName, sf::Vector2f b_pos)
** Description: Constructor for the character class. Takes a string of the name
**				of the character to be made into a button
********************************************************************************/
CharacterButton::CharacterButton(std::string characterName, sf::Vector2f b_pos)
{
	if (characterName == "Miss Scarlet") {
		texture.loadFromFile("res/images/characters/scarlet.png");
	}
	else if (characterName == "Mr. Green") {
		texture.loadFromFile("res/images/characters/green.png");
	}
	else if (characterName == "Colonel Mustard") {
		texture.loadFromFile("res/images/characters/mustard.png");
	}
	else if (characterName == "Mrs. White") {
		texture.loadFromFile("res/images/characters/white.png");
	}
	else if (characterName == "Mrs. Peacock") {
		texture.loadFromFile("res/images/characters/peacock.png");
	}
	else if (characterName == "Professor Plum")
	{
		texture.loadFromFile("res/images/characters/plum.png");
	}

	image.setTexture(texture);
	image.move(b_pos);
	pos = b_pos;
	hoverColor = sf::Color(255, 255, 255, 128);
	buttonState = IDLE;
	name = characterName;
}


/********************************************************************************
** Name: void CharacterButton::setButtonPos(sf::Vector2f targetpos)
** Description: Function to set the position of the button.
********************************************************************************/
void CharacterButton::setButtonPos(sf::Vector2f targetpos)
{
	image.setPosition(targetpos);
}

/********************************************************************************
** Name: void CharacterButton::update(sf::Vector2f mousePos)
** Description: Function that updates the button when hovered and pressed
********************************************************************************/
void CharacterButton::update(const sf::Vector2f mousePos)
{
	if (buttonState == DISABLED)
	{
		image.setColor(sf::Color(160, 160, 160, 100));
	}
	else
	{
		buttonState = IDLE;

		if (image.getGlobalBounds().contains(mousePos)) {
			buttonState = HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				buttonState = PRESSED;
			}
		}

		switch (buttonState) 
		{
			case IDLE:
			{
				// set color to original
				image.setColor(sf::Color(255, 255, 255));
				break;
			}
			case HOVER:
			{
				image.setColor(hoverColor);
				break;
			}
			default:
			{
				// turn white on click
				image.setColor(sf::Color(255, 255, 255, 200));
				break;
			}
		}
	}
}

/********************************************************************************
** Name: void CharacterButton::render(sf::RenderTarget* target)
** Description: Function that draws the button
********************************************************************************/
void CharacterButton::render(sf::RenderTarget* target)
{
	target->draw(image);
}

/********************************************************************************
** Name: void CharacterButton::resetPos()
** Description: Function to reset the button to it's original position
********************************************************************************/
void CharacterButton::resetPos()
{
	image.setPosition(pos);
}

/********************************************************************************
** Name: bool CharacterButton::isPressed()
** Description: Function that returns true if button is pressed
********************************************************************************/
bool CharacterButton::isPressed()
{
	if (buttonState == PRESSED) {
		return true;
	}
	return false;
}

/********************************************************************************
** Name: std::string CharacterButton::getName()
** Description: Function that returns the buttons name
********************************************************************************/
std::string CharacterButton::getName()
{
	return name;
}

/********************************************************************************
						void CharacterButton::setDisabled()
 * Description: Sets the button state to disabled, deactivating it from being
 * clicked on.
********************************************************************************/
void CharacterButton::setDisabled()
{
	buttonState = DISABLED;
}
