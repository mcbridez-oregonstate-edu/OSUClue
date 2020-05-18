/**************************************************************************************
 * Program Name: Client.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up a client.... maybe?
**************************************************************************************/
#include "Client.hpp"
#include <iostream>
using std::cout;
using std::endl;

/**************************************************************************************
                   Client::Client(sf::IpAddress server, int serverPort)
 * Description: The constructor for the client class. Takes the server's IP and port
 * as arguments.
**************************************************************************************/
Client::Client(sf::IpAddress server, int serverPort)
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
                        void Client::sendData(sf::Packet packet)
 * Description: Sends the passed packet to the server
**************************************************************************************/
void Client::sendData(sf::Packet packet)
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
                            sf::Packet Client::receiveData()
 * Description: Receives a packet from the server
***************************************************************************************/
sf::Packet Client::receiveData()
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