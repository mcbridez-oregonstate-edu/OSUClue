/******************************************************************************
 * Program Title: Server.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up basic server function.... maybe
******************************************************************************/
#include "Server.hpp"
#include <iostream>
using std::cout;
using std::endl;

/******************************************************************************
                            Server::Server()
 * Description: The default constructor. Has a hardcoded port value. 
******************************************************************************/
Server::Server()
{
    port = 3456;
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

/***************************************************************************************
                                    Server::Server(int inPort)
 * Description: Another constructor for the Server class. Takes a port number.
***************************************************************************************/
Server::Server(int inPort)
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
                         void Server::acceptClient()
 * Description: Tells the server to accept a client. Will not accept a client
 * if there are already 6 clients accepted (i.e. the max number of players in
 * a game of Clue). Again, printed messages are mainly for debug (though I'd
 * like to see the max players message make it into the UI)
*******************************************************************************/
void Server::acceptClient()
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
               void Server::sendOne(sf::Packet packet, int clientNum)
 * Description: Sends the passed packet to a specific client. Intended for
 * something like sending the player their options during a particular turn,
 * or any other situation where the server must send something to only one
 * client. Again, printed messages are mainly for debug.
******************************************************************************/
void Server::sendOne(sf::Packet packet, int clientNum)
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
                       void Server::sendAll(sf::Packet packet)
 * Description: Sends the passed packet to all the clients. Intended for use
 * in situations where all the clients need to be updated, like with what 
 * actions a player takes on their turn.
*****************************************************************************/
void Server::sendAll(sf::Packet packet)
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
                          sf::Packet Server::receiveData()
 * Description: A general receive function that loops through the clients 
 * with the selector to see which is ready to receive things. TBH I don't
 * entirely understand how this works, but it does for right now...
****************************************************************************/
sf::Packet Server::receiveData()
{
    sf::Packet packet;

    if (selector.wait())
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
