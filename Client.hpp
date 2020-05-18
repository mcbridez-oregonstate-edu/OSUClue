/*******************************************************************************
 * Program Name: Client.hpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: The header file to set up the client
*******************************************************************************/
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include <string>
using std::string;

class Client
{
    protected:
        sf::TcpSocket socket;
        int port;
        sf::IpAddress serverIP;

    public:
        Client(sf::IpAddress, int);
        void sendData(sf::Packet);
        sf::Packet receiveData();
};

#endif