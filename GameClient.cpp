/**************************************************************************************
 * Program Name: GameClient.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up a GameClient.... maybe?
**************************************************************************************/
#include "GameClient.hpp"
#include <iostream>
using std::cout;
using std::endl;

/**************************************************************************************
                 GameClient::GameClient(sf::IpAddress server, int serverPort)
 * Description: The constructor for the GameClient class. Takes the server's IP and port
 * as arguments.
**************************************************************************************/
GameClient::GameClient(sf::IpAddress server, int serverPort)
{
    serverIP = server;
    port = serverPort;

    sf::Socket::Status status = socket.connect(serverIP, port);
    if (status != sf::Socket::Done)
    {
        cout << "Error: Could not connect to server" << endl;
    }
    else
    {
        cout << "Connected to server" << endl;
    }
}

/**************************************************************************************
                        void GameClient::sendData(sf::Packet packet)
 * Description: Sends the passed packet to the server
**************************************************************************************/
void GameClient::sendData(sf::Packet packet)
{
    if (socket.send(packet) != sf::Socket::Done)
    {
        cout << "Error: Issue sending data" << endl;
    }
    else
    {
        cout << "Data sent!" << endl;
    }
}

/***************************************************************************************
                            sf::Packet GameClient::receiveData()
 * Description: Receives a packet from the server
***************************************************************************************/
sf::Packet GameClient::receiveData()
{
    sf::Packet packet;

    if (socket.receive(packet) != sf::Socket::Done)
    {
        cout << "Error: Issue receiving data" << endl;
    }
    else
    {
        cout << "Data received!" << endl;
    }

    return packet;
}
