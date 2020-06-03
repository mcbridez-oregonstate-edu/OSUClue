/************************************************************************************************
 * Program Name: Suggestion.hpp
 * Date: 6/3/20
 * Author: Adam Pham (with modifications by Abigail Minchella)
 * Description: The header file for the Suggestion class.
************************************************************************************************/
#include "Suggestion.hpp"
#include <iostream>
using std::cout;
using std::endl;

Suggestion::Suggestion(sf::Font* font)
{
	b_people = createButtonArray(0);
	b_weapons = createButtonArray(1);
	b_rooms = createButtonArray(2);
	suggestionText.setFont(*font);
	suspect = "NONE";
	weapon = "NONE";
	revealedCard = "NONE";
}

/***********************************************************************************************
						void Suggestion::suggestSuspect(const sf::Vector2f mouse)
 * Description: Gets the suspect suggested by the player
***********************************************************************************************/
void Suggestion::suggestSuspect(const sf::Vector2f mouse)
{
	for (int i = 0; i < b_people.size(); i++)
	{
		b_people[i]->update(mouse);
		if (b_people[i]->isPressed())
		{
			suspect = b_people[i]->getName();
		}
	}
}

/***********************************************************************************************
						void Suggestion::suggestWeapon(const sf::Vector2f mouse)
 * Description: Returns the weapon suggested by the player
***********************************************************************************************/
void Suggestion::suggestWeapon(const sf::Vector2f mouse)
{
	for (int i = 0; i < b_weapons.size(); i++) 
	{
		b_weapons[i]->update(mouse);
		if (b_weapons[i]->isPressed())
		{
			weapon = b_weapons[i]->getName();
		}
	}
}

/****************************************************************************************************************
	void Suggestion::chooseRevealCard(const sf::Vector2f mouse, string suspect, string weapon, string room)
 * Description: Returns the weapon suggested by the player
****************************************************************************************************************/
void Suggestion::chooseRevealCard(const sf::Vector2f mouse, string suspect, string weapon, string room)
{
	for (int i = 0; i < b_people.size(); i++) 
	{
		if (b_people[i]->getName() == suspect) 
		{
			b_people[i]->update(mouse);
			if (b_people[i]->isPressed()) 
			{
				revealedCard = b_people[i]->getName();
			}
		}
	}
	for (int i = 0; i < b_weapons.size(); i++) 
	{
		if (b_weapons[i]->getName() == weapon) 
		{
			b_weapons[i]->update(mouse);
			if (b_weapons[i]->isPressed()) 
			{
				revealedCard = b_weapons[i]->getName();
			}
		}
	}
	for (int i = 0; i < b_rooms.size(); i++) 
	{
		if (b_rooms[i]->getName() == room) 
		{
			b_rooms[i]->update(mouse);
			if (b_rooms[i]->isPressed()) 
			{
				revealedCard = b_rooms[i]->getName();
			}
		}
	}
}

/************************************************************************************************
								string Suggestion::getSuspect()
 * Description: Returns the suspect suggested by the player
************************************************************************************************/
string Suggestion::getSuspect()
{
	return suspect;
}

/************************************************************************************************
								string Suggestion::getWeapon()
 * Description: Returns the weapon suggested by the player
************************************************************************************************/
string Suggestion::getWeapon()
{
	return weapon;
}

/************************************************************************************************
								string Suggestion::getRevealCard()
 * Description: Returns the card chosen to be revealed by the player
************************************************************************************************/
string Suggestion::getRevealCard()
{
	return revealedCard;
}

/************************************************************************************************
	void Suggestion::renderSuspects(sf::RenderTarget* window, const sf::Vector2f mouse)
 * Description: Renders the suggestion buttons to the target window
************************************************************************************************/
void Suggestion::renderSuspects(sf::RenderTarget* window)
{
	suggestionText.setString("Suggestion: Choose a Suspect and press Enter");
	window->draw(suggestionText);
	for (int i = 0; i < b_people.size(); i++) 
	{
		b_people[i]->resetPos();
		b_people[i]->render(window);
	}
}

/************************************************************************************************
	void Suggestion::renderWeapons(sf::RenderTarget* window, const sf::Vector2f mouse)
 * Description: Renders the suggestion buttons to the target window
************************************************************************************************/
void Suggestion::renderWeapons(sf::RenderTarget* window)
{
	suggestionText.setString("Suggestion: Choose a Weapon and press Enter");
	window->draw(suggestionText);
	for (int i = 0; i < b_weapons.size(); i++) 
	{
		b_weapons[i]->resetPos();
		b_weapons[i]->render(window);
	}
}

/*************************************************************************************************************
	void Suggestion::renderSuggestion(sf::RenderTarget* window, string suspect, string weapon, string room)
 * Description: Renders the player's suggestion to the target window
*************************************************************************************************************/
void Suggestion::renderSuggestion(sf::RenderTarget* window, string suspect, string weapon, string room)
{
	suggestionText.setString("You have Suggested:\nPress 'Enter' to continue . . .");
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
	b_rooms[roomNum]->render(window);
}

/*************************************************************************************************************
	void Suggestion::renderRevealChoice(sf::RenderTarget* window, string suspect, string weapon, string room)
 * Description: Renders the buttons for the revealing player to choose their reveal with
*************************************************************************************************************/
void Suggestion::renderRevealChoice(sf::RenderTarget* window, string suspect, string weapon, string room)
{
	suggestionText.setString("Choose a card to reveal:");
	for (int j = 0; j < b_people.size(); j++) 
	{
		if (b_people[j]->getName() == suspect) 
		{
			b_people[j]->setButtonPos(sf::Vector2f(375, 140));
			b_people[j]->render(window);
		}
	}
	for (int k = 0; k < b_weapons.size(); k++) 
	{
		if (b_weapons[k]->getName() == weapon) 
		{
			b_weapons[k]->setButtonPos(sf::Vector2f(575, 140));
			b_weapons[k]->render(window);
		}
	}
	for (int h = 0; h < b_rooms.size(); h++) 
	{
		if (b_rooms[h]->getName() == room) 
		{
			b_rooms[h]->setButtonPos(sf::Vector2f(775, 140));
			b_rooms[h]->render(window);
		}
	}
	window->draw(suggestionText);
}
