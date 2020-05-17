/********************************************************************************
 * Program Name: GameServer.hpp
 * Author: Abigail Minchella
 * Date: 5/14/20
 * Description: The header file for GameServer
********************************************************************************/
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Deck.hpp"
#include "Card.hpp"
#include <vector>
#include <SFML/Network.hpp>
#include <string>
using std::string;

class GameServer {
    private:
        int port;
        sf::TcpListener listener;
        sf::TcpSocket clients[6];        
        sf::SocketSelector selector;
        int numClients;
        Deck theDeck;
        vector<Card*> solution;

    public:
        GameServer(int);
        void acceptClient();
        void sendOne(sf::Packet, int);
        void sendAll(sf::Packet);
        sf::Packet receiveData();
};

#endif