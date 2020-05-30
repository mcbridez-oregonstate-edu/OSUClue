/********************************************************************************
 * Program Name: GameServer.hpp
 * Author: Abigail Minchella
 * Date: 5/14/20
 * Description: The header file for GameServer
********************************************************************************/
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Server.hpp"
#include "Deck.hpp"
#include "Card.hpp"
#include "packetstructs.hpp"
#include <vector>
#include <SFML/Network.hpp>
#include <string>
using std::string;

class GameServer : public Server
{
    private:
        ServerPlayer players[6];
        int playersCreated;
        Deck theDeck;
        vector<Card*> solution;
        void receivePlayerInfo();

    public:
        GameServer();
        GameServer(int);
        void acceptPlayers();
        void sendTakenCharacters();
        void startGame();
        void dealPlayers();
};

#endif