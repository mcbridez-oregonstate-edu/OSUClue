/******************************************************************************************
 * Program Name: SimpleButton.hpp
 * Date: 5/25/2020
 * Author: Abigail Minchella
 * Description: A class to make a simple text button. Sets the size of the 
 * rectangle to fit the size of the text. Based on CardButton by Adam Pham
******************************************************************************************/
#include "SimpleButton.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

/******************************************************************************************
	SimpleButton::SimpleButton(std::string text, sf::Vector2f targetPos, int textSize)
 * Description: The constructor for the simple button class. Takes a string
 * for the label, a target position, and an int for the text size. Gets the dimensions of 
 * the box around the text and makes the backing rectangle slightly bigger
******************************************************************************************/
SimpleButton::SimpleButton(std::string text, sf::Vector2f targetPos, int textSize)
{
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) 
	{
		std::cout << "Font not loaded" << std::endl;
	}

	buttonLabel.setFont(font);
	buttonLabel.setString(text);
	fontSize = textSize;
	buttonLabel.setCharacterSize(fontSize);

	sf::FloatRect textbox = buttonLabel.getLocalBounds();
	float textWidth = textbox.width;
	float textHeight = textbox.height;

	pos = targetPos;

	// Add padding for the rectangle
	textWidth += 20;
	textHeight += 20;
	buttonBox.setSize(sf::Vector2f(textWidth, textHeight));
	buttonBox.setOutlineColor(sf::Color::White);
	buttonBox.setFillColor(sf::Color::Black);
	buttonBox.setOutlineThickness(5);
	buttonBox.setPosition(targetPos);

	// Set the position of the text to account for the offset
	// of the rectangle padding
	float buttonX = targetPos.x + 10;

	// Set the height offset based on the size of the font
	int heightOffset = 0;
	if (fontSize < 35)
	{
		heightOffset = 7;
	}
	else if (fontSize >= 35 && fontSize < 50)
	{
		heightOffset = 0;
	}
	else if (fontSize >= 50 && fontSize < 75)
	{
		heightOffset = -7;
	}
	else
	{
		heightOffset = -17;
	}

	float buttonY = targetPos.y + heightOffset;
	buttonLabel.setPosition(sf::Vector2f(buttonX, buttonY));

	boxHoverColor = sf::Color::White;
	textHoverColor = sf::Color::Black;
	buttonState = IDLE;
}

/*****************************************************************************
			void SimpleButton::setButtonPos(sf::Vector2f targetPos)
 * Description: Takes the position where the button is to be moved. Puts the
 * box at that position and offsets the label to maintain padding.
*****************************************************************************/
void SimpleButton::setButtonPos(sf::Vector2f targetPos)
{
	buttonBox.setPosition(targetPos);
	float buttonX = targetPos.x + 5;
	float buttonY = targetPos.y + 5;
	buttonLabel.setPosition(sf::Vector2f(buttonX, buttonY));
}

/******************************************************************************
			void SimpleButton::update(const sf::Vector2f mousePos)
 * Description: Updates the box based on the position of the mouse and whether
 * or not the button has been clicked.
******************************************************************************/
void SimpleButton::update(const sf::Vector2f mousePos)
{
	if (buttonState == DISABLED)
	{
		buttonBox.setOutlineColor(sf::Color(160, 160, 160, 100));
		buttonLabel.setFillColor(sf::Color(160, 160, 160, 100));
	}
	else
	{
		buttonState = IDLE;

		if (buttonBox.getGlobalBounds().contains(mousePos)) 
		{
			buttonState = HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
			{
				buttonState = PRESSED;
			}
		}

		switch (buttonState)
		{
			case IDLE:
			{
				// set color to original
				buttonBox.setFillColor(sf::Color::Black);
				buttonBox.setOutlineColor(sf::Color::White);
				buttonLabel.setFillColor(sf::Color::White);
				break;
			}
			case HOVER:
			{
				buttonBox.setFillColor(boxHoverColor);
				buttonLabel.setFillColor(textHoverColor);
				break;
			}
			default:
			{
				// turn white on click
				buttonBox.setFillColor(sf::Color(36, 94, 36, 255));
				break;
			}
		}
	}
}

/**************************************************************************
			void SimpleButton::render(sf::RenderTarget* target)
 * Description: Renders the button in the target window
**************************************************************************/
void SimpleButton::render(sf::RenderTarget* target)
{
	target->draw(buttonBox);
	target->draw(buttonLabel);
}

/**************************************************************************
						void SimpleButton::disable()
 * Description: Sets the button state to disabled, disallowing it from 
 * being clicked on and graying it out
**************************************************************************/
void SimpleButton::disable()
{
	if (buttonState != DISABLED)
	{
		buttonState = DISABLED;
	}
}

/**************************************************************************
						void SimpleButton::enable()
 * Description: Reenables the button if it was previously disabled, 
 * allowing it to be clicked on
**************************************************************************/
void SimpleButton::enable()
{
	if (buttonState == DISABLED)
	{
		buttonState = IDLE;
	}
}

/**************************************************************************
						bool SimpleButton::isPressed()
 * Description: Returns true if the button state is pressed, false if not
**************************************************************************/
bool SimpleButton::isPressed()
{
	if (buttonState == PRESSED) {
		return true;
	}
	return false;
}
