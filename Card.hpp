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
	friend sf::Packet& operator <<(sf::Packet&, const Card&);
	friend sf::Packet& operator >>(sf::Packet&, Card&);
};

// enum override-- taken from https://en.sfml-dev.org/forums/index.php?topic=17075.0
// (because SFML and C++11 enums don't cooperate and I never would have been able to figure this out on my own)
template<typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
sf::Packet& operator<<(sf::Packet& roPacket, const T& reMsgType)
{
	return roPacket << static_cast<typename std::underlying_type<T>::type>(reMsgType);
}

template<typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
sf::Packet& operator>>(sf::Packet& roPacket, T& reMsgType)
{
	typename std::underlying_type<T>::type xMsgType;
	roPacket >> xMsgType;
	reMsgType = static_cast<T>(xMsgType);

	return roPacket;
}


#endif