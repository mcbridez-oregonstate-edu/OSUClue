/**************************************************************************************
 * Program Name: GameClient.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up a GameClient.... maybe?
**************************************************************************************/
#include "GameClient.hpp"
#include "boardFunctions.hpp"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::tuple;

/**************************************************************************************
                 GameClient::GameClient(sf::IpAddress server, int serverPort)
 * Description: The constructor for the GameClient class. Takes the server's IP and port
 * as arguments, uses the Client constructor to initialize client stuff.
**************************************************************************************/
GameClient::GameClient(sf::IpAddress server, int serverPort) : Client(server, serverPort)
{
}

/**************************************************************************************
                            void GameClient::getPlayerData()
 * Description: Prompts the player to enter their information. Should eventually
 * disallow them from choosing the same character as other players. Needs to be 
 * replaced/integrated with GUI stuff.
**************************************************************************************/
void GameClient::getPlayerData(string name, token* playerToken, boardTile*** clueBoard)
{
    thisPlayer = Player(name, playerToken);
    sendPlayerData();
}

/**************************************************************************************
                      void GameClient::sendPlayerData()
 * Description: Takes the player data from the Player class instance, puts it into
 * the ServerPlayer struct to send to the server.
**************************************************************************************/
void GameClient::sendPlayerData()
{
    ServerPlayer myPlayer = { thisPlayer.getName(), thisPlayer.getTokenName(), -1,
        thisPlayer.getToken()->get_col(), thisPlayer.getToken()->get_row(), false };
    sf::Packet packet;
    packet << myPlayer;
    sendData(packet);
}

/***************************************************************************************
                            void GameClient::receiveHand()
 * Description: Receives the hand of cards dealt to the player by the server and 
 * stores them in the client's internal Player object's hand.
***************************************************************************************/
void GameClient::receiveHand()
{
    sf::Packet handDealt;
    handDealt = receiveData();
    if (!handDealt.endOfPacket())
    {
        Card card;
        while (handDealt >> card)
        {
            thisPlayer.addCard(card);
        }
    }
}

/****************************************************************************************
                    void GameClient::displayHand(sf::RenderTarget* window)
 * Description: Displays the player's hand to the target window. Yes, I'm aware this
 * is an odd function for this class to have, but since the decision to make the cards
 * displayable was not mine and the cards are stored in the player in this class, this
 * just has to be the way it is.
****************************************************************************************/
void GameClient::displayHand(sf::RenderTarget* window)
{
    thisPlayer.renderCards(window);
}

/****************************************************************************************
                                bool GameClient::handIsEmpty()
 * Description: Returns true if the player object's hand of cards is empty.
****************************************************************************************/
bool GameClient::handIsEmpty()
{
    return thisPlayer.getHand().empty();
}

/****************************************************************************************
                                 token* GameClient::getToken()
 * Description: Returns the pointer to the token representing the player
****************************************************************************************/
token* GameClient::getToken()
{
    return thisPlayer.getToken();
}

/****************************************************************************************
             void GameClient::updateInfo(bool isTurn, bool isSuggest, bool isAccuse)
 * Description: Sends a ServerPlayer struct to the server to update the player's
 * position and turn status
****************************************************************************************/
void GameClient::updateInfo(bool isTurn, bool isSuggest, bool isAccuse)
{
    ServerPlayer myPlayer = { thisPlayer.getName(), thisPlayer.getTokenName(), -1,
        thisPlayer.getToken()->get_col(), thisPlayer.getToken()->get_row(), isTurn};
    sf::Packet updatePacket;
    updatePacket << myPlayer << isSuggest << isAccuse;
    cout << "is Accuse in client" << isAccuse << endl;
    sendData(updatePacket);
}

/****************************************************************************************
                                void GameClient::sendHand()
 * Description: Sends the player's hand of Cards to the server
****************************************************************************************/
void GameClient::sendHand()
{
    sf::Packet cards;
    for (int i = 0; i < thisPlayer.getHand().size(); i++)
    {
        cards << thisPlayer.getHand()[i].getName();
    }
    sendData(cards);
}

/****************************************************************************************
                            string GameClient::getPrompt()
 * Description: Checks if the server has sent the prompt to send cards. Returns the 
 * string of the prompt to the calling function
****************************************************************************************/
string GameClient::getPrompt()
{
    sf::Packet prompt;
    prompt = receiveData();
    string sendCards;
    if (prompt >> sendCards)
    {
        return sendCards;
    }

    return "NO";
}

/*****************************************************************************************
                                bool GameClient::receiveMatch()
 * Description: Returns the results of the card match checking to the client
*****************************************************************************************/
bool GameClient::receiveMatch()
{
    sf::Packet matchPacket;
    bool match;
    bool packetReceived = false;
    while (!packetReceived)
    {
        matchPacket = receiveData();
        if (matchPacket >> match)
        {
            packetReceived = true;
        }
    }

    return match;
}

/******************************************************************************************
                            void GameClient::sendReveal(string cardName)
 * Description: Sends the chosen card name to the server to pass along to the suggesting
 * Player.
******************************************************************************************/
void GameClient::sendReveal(string cardName)
{
    sf::Packet revealPacket;
    revealPacket << cardName;
    sendData(revealPacket);
}

/******************************************************************************************
                                string GameClient::getResults()
 * Description: Gets the string with the message about the results of the suggestion from 
 * the server and returns it
******************************************************************************************/
string GameClient::getResults()
{
    sf::Packet results;
    string resultString;
    bool packetReceived = false;

    while (!packetReceived)
    {
        results = receiveData();
        if (results >> resultString)
        {
            packetReceived = true;
        }
    }

    return resultString;
}

/*******************************************************************************************
                                vector<Card> GameClient::getHand()
 * Description: Returns the client's player hand
*******************************************************************************************/
vector<Card> GameClient::getHand()
{
    return thisPlayer.getHand();
}
