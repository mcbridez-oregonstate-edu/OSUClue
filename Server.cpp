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
 * Description: The default constructor. Has a hardcoded port value. Sets a 
 * bool values based on the success of the server creation (false = failure, 
 * true = success).
******************************************************************************/
Server::Server()
{
    port = 3456;
    numClients = 0;
    if (listener.listen(port) != sf::Socket::Done)
    {
        success = false;
    }
    else
    {
        success = true;
    }
    listener.setBlocking(false);
}

/***************************************************************************************
                                    Server::Server(int inPort)
 * Description: Another constructor for the Server class. Takes a port number. Sets a 
 * bool values based on the success of the server creation (false = failure, true = 
 * success).
***************************************************************************************/
Server::Server(int inPort)
{
    port = inPort;
    numClients = 0;
    if (listener.listen(port) != sf::Socket::Done)
    {
        success = false;
    }
    else
    {
        success = true;
    }
    listener.setBlocking(false);
}

/*******************************************************************************
                            bool isSuccessful()
 * Description: Returns the status of the server creation (false = failure, 
 * true = success)
*******************************************************************************/
bool Server::isSuccessful()
{
    return success;
}

/*******************************************************************************
                         void Server::acceptClient()
 * Description: Tells the server to accept a client. Will not accept a client
 * if there are already 6 clients accepted (i.e. the max number of players in
 * a game of Clue).
*******************************************************************************/
void Server::acceptClient()
{
    if (numClients < 6)
    {
        if (listener.accept(clients[numClients]) == sf::Socket::Done)
        {
            selector.add(clients[numClients]);
            numClients++;
        }
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
        cout << "Server Error: Issue sending data to client " << clientNum << endl;
    }
    else
    {
        cout << "Server: Data sent!" << endl;
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
            cout << "Server Error: Issue sending data" << endl;
        }
        else
        {
            //cout << "Server: Data sent!" << endl;
        }
    }
}

/****************************************************************************
                          sf::Packet Server::receiveData()
 * Description: A general receive function that loops through the clients 
 * with the selector to see which is ready to receive things.
****************************************************************************/
sf::Packet Server::receiveData()
{
    sf::Packet packet;

    if (selector.wait(sf::microseconds(10.f)))
    {
        for (int i = 0; i < numClients; i++)
        {
            if (selector.isReady(clients[i]))
            {
                cout << "Server: receiving packet" << endl;
                clients[i].receive(packet);
            }
        }
    }
    else
    {
        //cout << "Server: Nothing ready to receive" << endl;
    }

    return packet;
}
