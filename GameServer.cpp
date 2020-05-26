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

/***************************************************************************
                      GameServer::GameServer() : Server()
 * Description: The default constructor for the GameServer class. Uses the
 * Server constructor to initialize the server values.
***************************************************************************/
GameServer::GameServer() : Server()
{
    solution = theDeck.getSolution();
}

/**************************************************************************
               GameServer::GameServer(int inport) : Server(inport)
 * Description: Another constructor for the GameServer class. Takes a port
 * number as an arg, uses the Server constructor to initialize server.
**************************************************************************/
GameServer::GameServer(int inport) : Server(inport)
{
    solution = theDeck.getSolution();
}

/**************************************************************************
                       void GameServer::receivePlayerInfo()
 * Description: Receives the player info from a sent packet, extracts the
 * info, and adds it into the array of player Structs.
**************************************************************************/
void GameServer::receivePlayerInfo()
{
    sf::Packet playerInfo;
    playerInfo = receiveData();
    string playerName;
    string character;
    int clientNum;              // This is just a bogus value sent by the client
    playerInfo >> playerName >> character >> clientNum;
    // Using -1 here b/c numClients is incremented when the client is accepted.
    players[numClients - 1].name = playerName;
    players[numClients - 1].character = character;
    players[numClients - 1].clientNum = numClients - 1;
    cout << "Data received: Name: " << playerName << endl;
    cout << "Character: " << character << endl;
    cout << "Client number: " << numClients << endl;
}

/*********************************************************************************
                            void GameServer::acceptPlayers()
 * Description: Accepts the player connections and then gets their info.
*********************************************************************************/
void GameServer::acceptPlayers()
{
    for (int i = 0; i < 6; i++)
    {
        acceptClient();
        cout << "Client accepted" << endl;
    }
}
