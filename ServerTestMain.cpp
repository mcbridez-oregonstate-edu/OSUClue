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
    sf::IpAddress myIP = "172.26.36.117";
    Server theServer(port);
    Client theClient(myIP, port);

    // Test sending data from client to server and receiving data
    char clientData[100] = "This is data from the client to the server";
    theClient.sendData(clientData);
    theServer.receiveData();

    // Test sending data from server to client and receiving data
    char serverData[100] = "This is data from the server to the client";
    theServer.sendData(serverData);
    theClient.receiveData();

    return 0;
}