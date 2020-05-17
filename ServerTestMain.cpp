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
    Client client1(myIP, port);
    Client client2(myIP, port);
    Client client3(myIP, port);
    Client client4(myIP, port);
    Client client5(myIP, port);
    Client client6(myIP, port);
    Client extraClient(myIP, port);
    for (int i = 0; i < 7; i++)
    {
        theServer.acceptClient();
    }

    // Test sending data from client to server and receiving data
    string client1Data = "I am client 1";
    string client2Data = "I am client 2";
    string client3Data = "I am client 3";
    string client4Data = "I am client 4";
    string client5Data = "I am client 5";
    string client6Data = "I am client 6";

    sf::Packet client1Packet;
    client1Packet << client1Data;
    client1.sendData(client1Packet);

    sf::Packet serverRecd;
    serverRecd = theServer.receiveData();
    string data;
    serverRecd >> data;
    cout << "Data Received: " << data << endl;

    sf::Packet client2Packet;
    client2Packet << client2Data;
    client2.sendData(client2Packet);

    serverRecd = theServer.receiveData();
    serverRecd >> data;
    cout << "Data Received: " << data << endl;

    sf::Packet client3Packet;
    client3Packet << client3Data;
    client3.sendData(client3Packet);

    serverRecd = theServer.receiveData();
    serverRecd >> data;
    cout << "Data Received: " << data << endl;

    sf::Packet client4Packet;
    client4Packet << client4Data;
    client4.sendData(client4Packet);

    serverRecd = theServer.receiveData();
    serverRecd >> data;
    cout << "Data Received: " << data << endl;

    sf::Packet client5Packet;
    client5Packet << client5Data;
    client5.sendData(client5Packet);

    serverRecd = theServer.receiveData();
    serverRecd >> data;
    cout << "Data Received: " << data << endl;

    sf::Packet client6Packet;
    client6Packet << client6Data;
    client6.sendData(client6Packet);

    serverRecd = theServer.receiveData();
    serverRecd >> data;
    cout << "Data Received: " << data << endl;

    // Test sending data from server to client and receiving data
    string serverData = "This is data from the server to all clients";
    sf::Packet serverPacket;
    serverPacket << serverData;
    theServer.sendAll(serverPacket);

    sf::Packet client1Recd;
    client1Recd = client1.receiveData();
    string data1;
    client1Recd >> data1;
    cout << "Data Received by client 1: " << data1 << endl;

    sf::Packet client2Recd;
    client2Recd = client2.receiveData();
    string data2;
    client2Recd >> data2;
    cout << "Data Received by client 2: " << data2 << endl;

    sf::Packet client3Recd;
    client3Recd = client3.receiveData();
    string data3;
    client3Recd >> data3;
    cout << "Data Received by client 3: " << data3 << endl;

    sf::Packet client4Recd;
    client4Recd = client4.receiveData();
    string data4;
    client4Recd >> data4;
    cout << "Data Received by client 4: " << data4 << endl;

    sf::Packet client5Recd;
    client5Recd = client5.receiveData();
    string data5;
    client5Recd >> data5;
    cout << "Data Received by client 5: " << data5 << endl;

    sf::Packet client6Recd;
    client6Recd = client6.receiveData();
    string data6;
    client6Recd >> data6;
    cout << "Data Received by client 6: " << data6 << endl;

    // Try sending to one client
    string dataForClient4 = "This data is meant for receipt by client 4";
    sf::Packet forClient4;
    forClient4 << dataForClient4;
    theServer.sendOne(forClient4, 3);

    sf::Packet client4packet;
    client4packet = client4.receiveData();
    string secretData;
    client4packet >> secretData;
    cout << "Client 4 received the following: " << secretData << endl;

    return 0;
}