/********************************************************************************
** Author: Adam Pham
** Date: 4/26/2019
** Description: Program to test UDP network sockets. Followed tutorial from
**				https://www.youtube.com/watch?v=kOXiLUTivHw&t=1s
**				To use, run multiple instances of the exe from Debug/SFML_visual.exe
**				Have one window run as the server on the port 2000.
********************************************************************************/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <map>
#include <conio.h>


using std::string;
using std::cout;
using std::cin;

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::UdpSocket socket;
	char connectionType;
	char buffer[2000];
	std::size_t received;
	std::string text = "Connected to: ";
	std::map<unsigned short, sf::IpAddress> computerID;

	std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
	std::cin >> connectionType;

	unsigned short port;

	std::cout << "Set port number (use 2000 if server): ";
	cin >> port;

	socket.bind(port);

	if (connectionType == 's') {
		char answer = 'b';
		do
		{
			sf::IpAddress rIp;
			unsigned short port;
			std::cout << "Awaiting connection from Client . . ." << std::endl;
			socket.receive(buffer, sizeof(buffer), received, rIp, port);
			if (received > 0) {
				computerID[port] = rIp;
			}
			std::cout << "Connection from port " << port << " received" << std::endl << std::endl;
			std::cout << "Enter (a) if there are no more clients to connect. Enter any other character otherwise." << std::endl;
			cin >> answer;
		} while (answer != 'a');
	}
	else {
		std::string sIP;
		
		sf::IpAddress sendIP(ip);
		socket.send(text.c_str(), text.length() + 1, sendIP, 2000);
		std::cout << "Connecting to Server . . ." << std::endl;
	}
	
	bool done = false;

	while (!done)
	{
		if (connectionType == 's')
		{
			std::cout << std::endl;
			std::cout << "Enter a string to send to clients:" << std::endl;
			cin.clear();
			cin.ignore(1000, '\n');
			std::getline(cin, text);
			std::map<unsigned short, sf::IpAddress>::iterator tempIterator;
			for (tempIterator = computerID.begin(); tempIterator != computerID.end(); tempIterator++) {
				std::cout << "Sending to port " << tempIterator->first << std::endl;
				socket.send(text.c_str(), text.length() + 1, tempIterator->second, tempIterator->first);
				
			}
		}
		else {
			sf::IpAddress tempIp;
			unsigned short tempPort;
			socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
			if (received > 0) {
				std::cout << "Received: " << buffer << std::endl;
			}
		}
	}
	


	system("pause");
	return 0;
}