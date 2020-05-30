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
#include <vector>
#include "Card.hpp"
using std::string;
using std::vector;

// A structure for keeping track of which client is which player, what character they're
// playing, and what their chosen name is (also later position once this gets integrated)
struct ServerPlayer
{
    string name;
    string character;   
    int clientNum;    // Type on this can be changed if necessary, mainly useful for printing/testing
    // Point pos            (uncomment once the GUI functionality gets added in--be sure to add into 
    //                      the operator overrides below)
};

// Packet operator overrides for ServerPlayer
sf::Packet& operator <<(sf::Packet&, const ServerPlayer&);

sf::Packet& operator >>(sf::Packet&, ServerPlayer&);

sf::Packet& operator <<(sf::Packet&, const vector<Card*>&);

sf::Packet& operator >>(sf::Packet&, vector<Card*>&);

#endif