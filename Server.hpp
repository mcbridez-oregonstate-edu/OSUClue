/********************************************************************************
 * Program Name: Server.hpp
 * Author: Abigail Minchella
 * Date: 5/14/20
 * Description: The header file for Server
********************************************************************************/
#ifndef SERVER_HPP
#define SERVER_HPP

#include "packetstructs.hpp"
#include <SFML/Network.hpp>
#include <string>
using std::string;

class Server 
{
    protected:
        int port;
        sf::TcpListener listener;
        sf::TcpSocket clients[6];        
        sf::SocketSelector selector;
        int numClients;
        bool success;

    public:
        Server();
        Server(int);
        bool isSuccessful();
        void acceptClient();
        void sendOne(sf::Packet, int);
        void sendAll(sf::Packet);
        void sendAllButOne(sf::Packet, int);
        sf::Packet receiveData();
};

#endif