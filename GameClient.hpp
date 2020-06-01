/*******************************************************************************
 * Program Name: GameClient.hpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: The header file to set up the GameClient. Inherits from the
 * Client class
*******************************************************************************/
#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <SFML/Network.hpp>
#include "Client.hpp"
#include "Player.hpp"
#include "packetstructs.hpp"

class GameClient : public Client
{
    private:
        Player thisPlayer;

    public:
        GameClient(sf::IpAddress, int);
        void getPlayerData(string, token*, boardTile***);
        void sendPlayerData();
        void receiveHand();
        void displayHand(sf::RenderTarget*);
        bool handIsEmpty();
};

#endif