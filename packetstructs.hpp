/**************************************************************************************
 * Program Name: packetstructs.hpp
 * Author: Abigail Minchella
 * Date: 5/18/20
 * Description: Defines structs for use with the server and extends the Packets to be
 * able to use them
**************************************************************************************/
#ifndef PACKETSTRUCTS_HPP
#define PACKETSTRUCTS_HPP

#include <SFML/Network.hpp>
#include <string>
#include "Card.hpp"
#include "Token.hpp"
using std::string;
using std::vector;

// A structure for keeping track of which client is which player, what character they're
// playing, and what their chosen name is (also later position once this gets integrated)
struct ServerPlayer
{
    string name;
    string character;   
    int clientNum;
    int column;
    int row;
    bool isTurn;
};

// Packet operator overrides for ServerPlayer
sf::Packet& operator <<(sf::Packet&, const ServerPlayer&);
sf::Packet& operator >>(sf::Packet&, ServerPlayer&);

#endif