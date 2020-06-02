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
                                void GameClient::updateInfo(bool isTurn)
 * Description: Sends a ServerPlayer struct to the server to update the player's
 * position and turn status
****************************************************************************************/
void GameClient::updateInfo(bool isTurn)
{
    ServerPlayer myPlayer = { thisPlayer.getName(), thisPlayer.getTokenName(), -1,
        thisPlayer.getToken()->get_col(), thisPlayer.getToken()->get_row(), isTurn};
    sf::Packet updatePacket;
    updatePacket << myPlayer;
    sendData(updatePacket);
}
