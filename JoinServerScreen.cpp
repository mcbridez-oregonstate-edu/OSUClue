/******************************************************************************
 * Program Name: JoinServerScreen.cpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: Manages the objects for the Join Server screen
******************************************************************************/
#include "JoinServerScreen.hpp"

/******************************************************************************
				JoinServerScreen::JoinServerScreen(sf::Font* font)
 * Description: The constructor for the joinServerScreen class. Sets up all
 * the objects used
******************************************************************************/
JoinServerScreen::JoinServerScreen(sf::Font* font) : back("Back", sf::Vector2f(750, 700), 75), proceed("Continue", sf::Vector2f(400, 700), 75)
{
	texture.loadFromFile("res/images/logo.jpg");
	logo.setTexture(texture);
	logo.setColor(sf::Color(255, 255, 255));
	logo.setPosition(sf::Vector2f(250, 150));
	logo.setScale(4, 4);

	clientInstructions.setFont(*font);
	clientInstructions.setCharacterSize(60);
	clientInstructions.setString("Please enter the IP address of the server you want to join\n        and press Enter (this may take a few seconds):");
	clientInstructions.setPosition(sf::Vector2f(90, 450));

	inputDisplay.setFont(*font);
	inputDisplay.setCharacterSize(60);
	inputDisplay.setPosition(sf::Vector2f(500, 580));

	proceed.disable();
}

/*******************************************************************************
		void JoinServerScreen::updateButtons(const sf::Vector2f mouse)
 * Description: Updates the buttons based on the actions of the mouse
*******************************************************************************/
void JoinServerScreen::updateButtons(const sf::Vector2f mouse)
{
	proceed.update(mouse);
	back.update(mouse);
}

/*******************************************************************************
				void JoinServerScreen::getUserInput(sf::Event* event)
 * Description: Gets and manages the user input from the event pointer. Handles
 * backspaces and only allows valid IP characters (i.e. numbers and periods).
*******************************************************************************/
void JoinServerScreen::getUserInput(sf::Event* event)
{
	// Check for backspace and erase last entered character
	if (event->text.unicode == 8 && input.getSize() > 0)
	{
		input.erase(input.getSize() - 1, 1);
		inputDisplay.setString(input);
	}

	// Check if entered character is either a number or a period
	else if ((event->text.unicode <= 57 && event->text.unicode >= 48) || event->text.unicode == 46)
	{
		if (input.getSize() < 15)
		{
			input += event->text.unicode;
			inputDisplay.setString(input);
		}
	}
}

/*******************************************************************************
						sf::String JoinServerScreen::getIP()
 * Description: Returns the input string that the user had been writing to
*******************************************************************************/
sf::String JoinServerScreen::getIP()
{
	return input;
}

/*********************************************************************************
						bool JoinServerScreen::proceedPressed()
 * Description: Returns true if the proceed button was pressed
*********************************************************************************/
bool JoinServerScreen::proceedPressed()
{
	return proceed.isPressed();
}

/*********************************************************************************
						bool JoinServerScreen::backPressed()
 * Description: Returns true if the back button was pressed
*********************************************************************************/
bool JoinServerScreen::backPressed()
{
	return back.isPressed();
}

/*********************************************************************************
						void JoinServerScreen::clientCreated()
 * Description: Updates the instructions and buttons to reflect that the client
 * creation was successful
*********************************************************************************/
void JoinServerScreen::clientCreated()
{
	proceed.enable();
	clientInstructions.setString("Connected to server! Press Continue to proceed");
	clientInstructions.setPosition(sf::Vector2f(200, 500));
	input.clear();
	inputDisplay.setString(input);
}

/*********************************************************************************
						void JoinServerScreen::clientNotCreated()
 * Description: Updates the instructions and buttons to reflect that the client
 * creation was NOT successful
*********************************************************************************/
void JoinServerScreen::clientNotCreated()
{
	clientInstructions.setString("Server IP invalid. Please enter a valid IP:");
	clientInstructions.setPosition(sf::Vector2f(275, 450));
	input.clear();
	inputDisplay.setString(input);
}

/*********************************************************************************
				void JoinServerScreen::render(sf::RenderTarget* window)
 * Description: Renders the objects for the join server screen in the target
 * window
*********************************************************************************/
void JoinServerScreen::render(sf::RenderTarget* window)
{
	window->draw(logo);
	proceed.render(window);
	back.render(window);
	window->draw(clientInstructions);
	window->draw(inputDisplay);
}
