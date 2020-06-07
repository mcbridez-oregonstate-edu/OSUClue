/**********************************************************************************
 * Program Name: CharacterSelectScreen.hpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: Manages the objects for the character select screen
**********************************************************************************/
#include "CharacterSelectScreen.hpp"

/**********************************************************************************
			CharacterSelectScreen::CharacterSelectScreen(sf::Font* font)
 * Description: The constructor for the character select screen. Initializes and
 * properly positions the objects needed for this screen
**********************************************************************************/
CharacterSelectScreen::CharacterSelectScreen(sf::Font* font)
{
	texture.loadFromFile("res/images/logo.jpg");
	logo.setTexture(texture);
	logo.setColor(sf::Color(255, 255, 255));
	logo.setPosition(sf::Vector2f(250, 150));
	logo.setScale(4, 4);

	inputDisplay.setFont(*font);
	inputDisplay.setCharacterSize(60);
	inputDisplay.setPosition(sf::Vector2f(500, 580));

	info.setFont(*font);
	info.setCharacterSize(75);
	info.setPosition(sf::Vector2f(100, 500));
	info.setString("Enter a name you would like to be known by:");

	players.setFont(*font);
	players.setCharacterSize(50);
	players.setPosition(sf::Vector2f(150, 200));
}

/**********************************************************************************
					string CharacterSelectScreen::getPlayers()
 * Description: Returns the string of players that have joined the game
**********************************************************************************/
string CharacterSelectScreen::getPlayers()
{
	return players.getString();
}

/**********************************************************************************
				void CharacterSelectScreen::setPlayers(string text)
 * Description: Sets the players text to whatever has been passed in
**********************************************************************************/
void CharacterSelectScreen::setPlayers(string text)
{
	players.setString(text);
}

/**********************************************************************************
	void CharacterSelectScreen::disableCharacters(string taken, const sf::Vector2f mouse)
 * Description: Disables the character buttons based on whichever one matches
 * the passed string
**********************************************************************************/
void CharacterSelectScreen::disableCharacters(string taken, const sf::Vector2f mouse)
{
	for (int i = 0; i < 6; i++)
	{
		if (characters[i].getName() == taken)
		{
			characters[i].setDisabled();
			characters[i].update(mouse);
		}
	}
}

/***********************************************************************************
		void CharacterSelectScreen::updateCharacters(const sf::Vector2f mouse)
 * Description: Updates the character buttons based on the actions of the mouse
***********************************************************************************/
void CharacterSelectScreen::updateCharacters(const sf::Vector2f mouse)
{
	for (int i = 0; i < 6; i++)
	{
		characters[i].update(mouse);
	}
}

/************************************************************************************
				void CharacterSelectScreen::getUserInput(sf::Event* event)
 * Description: Gets/handles user input based on the data from the event
************************************************************************************/
void CharacterSelectScreen::getUserInput(sf::Event* event)
{
	if (event->text.unicode == 8 && input.getSize() > 0)
	{
		input.erase(input.getSize() - 1, 1);
		inputDisplay.setString(input);
	}
	else if (input.getSize() < 16)
	{
		input += event->text.unicode;
		inputDisplay.setString(input);
	}
}

/************************************************************************************
						string CharacterSelectScreen::getName()
 * Description: Returns the name input by the user
************************************************************************************/
string CharacterSelectScreen::getName()
{
	return input;
}

/************************************************************************************
					void CharacterSelectScreen::nameEntered()
 * Description: Updates the info on the screen when the name has been entered
************************************************************************************/
void CharacterSelectScreen::nameEntered()
{
	info.setString("Choose your character:");
	info.setPosition(sf::Vector2f(350, 5));
}

/************************************************************************************
					string CharacterSelectScreen::characterPressed()
 * Description: Checks to see if any of the character buttons have been pressed
 * and returns the name of the character if pressed. Otherwise, returns ""
************************************************************************************/
string CharacterSelectScreen::characterPressed()
{
	for (int i = 0; i < 6; i++)
	{
		if (characters[i].isPressed())
		{
			info.setString("Waiting for other players...");
			return characters[i].getName();
		}
	}

	return "";
}

/*************************************************************************************
		void CharacterSelectScreen::renderCharacters(sf::RenderTarget* window)
 * Description: Renders the character buttons to the target window
*************************************************************************************/
void CharacterSelectScreen::renderCharacters(sf::RenderTarget* window)
{
	for (int i = 0; i < 6; i++)
	{
		characters[i].render(window);
	}
	window->draw(info);
}

/*************************************************************************************
		void CharacterSelectScreen::renderPlayers(sf::RenderTarget* window)
 * Description: Renders the list of joined players to the target window
*************************************************************************************/
void CharacterSelectScreen::renderPlayers(sf::RenderTarget* window)
{
	window->draw(players);
	window->draw(info);
}

/*************************************************************************************
		void CharacterSelectScreen::renderGetInput(sf::RenderTarget* window)
 * Description: Renders the "enter name" screen to the target window
*************************************************************************************/
void CharacterSelectScreen::renderGetInput(sf::RenderTarget* window)
{
	window->draw(logo);
	window->draw(inputDisplay);
	window->draw(info);
}
