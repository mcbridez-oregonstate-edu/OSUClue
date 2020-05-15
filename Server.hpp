/********************************************************************************
 * Program Name: Server.hpp
 * Author: Abigail Minchella
 * Date: 5/14/20
 * Description: The header file for Server
********************************************************************************/
#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <string>
using std::string;

class Server {
    private:
        int port;
        sf::TcpListener listener;
        sf::TcpSocket client;        
        sf::SocketSelector selector;

    public:
        Server(int);
        void acceptClient();
        void sendData(sf::Packet);
        string receiveData();
};

#endif