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

    sf::Socket::Status status = socket.connect(serverIP, port, sf::seconds(5.f));
    if (status != sf::Socket::Done)
    {
        success = false;
    }
    else
    {
        selector.add(socket);
        success = true;
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
        cout << "Client Error: Issue sending data" << endl;
    }
    else
    {
        cout << "Client: Data sent!" << endl;
    }
}

/***************************************************************************************
                            sf::Packet Client::receiveData()
 * Description: Receives a packet from the server
***************************************************************************************/
sf::Packet Client::receiveData()
{
    sf::Packet packet;
    if (selector.wait(sf::microseconds(10.f)))
    {
        if (selector.isReady(socket))
        {
            socket.receive(packet);
        }
    }
    else
    {
        //cout << "Server: Nothing ready to receive" << endl;
    }

    return packet;
}

/**************************************************************************
                             bool isSuccessful()
 * Description: Returns the value of "success" to indicated whether or not
 * connection to the server was succcesful
**************************************************************************/
bool Client::isSuccessful()
{
    return success;
}