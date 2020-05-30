/***********************************************************************************
 * Program Name: packetstructs.cpp
 * Author: Abigail Minchella
 * Date: 5/18/20
 * Description: Defines structs for use with the server and extends the Packets to be
 * able to use them
***********************************************************************************/

#include "packetstructs.hpp"


// Packet operator overrides for ServerPlayer
sf::Packet& operator <<(sf::Packet& packet, const ServerPlayer& player)
{
    return packet << player.name << player.character << player.clientNum;
}

sf::Packet& operator >>(sf::Packet& packet, ServerPlayer& player)
{
    return packet >> player.name >> player.character >> player.clientNum;
}

// Packet operator overrides for vector<Card*>
sf::Packet& operator <<(sf::Packet& packet, const vector<Card*>& hand)
{
    return packet << hand;
}

sf::Packet& operator >>(sf::Packet& packet, vector<Card*>& hand)
{
    return packet >> hand;
}