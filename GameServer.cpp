/******************************************************************************
 * Program Title: GameServer.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up basic GameServer function.... maybe
******************************************************************************/
#include "GameServer.hpp"
#include <iostream>
using std::cout;
using std::endl;

/******************************************************************************
                         GameServer::GameServer(int inPort)
 * Description: Sets up a GameServer. Takes an int for the port it should 
 * connect to. Will print success or failure to the console (mainly meant for
 * debugging--can be removed)
******************************************************************************/
GameServer::GameServer(int inPort)
{
    port = inPort;
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

/*******************************************************************************
                         void GameGameServer::acceptClient()
 * Description: Tells the GameServer to accept a client. Will not accept a client
 * if there are already 6 clients accepted (i.e. the max number of players in
 * a game of Clue). Again, printed messages are mainly for debug (though I'd
 * like to see the max players message make it into the UI)
*******************************************************************************/
void GameServer::acceptClient()
{
    if (numClients < 6)
    {
        if (listener.accept(clients[numClients]) != sf::Socket::Done)
        {
            cout << "Error: Issue accepting client" << endl;
        }

        else
        {
            selector.add(clients[numClients]);
            numClients++;
            cout << "Client accepted" << endl;
        }
    }
    else
    {
        cout << "Maximum number of players reached" << endl;
    }
}

/******************************************************************************
               void GameServer::sendOne(sf::Packet packet, int clientNum)
 * Description: Sends the passed packet to a specific client. Intended for
 * something like sending the player their options during a particular turn,
 * or any other situation where the GameServer must send something to only one
 * client. Again, printed messages are mainly for debug.
******************************************************************************/
void GameServer::sendOne(sf::Packet packet, int clientNum)
{
    if (clients[clientNum].send(packet) != sf::Socket::Done)
    {
        cout << "Error: Issue sending data" << endl;
    }
    else
    {
        cout << "Data sent!" << endl;
    }
}

/*****************************************************************************
                   void GameServer::sendAll(sf::Packet packet)
 * Description: Sends the passed packet to all the clients. Intended for use
 * in situations where all the clients need to be updated, like with what 
 * actions a player takes on their turn.
*****************************************************************************/
void GameServer::sendAll(sf::Packet packet)
{
    for (int i = 0; i < numClients; i++)
    {
        if (clients[i].send(packet) != sf::Socket::Done)
        {
            cout << "Error: Issue sending data" << endl;
        }
        else
        {
            cout << "Data sent!" << endl;
        }
    }
}

/****************************************************************************
                        sf::Packet GameServer::receiveData()
 * Description: A general receive function that loops through the clients 
 * with the selector to see which is ready to receive things. TBH I don't
 * entirely understand how this works, but it does for right now...
****************************************************************************/
sf::Packet GameServer::receiveData()
{
    sf::Packet packet;

    if (selector.wait(sf::seconds(10.f)))
    {
        for (int i = 0; i < 6; i++)
        {
            if (selector.isReady(clients[i]))
            {
                clients[i].receive(packet);
            }
        }
    }
    else
    {
        cout << "Error: Issue receiving data" << endl;
    }

    return packet;
}
