/********************************************************************************
 * Program Name: Server.hpp
 * Author: Abigail Minchella
 * Date: 5/14/20
 * Description: The header file for Server
********************************************************************************/
#ifndef SERVER_HPP
#define SERVER_HPP
#include <SFML/Network.hpp>

class Server {
    private:
        int port;
        sf::TcpListener listener;
        sf::TcpSocket socket;
        // sf::TcpSocket clients[6];        Do I need this?
        sf::SocketSelector selector;

    public:
        Server(int);
        void acceptClient(sf::TcpSocket);
        void sendData(char*);
        char* receiveData();
};

#endif