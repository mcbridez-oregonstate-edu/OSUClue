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
** Description: This is the default contructor for the Space Class.
********************************************************************************/
Card::Card(std::string clueName, CardType clueType) {
	name = clueName;
	type = clueType;
	
	// load textures for card images
	if (name == "Miss Scarlet") {		
		texture.loadFromFile("res/images/suspects/scarlett.jpg");
	}
	else if (name == "Mr. Green") {	
		texture.loadFromFile("res/images/suspects/green.jpg");
	}
	else if (name == "Colonel Mustard") {	
		texture.loadFromFile("res/images/suspects/mustard.jpg");	
	}
	else if (name == "Mrs. White") {
		texture.loadFromFile("res/images/suspects/white.jpg");	
	}
	else if (name == "Mrs. Peacock") {	
		texture.loadFromFile("res/images/suspects/peacock.jpg");	
	}
	else if (name == "Professor Plum")
	{	
		texture.loadFromFile("res/images/suspects/plum.jpg");	
	}
	else if (name == "Rope")
	{	
		texture.loadFromFile("res/images/weapons/rope.jpg");	
	}
	else if (name == "Wrench") {	
		texture.loadFromFile("res/images/weapons/wrench.jpg");	
	}
	else if (name == "Lead Pipe") {
		texture.loadFromFile("res/images/weapons/leadpipe.jpg");	
	}
	else if (name == "Knife") {	
		texture.loadFromFile("res/images/weapons/knife.jpg");	
	}
	else if (name == "Candlestick") {	
		texture.loadFromFile("res/images/weapons/candlestick.jpg");	
	}
	else if (name == "Revolver") {
		texture.loadFromFile("res/images/weapons/revolver.jpg");	
	}
	else if (name == "Lounge") {
		texture.loadFromFile("res/images/locations/lounge.jpg");
	}
	else if (name == "Library") {
		texture.loadFromFile("res/images/locations/library.jpg");;	
	}
	else if (name == "Ballroom") {	
		texture.loadFromFile("res/images/locations/ballroom.jpg");	
	}
	else if (name == "Billiard Room") {	
		texture.loadFromFile("res/images/locations/billiard.jpg");	
	}
	else if (name == "Kitchen") {	
		texture.loadFromFile("res/images/locations/kitchen.jpg");	
	}
	else if (name == "Conservatory") {	
		texture.loadFromFile("res/images/locations/conservatory.jpg");		
	}
	else if (name == "Hall") {	
		texture.loadFromFile("res/images/locations/hall.jpg");	
	}
	else if (name == "Study") {	
		texture.loadFromFile("res/images/locations/study.jpg");
	}
	else if (name == "Dining Room") {	
		texture.loadFromFile("res/images/locations/dining.jpg");	
	}

	image.setTexture(texture);
}

/********************************************************************************
** Function: std::string getName()
** Description: Returns the name of the card
********************************************************************************/
std::string Card::getName() {
	return name;
}

/********************************************************************************
** Function: void setCardPos(sf::Vector2f pos);
** Description: Sets the card's position in the game window.
********************************************************************************/
void Card::setCardPos(sf::Vector2f pos)
{
	image.move(pos);
}

/********************************************************************************
** Function: sf::Sprite getSprite()
** Description: returns the Card's sprite
********************************************************************************/
sf::Sprite Card::getSprite()
{
	return image;
}


/********************************************************************************
** Function: CardType getType()
** Description: Returns the type of the card
********************************************************************************/
CardType Card::getType() {
	return type;
}