/********************************************************************************
 * Program Name: Clue.cpp
 * Author: Abigail Minchella
 * Date: 5/18/20
 * Description: The Clue game main. I would like this to become the epicenter
 * for all the finished code.
********************************************************************************/
#include "GameServer.hpp"
#include "GameClient.hpp"
#include "SimpleButton.hpp"
#include <iostream>
#include <thread>
using std::cin;
using std::cout;
using std::endl;

const int PORT = 3456;
enum joinState { START, SERVER_CREATE, SERVER_SELECT, CHARACTER_SELECT, WAITING };

int main()
{
	// Set initial state and create window
	int state = START;
	sf::RenderWindow window(sf::VideoMode(1280, 960), "Clue!", sf::Style::Default);

	// Load font for texts
	sf::Font font;
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) 
	{
		std::cout << "Font not loaded" << std::endl;
	}

	// Set up clue logo
	sf::Sprite logo;
	sf::Texture texture;
	texture.loadFromFile("res/images/logo.jpg");
	logo.setTexture(texture);
	logo.setColor(sf::Color(255, 255, 255));
	logo.setPosition(sf::Vector2f(250, 150));
	logo.setScale(4, 4);

	// Create buttons for start screen
	SimpleButton makeServer("Create a Server", sf::Vector2f(440, 550), 75);
	SimpleButton joinServer("Join a Server", sf::Vector2f(475, 670), 75);

	// Create objects for create/join server screen
	sf::Text instructions;
	instructions.setFont(font);
	instructions.setCharacterSize(70);
	instructions.setPosition(sf::Vector2f(500, 500));

	sf::Text clientInstructions;
	clientInstructions.setFont(font);
	clientInstructions.setCharacterSize(60);
	clientInstructions.setString("Please enter the IP address of the server you want to join\n        and press Enter (this may take a few seconds):");
	clientInstructions.setPosition(sf::Vector2f(90, 450));

	sf::Text IP;
	IP.setFont(font);
	IP.setCharacterSize(60);

	SimpleButton back("Back", sf::Vector2f(750, 700), 75);
	SimpleButton proceed("Continue", sf::Vector2f(400, 700), 75);

	sf::String input;
	sf::Text inputDisplay;
	inputDisplay.setFont(font);
	inputDisplay.setCharacterSize(60);
	inputDisplay.setPosition(sf::Vector2f(500, 600));

	// Set up server and client pointers and bool to track creation
	GameServer* server = nullptr;
	bool serverCreated = false;
	bool connected = false;

	GameClient* client = nullptr;
	bool clientCreated = false;
	sf::IpAddress serverIP;

	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;
		sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		// Render start screen
		if (state == START)
		{
			while (window.pollEvent(event))
			{
				makeServer.update(mouse);
				joinServer.update(mouse);
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case sf::Event::MouseButtonPressed:
					{
						if (makeServer.isPressed())
						{
							cout << "Clicked makeServer, state is changed" << endl;
							state = SERVER_CREATE;
						}
						else if (joinServer.isPressed())
						{
							cout << "Clicked joinServer, state is changed" << endl;
							state = SERVER_SELECT;
						}
						break;
					}
					default:
					{
						break;
					}
				}
			}
			window.clear();
			makeServer.render(&window);
			joinServer.render(&window);
			window.draw(logo);
			window.display();
		}

		// Render server creation screen
		else if (state == SERVER_CREATE)
		{
			// Create server
			instructions.setString("Creating server...");
			if (!serverCreated)
			{
				server = new GameServer(PORT);
				serverCreated = true;
			}
			bool serverStatus = server->isSuccessful();
			if (serverStatus == true)
			{
				serverIP = sf::IpAddress::getLocalAddress();
				instructions.setString("Done! Share the IP address with your friends!");
				instructions.setPosition(sf::Vector2f(140, 500));
				IP.setString("Server IP: " + serverIP.toString());
				IP.setPosition(sf::Vector2f(495, 575));
			}
			else if (serverStatus == false)
			{
				instructions.setString("Something went wrong! Please go back and try again");
			}

			// Don't allow the continue button to update if the server wasn't successful
			if (serverStatus == true)
			{
				proceed.update(mouse);
			}
			back.update(mouse);

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case sf::Event::MouseButtonPressed:
					{
						if (proceed.isPressed())
						{
							cout << "Continue pressed, state changing" << endl;
							state = CHARACTER_SELECT;
						}

						// Delete server and reset serverCreated so user can go back and try again
						// or select other option
						else if (back.isPressed())
						{
							cout << "Back pressed, deleting server and returning to start" << endl;
							delete server;
							server = nullptr;
							serverCreated = false;
							state = START;
						}
						break;
					}
					default:
					{
						break;
					}
				}
			}
			window.clear();
			window.draw(logo);
			back.render(&window);
			// Only draw the continue button if server creation was successful
			if (serverStatus == true)
			{
				proceed.render(&window);
			}
			window.draw(instructions);
			window.draw(IP);
			window.display();
		}

		// Render join server screen
		else if (state == SERVER_SELECT)
		{
			back.update(mouse);
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
break;
					}
					case sf::Event::TextEntered:
					{
						// Check for backspace and erase last entered character
						if (event.text.unicode == 8)
						{
							if (input.getSize() > 0)
							{
								input.erase(input.getSize() - 1, 1);
								inputDisplay.setString(input);
							}
						}

						// Check if entered character is either a number or a period
						else if ((event.text.unicode <= 57 && event.text.unicode >= 48) || event.text.unicode == 46)
						{
							if (input.getSize() < 15)
							{
								input += event.text.unicode;
								inputDisplay.setString(input);
							}
						}
					}
					case sf::Event::KeyPressed:
					{
						if (event.key.code == sf::Keyboard::Enter)
						{
							cout << "Enter Pressed!" << endl;
							serverIP = sf::IpAddress(input);
							if (!clientCreated)
							{
								client = new GameClient(serverIP, PORT);
								clientCreated = true;
								cout << "Client created" << endl;
							}

						}
					}
					case sf::Event::MouseButtonPressed:
					{
						if (proceed.isPressed())
						{
							cout << "Continue pressed, state changing" << endl;
							state = CHARACTER_SELECT;
						}

						// Delete client and reset clientCreated so user can go back and try again
						// or select other option
						else if (back.isPressed())
						{
							if (clientCreated == true)
							{
								delete client;
								client = nullptr;
								clientCreated = false;
							}
							state = START;
						}
						break;
					}
					default:
					{
						break;
					}
				}
			}
			window.clear();
			if (clientCreated == true)
			{
				cout << "clientCreated is true" << endl;
				bool clientStatus = client->isSuccessful();
				if (clientStatus == true)
				{
					cout << "Client connected" << endl;
					clientInstructions.setString("Connected to server! Press Continue to proceed");
					// Only update/render continue button if client successful
					proceed.update(mouse);
					proceed.render(&window);
				}
				else
				{
					cout << "Client not connected, clearing input and deleting client" << endl;
					clientInstructions.setString("Server IP invalid. Please enter a valid IP:");
					clientInstructions.setPosition(sf::Vector2f(275, 450));
					input.clear();
					inputDisplay.setString(input);
					delete client;
					client = nullptr;
					clientCreated = false;
				}
			}
			window.draw(logo);
			back.render(&window);
			window.draw(clientInstructions);
			window.draw(inputDisplay);
			window.display();
		}

		// Render character select screen
		else if (state == CHARACTER_SELECT)
		{
			
		}
	}


    /*
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
    }*/


    return 0;
}