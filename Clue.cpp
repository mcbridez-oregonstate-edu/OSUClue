/********************************************************************************
 * Program Name: Clue.cpp
 * Author: Abigail Minchella
 * Date: 5/18/20
 * Description: The Clue game main. I would like this to become the epicenter
 * for all the finished code.
********************************************************************************/
#include "GameServer.hpp"
#include "GameClient.hpp"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

const int PORT = 3456;

int main()
{
    // Print welcome and choices--to be replaced with GUI
    cout << "Welcome to Clue. Please choose from the following options: " << endl;
    cout << "1. Set up a server" << endl;
    cout << "2. Join a server (need IP address)" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
        {
            GameServer server(PORT);
            sf::IpAddress myIP = sf::IpAddress::getLocalAddress();
            cout << "Server set up." << endl;
            cout << "The IP address of the server is : " << myIP << "." << endl;
            cout << "Please share this with whoever you would like to play with so they can join!" << endl;
            GameClient client(myIP, PORT);
            server.acceptPlayers();
            break;
        }
        case 2:
        {
            cout << "Please input the IP address of the server you would like to connect to: ";
            sf::IpAddress serverIP;
            cin >> serverIP;
            GameClient client(serverIP, PORT);
            break;
        }
    }


    return 0;
}