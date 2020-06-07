/********************************************************************************************
 * Program Name: Accusation.cpp
 * Date: 6/7/20
 * Author: Abigail Minchella
 * Description: Handles the objects for accusations. A child of the Suggestion class (since 
 * they use similar functionality
********************************************************************************************/
#include "Accusation.hpp"

/********************************************************************************************
					Accusation::Accusation(sf::Font* font) : Suggestion(font)
 * Description: The constructor for Accusation, uses Suggestion to instantiate the objects
********************************************************************************************/
Accusation::Accusation(sf::Font* font) : Suggestion(font), yes("Yes", 
	sf::Vector2f(450, 500), 70), no("No", sf::Vector2f(750, 500), 70)
{
	suggestionText.setString("Making a false accusation will end the game for you.\n         Are you sure you want to proceed?");
	suggestionText.setPosition(sf::Vector2f(100, 200));
	suggestionText.setCharacterSize(75);

	room = "NONE";
}

/********************************************************************************************
					void Accusation::renderConfirmation(sf::RenderTarget* window)
 * Description: Renders the objects for the confirmation screen in the target window
********************************************************************************************/
void Accusation::renderConfirmation(sf::RenderTarget* window)
{
	window->draw(suggestionText);
	yes.render(window);
	no.render(window);
}

/********************************************************************************************
					void Accusation::updateButtons(const sf::Vector2f mouse)
 * Description: Updates the buttons based on mouse position
********************************************************************************************/
void Accusation::updateButtons(const sf::Vector2f mouse)
{
	yes.update(mouse);
	no.update(mouse);
}

/********************************************************************************************
								bool Accusation::yesPressed()
 * Description: Returns true if yes pressed
********************************************************************************************/
bool Accusation::yesPressed()
{
	return yes.isPressed();
}

/********************************************************************************************
							bool Accusation::noPressed()
 * Description: Returns true if no pressed
********************************************************************************************/
bool Accusation::noPressed()
{
	return no.isPressed();
}

/********************************************************************************************
				void Accusation::suggestRoom(const sf::Vector2f mouse)
 * Description: Gets the room suggested by the player
********************************************************************************************/
void Accusation::suggestRoom(const sf::Vector2f mouse)
{
	for (int i = 0; i < b_rooms.size(); i++)
	{
		b_rooms[i]->update(mouse);
		if (b_rooms[i]->isPressed())
		{
			room = b_rooms[i]->getName();
		}
	}
}

/************************************************************************************************
									string Accusation::getRoom()
 * Description: Returns the room chosen by the player
************************************************************************************************/
string Accusation::getRoom()
{
	return room;
}

/************************************************************************************************
						void Accusation::renderSuspects(sf::RenderTarget* window)
 * Description: Renders the accusation buttons to the target window (overrides the inherited
 * function from Suggestion to make the text accurate
************************************************************************************************/
void Accusation::renderSuspects(sf::RenderTarget* window)
{
	suggestionText.setCharacterSize(40);
	suggestionText.setPosition(sf::Vector2f(350, 25));
	suggestionText.setString("Accusation: Choose a Suspect and press Enter");
	window->draw(suggestionText);
	for (int i = 0; i < b_people.size(); i++)
	{
		b_people[i]->resetPos();
		b_people[i]->render(window);
	}
}

/************************************************************************************************
					void Accusation::renderWeapons(sf::RenderTarget* window)
 * Description: Renders the accusation buttons to the target window
************************************************************************************************/
void Accusation::renderWeapons(sf::RenderTarget* window)
{
	suggestionText.setCharacterSize(40);
	suggestionText.setPosition(sf::Vector2f(350, 25));
	suggestionText.setString("Accusation: Choose a Weapon and press Enter");
	window->draw(suggestionText);
	for (int i = 0; i < b_weapons.size(); i++)
	{
		b_weapons[i]->resetPos();
		b_weapons[i]->render(window);
	}
}

/************************************************************************************************
					void Accusation::renderRooms(sf::RenderTarget* window)
 * Description: Renders the accusation buttons to the target window
************************************************************************************************/
void Accusation::renderRooms(sf::RenderTarget* window)
{
	suggestionText.setCharacterSize(40);
	suggestionText.setPosition(sf::Vector2f(350, 25));
	suggestionText.setString("Accusation: Choose a Room and press Enter");
	window->draw(suggestionText);
	for (int i = 0; i < b_rooms.size(); i++)
	{
		b_rooms[i]->resetPos();
		b_rooms[i]->render(window);
	}
}

/************************************************************************************************
					void Accusation::renderRooms(sf::RenderTarget* window)
 * Description: Renders the player's accusation to the target window
************************************************************************************************/
void Accusation::renderSuggestion(sf::RenderTarget* window)
{
	suggestionText.setString("You have Accused: (Press 'Enter' to continue . . .)");
	window->draw(suggestionText);
	int suspectNum = -1;
	int weaponNum = -1;
	int roomNum = -1;

	for (int i = 0; i < b_people.size(); i++)
	{
		if (b_people[i]->getName() == suspect)
		{
			suspectNum = i;
		}
	}
	for (int i = 0; i < b_weapons.size(); i++)
	{
		if (b_weapons[i]->getName() == weapon)
		{
			weaponNum = i;
		}
	}
	for (int i = 0; i < b_rooms.size(); i++)
	{
		if (b_rooms[i]->getName() == room)
		{
			roomNum = i;
		}
	}

	b_people[suspectNum]->setButtonPos(sf::Vector2f(375, 140));
	b_people[suspectNum]->setIdle();
	b_people[suspectNum]->render(window);

	b_weapons[weaponNum]->setButtonPos(sf::Vector2f(575, 140));
	b_weapons[weaponNum]->setIdle();
	b_weapons[weaponNum]->render(window);

	b_rooms[roomNum]->setButtonPos(sf::Vector2f(775, 140));
	b_rooms[roomNum]->setIdle();
	b_rooms[roomNum]->render(window);
}
