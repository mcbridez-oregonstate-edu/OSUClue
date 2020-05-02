/********************************************************************************
** Changes by: Adam Pham
** Date: 4/15/2020
** Description: This is the implementation file for the Card class. Represents the
				clues that the player can have
********************************************************************************/

#include "Card.hpp"
#include <string>

/********************************************************************************
** Function: Card()
** Description: This is the default contructor for the Card Class.
********************************************************************************/
Card::Card() {
	name = "";
	type = SUSPECT;
}

/********************************************************************************
** Function: Card::(std::string clueName; CardType clueType)
** Description: This is the default contructor for the Card Class.
********************************************************************************/
Card::Card(std::string clueName, CardType clueType) {
	name = clueName;
	type = clueType;
}

/********************************************************************************
** Function: std::string getName()
** Description: Returns the name of the card
********************************************************************************/
std::string Card::getName() {
	return name;
}

/********************************************************************************
** Function: CardType getType()
** Description: Returns the type of the card
********************************************************************************/
CardType Card::getType() {
	return type;
}