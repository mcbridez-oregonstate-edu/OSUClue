/********************************************************************************
** Changes by: Adam Pham
** Date: 4/15/2020
** Description: This is the header file for the Card class. Represents the
				clues that the player can have
********************************************************************************/

#ifndef CARD_HPP
#define CARD_HPP

#include<string>

enum CardType {WEAPON, SUSPECT, ROOM};

class Card {
private:
	std::string name;
	CardType type;
public:
	Card();
	Card(std::string clueName, CardType clueType);
	std::string getName();
	CardType getType();
};



#endif