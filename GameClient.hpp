/*******************************************************************************
 * Program Name: GameClient.hpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: The header file to set up the GameClient
*******************************************************************************/
#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <SFML/Network.hpp>

class GameClient
{
    private:
        sf::TcpSocket socket;
        int port;
        sf::IpAddress serverIP;

    public:
        GameClient(sf::IpAddress, int);
        void sendData(sf::Packet);
        sf::Packet receiveData();
};

#endif