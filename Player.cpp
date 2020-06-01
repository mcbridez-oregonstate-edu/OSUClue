/********************************************************************************
** Created by: Devin Mourrain
** Suggestion function by: Abigail Minchella
** Date: 4/17/2020
** Description: This is the implementation of the Player class. See "Player.hpp"
				for a full list of the Player's attributes.
********************************************************************************/

#include "Player.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <time.h>
#include <cstdlib>
#include <limits>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::srand;
using std::rand;

//The default constructor for the player class; not sure how/if this will be used
Player::Player()
{
	this->name = "N/A";
}

//An overloaded constructor for the Player class to set its attributes
Player::Player(std::string name, token* playerToken)
{
	this->name = name;
	this->playerToken = playerToken;

	// -1 is empty, 0 is an "No", and 1 is a "Yes"; The initial layout is all empty
	std::vector<std::vector<int>> initialNotebook{	{-1, -1, -1, -1, -1},			//Green
													{-1, -1, -1, -1, -1},			//Mustard
													{-1, -1, -1, -1, -1},			//Peacock
													{-1, -1, -1, -1, -1},			//Plum
													{-1, -1, -1, -1, -1},			//Scarlet
													{-1, -1, -1, -1, -1},			//White
													{-1, -1, -1, -1, -1},			//Candlestick
													{-1, -1, -1, -1, -1},			//Knife
													{-1, -1, -1, -1, -1},			//Revolver
													{-1, -1, -1, -1, -1},			//Lead Pipe
													{-1, -1, -1, -1, -1},			//Rope
													{-1, -1, -1, -1, -1},			//Wrench
													{-1, -1, -1, -1, -1},			//Conservatory
													{-1, -1, -1, -1, -1},			//Ballroom
													{-1, -1, -1, -1, -1},			//Kitchen
													{-1, -1, -1, -1, -1},			//Dining Room
													{-1, -1, -1, -1, -1},			//Lounge
													{-1, -1, -1, -1, -1},			//Hall
													{-1, -1, -1, -1, -1},			//Study
													{-1, -1, -1, -1, -1},			//Library
													{-1, -1, -1, -1, -1},			//Billiard Room
	};
	this->notebook = initialNotebook;

	cardTextures.push_back(card1texture);
	cardTextures.push_back(card2texture);
	cardTextures.push_back(card3texture);

	cardSprites.push_back(card1sprite);
	cardSprites.push_back(card2sprite);
	cardSprites.push_back(card3sprite);
}

//Gets the player's name
std::string Player::getName()
{
	return this->name;
}

//Gets the player's token (represented as a number)
token* Player::getToken()
{
	return this->playerToken;
}

//Gets the player's token (represented as text)
//If the token isn't set or is another unexpected value, returns "Unknown Character"
std::string Player::getTokenName()
{
	return playerToken->getName();
}

//Removes the first instance of a card from a player's hand given its name
void Player::removeCard(std::string cardName)
{
	for (std::size_t i = 0; i < this->hand.size(); i++) {
		if (this->hand.at(i).getName() == cardName) {
			this->hand.erase(this->hand.begin() + i);
			break;
		}
	}
}

//Adds a specific card to hand
void Player::addCard(Card card)
{
	this->hand.push_back(card);
	string name = card.getName();
	
	// load textures for card images
	if (name == "Miss Scarlet") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/suspects/scarlett.jpg");
	}
	else if (name == "Mr. Green") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/suspects/green.jpg");
	}
	else if (name == "Colonel Mustard") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/suspects/mustard.jpg");
	}
	else if (name == "Mrs. White") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/suspects/white.jpg");
	}
	else if (name == "Mrs. Peacock") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/suspects/peacock.jpg");
	}
	else if (name == "Professor Plum")
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/suspects/plum.jpg");
	}
	else if (name == "Rope")
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/weapons/rope.jpg");
	}
	else if (name == "Wrench") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/weapons/wrench.jpg");
	}
	else if (name == "Lead Pipe") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/weapons/leadpipe.jpg");
	}
	else if (name == "Knife") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/weapons/knife.jpg");
	}
	else if (name == "Candlestick") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/weapons/candlestick.jpg");
	}
	else if (name == "Revolver") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/weapons/revolver.jpg");
	}
	else if (name == "Lounge") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/lounge.jpg");
	}
	else if (name == "Library") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/library.jpg");;
	}
	else if (name == "Ballroom") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/ballroom.jpg");
	}
	else if (name == "Billiard Room") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/billiard.jpg");
	}
	else if (name == "Kitchen") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/kitchen.jpg");
	}
	else if (name == "Conservatory") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/conservatory.jpg");
	}
	else if (name == "Hall") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/hall.jpg");
	}
	else if (name == "Study") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/study.jpg");
	}
	else if (name == "Dining Room") 
	{
		cardTextures[hand.size() - 1].loadFromFile("res/images/locations/dining.jpg");
	}

	cardSprites[hand.size() - 1].setTexture(cardTextures[hand.size() - 1]);
}

//Gets the player's hand as a vector of Cards
std::vector<Card> Player::getHand()
{
	return this->hand;
}

//Gets the Player's handbook
//WIP in terms of how we want the notebook implemented; can probably parse over newlines currently
std::vector<std::vector<int>> Player::getNotebook()
{
	return this->notebook;
	
}

//Adds an entry to the notebook, delimited by a newline and a "-"
void Player::updateNotebook(NotebookEntities row, int col, int change)
{
	this->notebook[row][col] = change;
}

/*********************************************************************************************
					void Player::renderCards(sf::RenderTarget* window)
 * Description: Renders the player's cards in the target window
*********************************************************************************************/
void Player::renderCards(sf::RenderTarget* window)
{
	cardSprites[0].setPosition(sf::Vector2f(375, 680));
	cardSprites[1].setPosition(sf::Vector2f(575, 680));
	cardSprites[2].setPosition(sf::Vector2f(775, 680));
	
	window->draw(cardSprites[0]);
	window->draw(cardSprites[1]);
	window->draw(cardSprites[2]);
}
