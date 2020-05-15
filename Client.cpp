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
using std::size_t;

Client::Client(sf::IpAddress server, int serverPort)
{
    serverIP = server;
    port = serverPort;

    sf::Socket::Status status = socket.connect(serverIP, port);
    if (status != sf::Socket::Done)
    {
        cout << "Error: Could not connect to server" << endl;
    }
}

void Client::sendData(char* data)
{
    if (socket.send(data, 100) != sf::Socket::Done)
    {
        cout << "Error: Issue sending data" << endl;
    }
}

char* Client::receiveData()
{
    char* data = nullptr;
    size_t bytesRecd;

    if (socket.receive(data, 100, bytesRecd) != sf::Socket::Done)
    {
        cout << "Error: Issue receiving data" << endl;
    }
    else
    {
        cout << "Received " << bytesRecd << " bytes" << endl;
    }

    return data;
}
