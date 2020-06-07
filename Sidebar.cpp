/*****************************************************************************************
 * Program Name: Sidebar.hpp
 * Date: 6/6/20
 * Author: Abigail Minchella
 * Description: Creates the sidebar for the player that houses their info and available
 * actions
*****************************************************************************************/
#include "Sidebar.hpp"

/*****************************************************************************************
			Sidebar::Sidebar(sf::Font* font, string playerName, string characterName)
 * Description: The constructor for the Sidebar. Sets up all the objects.
*****************************************************************************************/
Sidebar::Sidebar(sf::Font* font, string name, string characterName) : accuse("Make an Accusation", sf::Vector2f(40, 400), 35),
	endTurn("End Turn", sf::Vector2f(50, 475), 35), 
	secretPassage("Use Secret Passage", sf::Vector2f(40, 550), 35)
{
	if (characterName == "Miss Scarlet") {
		characterTexture.loadFromFile("res/images/characters/scarlet.png");
	}
	else if (characterName == "Mr. Green") {
		characterTexture.loadFromFile("res/images/characters/green.png");
	}
	else if (characterName == "Colonel Mustard") {
		characterTexture.loadFromFile("res/images/characters/mustard.png");
	}
	else if (characterName == "Mrs. White") {
		characterTexture.loadFromFile("res/images/characters/white.png");
	}
	else if (characterName == "Mrs. Peacock") {
		characterTexture.loadFromFile("res/images/characters/peacock.png");
	}
	else if (characterName == "Professor Plum")
	{
		characterTexture.loadFromFile("res/images/characters/plum.png");
	}

	characterImage.setTexture(characterTexture);
	characterImage.setScale(.75, .75);
	characterImage.setPosition(sf::Vector2f(50, 50));

	playerName.setFont(*font);
	playerName.setString(name);
	playerName.setCharacterSize(40);
	playerName.setPosition(sf::Vector2f(50, 325));
	secretPassage.disable();
	endTurn.disable();
}

/*****************************************************************************************
						void Sidebar::updateButtons(const sf::Vector2f mouse)
 * Description: Updates the buttons based on the mouse position
*****************************************************************************************/
void Sidebar::updateButtons(const sf::Vector2f mouse)
{
	accuse.update(mouse);
	secretPassage.update(mouse);
	endTurn.update(mouse);
}

/*****************************************************************************************
						void Sidebar::render(sf::RenderTarget* window)
 * Description: Renders the sidebar objects in the target window
*****************************************************************************************/
void Sidebar::render(sf::RenderTarget* window)
{
	window->draw(characterImage);
	window->draw(playerName);
	accuse.render(window);
	secretPassage.render(window);
	endTurn.render(window);
}

/*****************************************************************************************
						void Sidebar::enablePassage(bool canUsePassage)
 * Description: Enables the secret passage button based on the bool value
*****************************************************************************************/
void Sidebar::enablePassage(bool canUsePassage)
{
	if (canUsePassage)
	{
		secretPassage.enable();
	}
	else
	{
		secretPassage.disable();
	}
}

/*****************************************************************************************
						void Sidebar::enableEndTurn(int steps, bool isTurn)
 * Description: Enables the end turn button if the number of steps is 0 and it is the 
 * player's turn
*****************************************************************************************/
void Sidebar::enableEndTurn(int steps, bool isTurn)
{
	if (steps == 0 && isTurn)
	{
		endTurn.enable();
	}
}

/*********************************************************************************************
								void Sidebar::disableButtons(bool isTurn)
 * Description: Disables the buttons if it is not the player's turn
*********************************************************************************************/
void Sidebar::disableButtons(bool isTurn)
{
	if (!isTurn)
	{
		endTurn.disable();
		secretPassage.disable();
		accuse.disable();
	}
	else
	{
		accuse.enable();
	}
}

/*********************************************************************************************
									bool Sidebar::accusePressed()
 * Description: Returns true if accuse has been pressed
*********************************************************************************************/
bool Sidebar::accusePressed()
{
	return accuse.isPressed();
}

/*********************************************************************************************
									bool Sidebar::passagePressed()
 * Description: Returns true if secretPassage has been pressed
*********************************************************************************************/
bool Sidebar::passagePressed()
{
	return secretPassage.isPressed();
}

/*********************************************************************************************
									bool Sidebar::endTurnPressed()
 * Description: Returns true endTurn has been pressed
*********************************************************************************************/
bool Sidebar::endTurnPressed()
{
	return endTurn.isPressed();
}

/*********************************************************************************************
									void Sidebar::resetAccuse()
 * Description: Resets the accuse button to IDLE so that it can be pressed again
*********************************************************************************************/
void Sidebar::resetAccuse()
{
	accuse.setIdle();
}
