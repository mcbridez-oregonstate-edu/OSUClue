/***********************************************************************************
 * Program Name: ServerTestMain.cpp
 * Author: Abigail Minchella
 * Date: 5/15/20
 * Description: A main to test the server setup because I have no clue what I'm
 * doing
***********************************************************************************/
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    // Set up
    int port = 3456;
    sf::IpAddress myIP = sf::IpAddress::getLocalAddress();
    Server theServer(port);
    Client theClient(myIP, port);
    theServer.acceptClient();

    // Test sending data from client to server and receiving data
    string clientData = "This is data from the client to the server";
    sf::Packet clientPacket;
    clientPacket << clientData;
    theClient.sendData(clientPacket);
    string serverRecd;
    serverRecd = theServer.receiveData();
    cout << "Data Received: " << serverRecd << endl;

    // Test sending data from server to client and receiving data
    string serverData = "This is data from the server to the client";
    sf::Packet serverPacket;
    serverPacket << serverData;
    theServer.sendData(serverPacket);
    string clientRecd;
    clientRecd = theClient.receiveData();
    cout << "Data Received: " << clientRecd << endl;

    return 0;
}