#include "Server.hpp"
/******************************************************************************
 * Program Title: Server.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: Sets up basic server function.... maybe
******************************************************************************/
#include "Server.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::size_t;

Server::Server(int inPort)
{
    port = inPort;
    if (listener.listen(port) != sf::Socket::Done)
    {
        cout << "Error: Issue connecting to port" << endl;
    }
}

void Server::acceptClient(sf::TcpSocket client)
{
    if (listener.accept(client) != sf::Socket::Done)
    {
        cout << "Error: Issue accepting client" << endl;
    }
}

void Server::sendData(char* data)
{
    if (socket.send(data, 100) != sf::Socket::Done)
    {
        cout << "Error: Issue sending data" << endl;
    }
}

char* Server::receiveData()
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
