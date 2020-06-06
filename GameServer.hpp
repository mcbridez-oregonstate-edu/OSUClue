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
        int playerTurn;
        int playersCreated;
        Deck theDeck;
        vector<Card> solution;
        void receivePlayerInfo();
        void swap(ServerPlayer*, ServerPlayer*);

    public:
        GameServer();
        GameServer(int);
        void acceptPlayers();
        void sendTakenCharacters();
        void startGame();
        void dealPlayers();
        void setPlayerOrder();
        void sendTurn();
        void updatePlayers();
        void playGame();
        void handleSuggestion();
        vector<string> getPlayerHand();
        void promptForCards(int);
        void sendDone();
        void sendMatch(bool, int);
        void getReveal(int);
        void sendResultsMessage(bool, int, string);
};

#endif