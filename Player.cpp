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


Player::Player()
{
	this->name = "N/A";
	this->position = std::make_tuple(-1, -1);
	this->notebook = "";
}

Player::Player(std::string name, PlayerToken token, std::vector<Card*> hand, std::tuple<int, int> position, std::string notebook)
{
	this->name = name;
	this->token = token;
	this->hand = hand;
	this->position = position;
	this->notebook = notebook;
}

std::string Player::getName()
{
	return this->name;
}

PlayerToken Player::getToken()
{
	return this->token;
}

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

void Player::addCard(Card* card)
{
	this->hand.push_back(card);
}

std::vector<Card*> Player::getHand()
{
	return this->hand;
}

std::tuple<int, int> Player::getPosition()
{
	return this->position;
}

void Player::updatePosition(std::tuple<int, int> pos)
{
	this->position = pos;
}

std::string Player::getNotebook()
{
	if (this->notebook.empty()) {
		return this->getTokenName() + "\'s Notebook:\n\t* No Current Entries *";
	}
	else {
		return this->getTokenName() + "\'s Notebook:\n" + this->notebook;
	}
	
}

void Player::updateNotebook(std::string entry)
{
	this->notebook += "\n\t- "+entry;
}
