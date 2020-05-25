/*****************************************************************************
 * Program Name: SimpleButton.hpp
 * Date: 5/25/2020
 * Author: Abigail Minchella
 * Description: A class to make a simple text button. Sets the size of the 
 * rectangle to fit the size of the text. Based on CardButton by Adam Pham
*****************************************************************************/
#include "SimpleButton.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

/*****************************************************************************
	SimpleButton::SimpleButton(std::string text, sf::Vector2f targetPos)
 * Description: The constructor for the simple button class. Takes a string
 * for the label and a target position. Gets the dimensions of the box around
 * the text and makes the backing rectangle slightly bigger
*****************************************************************************/
SimpleButton::SimpleButton(std::string text, sf::Vector2f targetPos)
{
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) {
		std::cout << "Font not loaded" << std::endl;
	}

	buttonLabel.setFont(font);
	buttonLabel.setString(text);
	
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
	float buttonY = targetPos.y + 5;
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
	buttonState = IDLE;
	if (buttonBox.getGlobalBounds().contains(mousePos)) {
		buttonState = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = PRESSED;
		}
	}

	switch (buttonState) {
	case IDLE:
		buttonBox.setFillColor(sf::Color::Black);
		buttonLabel.setFillColor(sf::Color::White);
		break;
	case HOVER:
		buttonBox.setFillColor(boxHoverColor);
		buttonLabel.setFillColor(textHoverColor);
		break;
	default:
		// turn green on click
		buttonBox.setFillColor(sf::Color(36, 94, 36, 255));
		break;
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
