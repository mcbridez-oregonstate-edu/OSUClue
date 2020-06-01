/********************************************************************************
** Changes by: Adam Pham
** Date: 4/15/2020
** Description: This is the header file for the Card class. Represents the
				clues that the player can have
********************************************************************************/

#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

enum CardType { WEAPON, SUSPECT, ROOM };

class Card {
private:
	std::string name;
	CardType type;

public:
	Card();
	Card(std::string clueName, CardType clueType);
	std::string getName();
	CardType getType();

	//Packet operator overrides for Card*
	friend sf::Packet& operator <<(sf::Packet&, const Card*&);
	friend sf::Packet& operator >>(sf::Packet&, Card*&);
};

// Packet operator overrides for CardType
sf::Packet& operator <<(sf::Packet&, const CardType&);
sf::Packet& operator >>(sf::Packet&, CardType&);

#endif