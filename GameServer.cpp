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
    playerTurn = 0;
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
    playerTurn = 0;
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
    int clientNum = 0;
    if (!playerInfo.endOfPacket())
    {
        playerInfo >> players[playersCreated] >> clientNum;
        cout << "Was client num received? client num is " << clientNum << endl;
        players[playersCreated].clientNum = clientNum;
        cout << "Data received: Name: " << players[playersCreated].name << endl;
        cout << "Character: " << players[playersCreated].character << endl;
        cout << "Client Num: " << players[playersCreated].clientNum << endl;
        playersCreated++;
    }
}

/**********************************************************************************
               void GameServer::swap(ServerPlayer* a, ServerPlayer* b)
 * Description: Swaps the serverPlayers in the array. Used to get the proper
 * order of players for taking turns
**********************************************************************************/
void GameServer::swap(ServerPlayer* a, ServerPlayer* b)
{
    ServerPlayer temp = *a;
    *a = *b;
    *b = temp;
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
        if ((prevNumClients < numClients || prevNumPlayers < playersCreated) && playersCreated != 0)
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
 * Description: Deals cards to the players by sending a packet with cards in
 * it
************************************************************************************/
void GameServer::dealPlayers()
{
    vector<vector<Card>> hands = theDeck.deal();
    for (int i = 0; i < numClients; i++)
    {
        sf::Packet playerHand;
        vector<Card> hand = hands[i];
        for (int j = 0; j < hand.size(); j++)
        {
            playerHand << hand[j];
        }
        sendOne(playerHand, i);
    }
}

/****************************************************************************************
                            void GameServer::setPlayerOrder()
 * Description: Reorders the player struct array so that the players are in the order 
 * they will take turns in (Ms. Scarlet goes first, then the player to her left
 * according to the rules). Needs to loop twice because certain edge cases don't sort
 * properly the first time.
****************************************************************************************/
void GameServer::setPlayerOrder()
{
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < playersCreated; i++)
        {
            if (players[i].character == "Miss Scarlet" && i != 0)
            {
                players[i].isTurn = true;
                swap(&players[i], &players[0]);
            }
            else if (players[i].character == "Colonel Mustard" && i != 1)
            {
                swap(&players[i], &players[1]);
            }
            else if (players[i].character == "Mrs. White" && i != 2)
            {
                swap(&players[i], &players[2]);
            }
            else if (players[i].character == "Mr. Green" && i != 3)
            {
                swap(&players[i], &players[3]);
            }
            else if (players[i].character == "Mrs. Peacock" && i != 4)
            {
                swap(&players[i], &players[4]);
            }
            else if (players[i].character == "Professor Plum" && i != 5)
            {
                swap(&players[i], &players[5]);
            }
        }
    }
}

/***************************************************************************************
                                  void GameServer::sendTurn()
 * Description: Sends info about whose turn it is to all clients. Client determines
 * if it is their turn if their character name matches the one sent, otherwise will
 * display a message about whose turn it is.
***************************************************************************************/
void GameServer::sendTurn()
{
    if (playerTurn == 6)
    {
        playerTurn = 0;
    }
    sf::Packet turnPacket;
    turnPacket << players[playerTurn].name << players[playerTurn].character;
    sendAll(turnPacket);
}

/*******************************************************************************************
                                void GameServer::updatePlayers()
 * Description: Receives updated positional data from the client, updates the server's 
 * internal representation of the player, and distributes the new position to all clients
*******************************************************************************************/
void GameServer::updatePlayers()
{
    // Get data
    sf::Packet clientPos;
    clientPos = receiveData();
    ServerPlayer receivedPlayer;
    bool isSuggest;
    if (clientPos >> receivedPlayer >> isSuggest)
    {
        // Update info for that player
        for (int i = 0; i < 6; i++)
        {
            if (receivedPlayer.character == players[i].character)
            {
                players[i].row = receivedPlayer.row;
                players[i].column = receivedPlayer.column;
                players[i].isTurn = receivedPlayer.isTurn;
            }
        }

        sf::Packet sendPos;
        sendPos << receivedPlayer.character << receivedPlayer.column << receivedPlayer.row << !receivedPlayer.isTurn << isSuggest;
        sendAll(sendPos);

        if (isSuggest)
        {
            handleSuggestion();
        }
        // If that player's turn is over, increment the turn tracker
        if (receivedPlayer.isTurn == false)
        {
            playerTurn++;
            sendTurn();
        }
    }
}

/*********************************************************************************************
                                void GameServer::playGame()
 * Description: The loop from which the server administrates the game
*********************************************************************************************/
void GameServer::playGame()
{
    sendTurn();
    while (true)
    {
        updatePlayers();
    }
}

/**********************************************************************************************
                                void GameServer::handleSuggestion()
 * Description: Receives suggestion from a player, checks the hands of the other players,
 * and returns the results to the prompting player.
**********************************************************************************************/
void GameServer::handleSuggestion()
{
    string suspect;
    string weapon;
    string room;
    int clientNum;
    string playerName;
    bool suggestReceived = false;

    while (!suggestReceived)
    {
        // Receive suggestion
        sf::Packet suggestion;
        suggestion = receiveData();

        // If the packet extracts, find the player name of the client
        if (suggestion >> suspect >> weapon >> room >> clientNum)
        {
            suggestReceived = true;
            for (int i = 0; i < numClients; i++)
            {
                if (players[i].clientNum == clientNum)
                {
                    playerName = players[i].name;
                }
            }

            // Send the suggestion data to all but the suggesting client
            sf::Packet suggestOut;
            suggestOut << playerName << suspect << weapon << room;
            cout << "Server: about to send suggestion" << endl;
            sendAllButOne(suggestOut, clientNum);
        }
    }

    int checkPlayer = clientNum + 1;

    for (int i = 0; i < numClients - 1; i++)
    {
        if (checkPlayer == 6)
        {
            checkPlayer = 0;
        }
        promptForCards(checkPlayer);
        vector<Card> playerCards = getPlayerHand();
        bool match = false;
        for (int i = 0; i < playerCards.size(); i++)
        {
            if (playerCards[i].getName() == suspect || playerCards[i].getName() == room || playerCards[i].getName() == weapon)
            {
                match = true;
            }
        }
        sendMatch(match, checkPlayer);
        if (match == false)
        {
            checkPlayer++;
        }
        else
        {

        }
    }
}

/******************************************************************************************************
                            vector<Card> GameServer::getPlayerHand()
 * Description: Gets the player's cards from the client
******************************************************************************************************/
vector<Card> GameServer::getPlayerHand()
{
    sf::Packet playerHand;
    playerHand = receiveData();
    vector<Card> cards;
    Card card;
    for (int i = 0; i < 3; i++)
    {
        playerHand >> card;
        cards.push_back(card);
    }
    return cards;
}

/******************************************************************************************************
                                void GameServer::promptForCards(int clientNum)
 * Description: Sends a signal to the client to send the server their cards to be checked
******************************************************************************************************/
void GameServer::promptForCards(int clientNum)
{
    sf::Packet cardPrompt;
    cardPrompt << "CARDS";
    sendOne(cardPrompt, clientNum)
}

/******************************************************************************************************
                                 void GameServer::sendMatch(bool match, int clientNum)
 * Description: Sends the results of match to the client
******************************************************************************************************/
void GameServer::sendMatch(bool match, int clientNum)
{
    sf::Packet matchPacket;
    matchPacket << match;
    sendOne(matchPacket, clientNum);
}
