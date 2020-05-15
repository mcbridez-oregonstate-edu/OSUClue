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

Server::Server(int inPort)
{
    port = inPort;
  
    if (listener.listen(port) != sf::Socket::Done)
    {
        cout << "Error: Issue connecting to port" << endl;
    }
    else
    {
        cout << "Connection to port " << port << " successful" << endl;
    }
}

void Server::acceptClient()
{
    if (listener.accept(client) != sf::Socket::Done)
    {
        cout << "Error: Issue accepting client" << endl;
    }
    else
    {
        selector.add(client);
        cout << "Client accepted" << endl;
    }
}

void Server::sendData(sf::Packet packet)
{
    if (client.send(packet) != sf::Socket::Done)
    {
        cout << "Error: Issue sending data" << endl;
    }
    else
    {
        cout << "Data sent!" << endl;
    }
}

string Server::receiveData()
{
    string data;
    sf::Packet packet;

    if (selector.wait(sf::seconds(10.f)))
    {
        client.receive(packet);
        if (packet >> data)
        {
            cout << "Data received!" << endl;
        }
    }
    else
    {
        cout << "Error: Issue receiving data" << endl;
    }

    return data;
}
