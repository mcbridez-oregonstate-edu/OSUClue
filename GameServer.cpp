/*************************************************************************
 * Program Name: GameServer.cpp
 * Author: Abigail Minchella
 * Date: 5/17/20
 * Description: An extension of the Server class that attempts to
 * implement some of the already-written game logic
*************************************************************************/
#include "GameServer.hpp"
#include <iostream>
using std::cout;
using std::endl;

GameServer::GameServer(int inport)
{
    port = inport;
    numClients = 0;

    if (listener.listen(port) != sf::Socket::Done)
    {
        cout << "Error: Issue connecting to port" << endl;
    }
    else
    {
        cout << "Connection to port " << port << " successful" << endl;
    }
}
