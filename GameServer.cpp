/*************************************************************************
 * Program Name: GameServer.cpp
 * Author: Abigail Minchella
 * Date: 5/17/20
 * Description: An extension of the Server class that attempts to
 * implement some of the already-written game logic
*************************************************************************/
#include "GameServer.hpp"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

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
    int clientNum;
    if (playerInfo >> playerName)
    {
        playerInfo >> character >> clientNum;
        cout << "About to assign player info in GameServer::receivePlayerInfo" << endl;
        players[playersCreated].name = playerName;
        players[playersCreated].character = character;
        players[playersCreated].clientNum = clientNum;
        playersCreated++;
        cout << "Data received: Name: " << playerName << endl;
        cout << "Character: " << character << endl;
        cout << "Client Num: " << clientNum << endl;
    }
}

/*********************************************************************************
                            void GameServer::acceptPlayers()
 * Description: Accepts the player connections and then gets their info.
*********************************************************************************/
void GameServer::acceptPlayers()
{
    int prevNumClients = numClients;
    int prevNumPlayers = playersCreated;
    while(playersCreated < 6)
    {
        acceptClient();
        // Only send if we have a new client or player
        if (prevNumClients < numClients || prevNumPlayers < playersCreated)
        {
            sendTakenCharacters();
            prevNumClients = numClients;
            prevNumPlayers = playersCreated;
        }
        receivePlayerInfo();
    }
}

/**********************************************************************************
                          void GameServer::sendTakenCharacters()
 * Description: Checks the list of currently accepted clients to see which 
 * characters are in use and sends the info to the clients so that they can disable
 * the proper characters from being selected. Also sends character names so they
 * can be used on the waiting screen
**********************************************************************************/
void GameServer::sendTakenCharacters()
{
    sf::Packet takenChars;
    takenChars << playersCreated * 2;
    for (int i = 0; i < playersCreated; i++)
    {
        takenChars << players[i].name;
        takenChars << players[i].character;
    }
    sendAll(takenChars);
}

/***********************************************************************************
                            void GameServer::startGame()
 * Description: Sends the client a signal that the game is starting (a randomly
 * -generated string that would be nearly impossible to come up with and is too 
 * long for the user to enter (limit on chars is 25))
***********************************************************************************/
void GameServer::startGame()
{
    sf::Packet startGame;
    startGame << 1 << "d2WO8CBMC7b9KoMHh@@abO8ci!";
    sendAll(startGame);
}

/************************************************************************************
                                void GameServer::dealPlayers()
 * Description: Deals cards to the players by sending a packet with their hand in
 * it
************************************************************************************/
void GameServer::dealPlayers()
{
    vector<vector<Card*>> hands = theDeck.deal();
    for (int i = 0; i < 6; i++)
    {
        sf::Packet playerHand;
        playerHand << hands[i];
        sendOne(playerHand, i);
    }
}
