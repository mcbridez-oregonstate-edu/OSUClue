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
	std::string tokenName = "Colonel Mustard";
	return tokenName;
}

void Player::removeCard(Card*)
{

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
	return this->notebook;
}

void Player::updateNotebook(std::string entry)
{
	this->notebook += entry;
}
