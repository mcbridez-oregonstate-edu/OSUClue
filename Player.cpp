/********************************************************************************
** Created by: Devin Mourrain
** Date: 4/17/2020
** Description: This is the implementation of the Player class. See "Player.hpp"
				for a full list of the Player's attributes.
********************************************************************************/

#include "Player.hpp"

#include <string>
#include <vector>
#include <tuple>

//The default constructor for the player class; not sure how/if this will be used
Player::Player()
{
	this->name = "N/A";
	this->position = std::make_tuple(-1, -1);
	this->notebook = "";
}

//An overloaded constructor for the Player class to set its attributes
Player::Player(std::string name, PlayerToken token, std::vector<Card*> hand, std::tuple<int, int> position, std::string notebook)
{
	this->name = name;
	this->token = token;
	this->hand = hand;
	this->position = position;
	this->notebook = notebook;
}

//Gets the player's name
std::string Player::getName()
{
	return this->name;
}

//Gets the player's token (represented as a number)
PlayerToken Player::getToken()
{
	return this->token;
}

//Gets the player's token (represented as text)
//If the token isn't set or is another unexpected value, returns "Unknown Character"
std::string Player::getTokenName()
{
	if (this->token == GREEN) {
		return "Mr. Green";
	}
	else if (this->token == MUSTARD) {
		return "Colonel Mustard";
	}
	else if (this->token == PEACOCK) {
		return "Mrs. Peacock";
	}
	else if (this->token == PLUM) {
		return "Professor Plum";
	}
	else if (this->token == SCARLET) {
		return "Miss Scarlet";
	}
	else if (this->token == WHITE) {
		return "Mrs. White";
	}
	else {
		return  "Unknown Character";
	}
}

//Removes the first instance of a card from a player's hand given its name
void Player::removeCard(std::string cardName)
{
	for (std::size_t i = 0; i < this->hand.size(); i++) {
		if (this->hand.at(i)->getName() == cardName) {
			this->hand.erase(this->hand.begin() + i);
			break;
		}
	}
}

//Adds a specific card to hand
void Player::addCard(Card* card)
{
	this->hand.push_back(card);
}

//Gets the player's hand as a vector of Cards
std::vector<Card*> Player::getHand()
{
	return this->hand;
}

//Returns the Player's current position as a tuple (x, y)
std::tuple<int, int> Player::getPosition()
{
	return this->position;
}

//Updates the Player's current position to a specific x, y coordinate
void Player::updatePosition(std::tuple<int, int> pos)
{
	this->position = pos;
}

//Gets the Player's handbook
//WIP in terms of how we want the notebook implemented; can probably parse over newlines currently
std::string Player::getNotebook()
{
	if (this->notebook.empty()) {
		return this->getTokenName() + "\'s Notebook:\n\t* No Current Entries *";
	}
	else {
		return this->getTokenName() + "\'s Notebook:\n" + this->notebook;
	}
	
}

//Adds an entry to the notebook, delimited by a newline and a "-"
void Player::updateNotebook(std::string entry)
{
	this->notebook += "\n\t- "+entry;
}
