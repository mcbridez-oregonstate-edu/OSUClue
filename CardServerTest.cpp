#include <SFML/Network.hpp>
#include "GameServer.hpp"
#include "GameClient.hpp"

int main()
{
	GameServer server(3456);
	sf::IpAddress serverIP = sf::IpAddress::getPublicAddress();

	GameClient client1(serverIP, 3456);
	GameClient client2(serverIP, 3456);
	GameClient client3(serverIP, 3456);
	GameClient client4(serverIP, 3456);
	GameClient client5(serverIP, 3456);
	GameClient client6(serverIP, 3456);

	for (int i = 0; i < 6; i++)
	{
		server.acceptClient();
	}
	
	server.dealPlayers();

	client1.receiveHand();
	client2.receiveHand();
	client3.receiveHand();
	client4.receiveHand();
	client5.receiveHand();
	client6.receiveHand();
}