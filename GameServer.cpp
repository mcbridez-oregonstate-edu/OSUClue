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
    playersCreated = 0;
}

/**************************************************************************
               GameServer::GameServer(int inport) : Server(inport)
 * Description: Another constructor for the GameServer class. Takes a port
 * number as an arg, uses the Server constructor to initialize server.
**************************************************************************/
GameServer::GameServer(int inport) : Server(inport)
{
    solution = theDeck.getSolution();
    playersCreated = 0;
}

/**************************************************************************
                       void GameServer::receivePlayerInfo()
 * Description: Receives the player info from a sent packet, extracts the
 * info, and adds it into the array of player Structs.
**************************************************************************/
void GameServer::receivePlayerInfo()
{
    sf::Packet playerInfo;
    //cout << "Server: Checking if player data is sent" << endl;
    playerInfo = receiveData();
    string playerName;
    string character;
    if (playerInfo >> playerName)
    {
        playerInfo >> character;
        cout << "About to assign player info in GameServer::receivePlayerInfo" << endl;
        players[playersCreated].name = playerName;
        players[playersCreated].character = character;
        playersCreated++;
        cout << "Data received: Name: " << playerName << endl;
        cout << "Character: " << character << endl;
        cout << "Players Created: " << playersCreated << endl;
    }
}

/*********************************************************************************
                            void GameServer::acceptPlayers()
 * Description: Accepts the player connections and then gets their info.
*********************************************************************************/
void GameServer::acceptPlayers()
{
    while(numClients != 6)
    {
        acceptClient();
        sendTakenCharacters();
        receivePlayerInfo();
    }
}

/**********************************************************************************
                            void GameServer::sendTakenCharacters()
 * Description: Checks the list of currently accepted clients to see which 
 * characters are in use and sends the info to the clients so that they can disable
 * the proper characters from being selected
**********************************************************************************/
void GameServer::sendTakenCharacters()
{
    sf::Packet takenChars;
    takenChars << playersCreated;
    for (int i = 0; i < playersCreated; i++)
    {
        takenChars << players[i].character;
    }
    sendAll(takenChars);
}
