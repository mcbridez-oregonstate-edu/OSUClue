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

/************************************************************************************************
								Suggestion::Suggestion(sf::Font* font)
 * Description: The constructor for Suggestion
************************************************************************************************/
Suggestion::Suggestion(sf::Font* font)
{
	b_people = createButtonArray(0);
	b_weapons = createButtonArray(1);
	b_rooms = createButtonArray(2);
	suggestionText.setFont(*font);
	suspect = "NONE";
	weapon = "NONE";
	revealedCard = "NONE";
	revealedCardButton = nullptr;
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
	void Suggestion::chooseRevealCard(const sf::Vector2f mouse, string suspect, string weapon, string room, vector<Card> cards)
 * Description: Allows the revealing player to choose the card to reveal
****************************************************************************************************************/
void Suggestion::chooseRevealCard(const sf::Vector2f mouse, string suspect, string weapon, string room, vector<Card> cards)
{
	for (int i = 0; i < cards.size(); i++)
	{
		if (cards[i].getName() == suspect || cards[i].getName() == weapon || cards[i].getName() == room)
		{
			for (int j = 0; j < b_people.size(); j++)
			{
				if (b_people[j]->getName() == cards[i].getName())
				{
					suggestCards.push_back(b_people[j]);
				}
			}

			for (int j = 0; j < b_weapons.size(); j++)
			{
				if (b_weapons[j]->getName() == cards[i].getName())
				{
					suggestCards.push_back(b_weapons[j]);
				}
			}

			for (int j = 0; j < b_rooms.size(); j++)
			{
				if (b_rooms[j]->getName() == cards[i].getName())
				{
					suggestCards.push_back(b_rooms[j]);
				}
			}
		}
	}
	
	for (int i = 0; i < suggestCards.size(); i++)
	{
		suggestCards[i]->update(mouse);
		if (suggestCards[i]->isPressed())
		{
			revealedCard = suggestCards[i]->getName();
		}
	}
}

/************************************************************************************************
			void Suggestion::showRevealCard(string cardName, string revealingPlayer)
 * Description: Shows the revealed card to the suggesting player
************************************************************************************************/
void Suggestion::showRevealCard(string cardName, string revealingPlayer)
{
	suggestionText.setString(revealingPlayer + " reveals:\n Press Enter to continue...");
	for (int i = 0; i < b_people.size(); i++)
	{
		if (b_people[i]->getName() == cardName)
		{
			revealedCardButton = b_people[i];
		}
	}
	for (int i = 0; i < b_weapons.size(); i++)
	{
		if (b_weapons[i]->getName() == cardName)
		{
			revealedCardButton = b_weapons[i];
		}
	}
	for (int i = 0; i < b_rooms.size(); i++)
	{
		if (b_rooms[i]->getName() == cardName)
		{
			revealedCardButton = b_rooms[i];
		}
	}
	revealedCardButton->setButtonPos(sf::Vector2f(575, 340));
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
void Suggestion::renderRevealChoice(sf::RenderTarget* window)
{
	suggestionText.setString("Choose a card to reveal:");
	
	if (suggestCards.size() == 1)
	{
		suggestCards[0]->setButtonPos(sf::Vector2f(575, 140));
	}

	else if (suggestCards.size() == 2)
	{
		suggestCards[0]->setButtonPos(sf::Vector2f(475, 140));
		suggestCards[1]->setButtonPos(sf::Vector2f(675, 140));
	}

	else
	{
		suggestCards[0]->setButtonPos(sf::Vector2f(375, 140));
		suggestCards[1]->setButtonPos(sf::Vector2f(575, 140));
		suggestCards[2]->setButtonPos(sf::Vector2f(775, 140));
	}
	
	for (int i = 0; i < suggestCards.size(); i++)
	{
		suggestCards[i]->render(window);
	}

	window->draw(suggestionText);
}

/****************************************************************************************
					void Suggestion::renderReveal(sf::RenderTarget* window)
 * Description: Renders the objects for the card reveal in the target window
****************************************************************************************/
void Suggestion::renderReveal(sf::RenderTarget* window)
{
	window->draw(suggestionText);
	revealedCardButton->render(window);
}

/****************************************************************************************
									void Suggestion::reset()
 * Description: Resets the variables and positions of objects so that the next time
 * a suggestion is made, things don't get wonky.
****************************************************************************************/
void Suggestion::reset()
{
	suspect = "NONE";
	weapon = "NONE";
	revealedCard = "NONE";
	revealedCardButton = nullptr;

	for (int j = 0; j < b_people.size(); j++) 
	{
		b_people[j]->resetPos();
	}
	for (int j = 0; j < b_weapons.size(); j++) 
	{
		b_weapons[j]->resetPos();
	}
	for (int j = 0; j < b_rooms.size(); j++) 
	{
		b_rooms[j]->resetPos();
	}
}
