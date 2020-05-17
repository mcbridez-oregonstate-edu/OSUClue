/****************************************************************************************
 * Program Name: GameServer.hpp
 * Author: Abigail Minchella
 * Date: 5/17/2020
 * Description: The header file for the GameServer class. Inherits from the Server class
****************************************************************************************/
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Server.hpp"
#include "Deck.hpp"
#include "Card.hpp"
#include <vector>

struct serverPlayer
{
    string character;
    int clientNum;
    // Point pos;       (will uncomment once the GUI functionality gets added in, I just want to have this here as a reminder
};

class GameServer : public Server
{
    private:
        Deck theDeck;
        vector<Card*> solution;

    public:
        GameServer(int);
};

#endif