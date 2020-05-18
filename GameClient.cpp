/**************************************************************************************
 * Program Name: GameClient.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up a GameClient.... maybe?
**************************************************************************************/
#include "GameClient.hpp"
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
    getPlayerData();
    sendPlayerData();
}

/**************************************************************************************
                            void GameClient::getPlayerData()
 * Description: Prompts the player to enter their information. Should eventually
 * disallow them from choosing the same character as other players. Needs to be 
 * replaced/integrated with GUI stuff.
**************************************************************************************/
void GameClient::getPlayerData()
{
    cout << "Enter a name you want to be known by: ";
    string name;
    cin >> name;

    // Add in a call to the server to determine which choices are taken... 
    // Not sure how to disallow a choice tho.
    cout << "Choose which character you want to be from the following options (enter a number): " << endl;
    cout << "1. Miss Scarlet" << endl;
    cout << "2. Professor Plum" << endl;
    cout << "3. Mrs. White" << endl;
    cout << "4. Colonel Mustard" << endl;
    cout << "5. Mrs. Peacock" << endl;
    cout << "6. Mr. Green" << endl;
    int choice;
    PlayerToken token;
    cin >> choice;
    switch (choice)
    {
        case 1:
        {
            token = SCARLET;
            break;
        }

        case 2:
        {
            token = PLUM;
            break;
        }

        case 3:
        {
            token = WHITE;
            break;
        }

        case 4:
        {
            token = MUSTARD;
            break;
        }

        case 5:
        {
            token = PEACOCK;
            break;
        }

        case 6:
        {
            token = GREEN;
            break;
        }
    }
    tuple<int, int> placeholder;
    thisPlayer = Player(name, token, placeholder);
}

/**************************************************************************************
                                void GameClient::sendPlayerData()
 * Description: Takes the player data from the Player class instance, puts it into
 * the ServerPlayer struct to send to the server.
**************************************************************************************/
void GameClient::sendPlayerData()
{
    string name = thisPlayer.getName();
    string character = thisPlayer.getTokenName();
    int notClientPos = -1;
    ServerPlayer playerData = { name, character, notClientPos };
    sf::Packet packet;
    packet << playerData.name << playerData.character << playerData.clientNum;
    sendData(packet);
}
