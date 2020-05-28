/********************************************************************************
 * Program Name: Clue.cpp
 * Author: Abigail Minchella
 * Date: 5/18/20
 * Description: The Clue game main. I would like this to become the epicenter
 * for all the finished code.
********************************************************************************/
#include "GameServer.hpp"
#include "GameClient.hpp"
#include "CharacterButton.hpp"
#include "SimpleButton.hpp"
#include "boardFunctions.hpp"
#include "threadFunctions.hpp"
#include <iostream>
#include <thread>
using std::cin;
using std::cout;
using std::endl;
using std::thread;

const int PORT = 3456;
enum joinState { START, SERVER_CREATE, SERVER_SELECT, CHARACTER_SELECT, GAME };

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

	// Create objects for create server screen
	sf::Text instructions;
	instructions.setFont(font);
	instructions.setCharacterSize(70);
	instructions.setPosition(sf::Vector2f(500, 500));

	sf::Text IP;
	IP.setFont(font);
	IP.setCharacterSize(60);
	IP.setPosition(sf::Vector2f(455, 575));

	SimpleButton back("Back", sf::Vector2f(750, 700), 75);
	SimpleButton proceed("Continue", sf::Vector2f(400, 700), 75);
	proceed.disable();

	// Create objects for Server join screen
	sf::Text clientInstructions;
	clientInstructions.setFont(font);
	clientInstructions.setCharacterSize(60);
	clientInstructions.setString("Please enter the IP address of the server you want to join\n        and press Enter (this may take a few seconds):");
	clientInstructions.setPosition(sf::Vector2f(90, 450));

	sf::String input;
	sf::Text inputDisplay;
	inputDisplay.setFont(font);
	inputDisplay.setCharacterSize(60);
	inputDisplay.setPosition(sf::Vector2f(500, 580));

	// Character select items
	sf::Text info;
	info.setFont(font);
	info.setCharacterSize(75);
	info.setPosition(sf::Vector2f(100, 500));
	info.setString("Enter a name you would like to be known by:");

	sf::Text players;
	players.setFont(font);
	players.setCharacterSize(50);
	players.setPosition(sf::Vector2f(150, 200));

	CharacterButton characters[6] =
	{
		CharacterButton("Miss Scarlet", sf::Vector2f(150, 120)),
		CharacterButton("Mrs. Peacock", sf::Vector2f(500, 120)),
		CharacterButton("Mrs. White", sf::Vector2f(850, 120)),
		CharacterButton("Mr. Green", sf::Vector2f(150, 525)),
		CharacterButton("Colonel Mustard", sf::Vector2f(500, 525)),
		CharacterButton("Professor Plum", sf::Vector2f(850, 525))
	};

	string name;
	string character;
	bool nameEntered = false;
	bool characterCreated = false;

	// Clue board
	boardTile*** clueBoard = createBoardArray();

	// Server creation stuff (not used if client only
	GameServer* server = nullptr;
	bool serverCreated = false;
	bool connected = false;

	// Client creation stuff
	GameClient* client = nullptr;
	bool clientCreated = false;
	sf::IpAddress serverIP;

	// Going to try using threading with a pointer since only in certain cases is the thread actually implemented
	thread* serverThread = nullptr;

	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;
		sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		/*******************************************RENDER START SCREEN********************************************/
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

		/************************************RENDER SERVER CREATION SCREEN*****************************************/
		else if (state == SERVER_CREATE)
		{
			// Create server
			instructions.setString("Creating server...");
			if (!serverCreated)
			{
				server = new GameServer(PORT);
				serverCreated = true;
			}

			// If the server was successful, get and print the IP address and enable the proceed button
			bool serverStatus = server->isSuccessful();
			if (serverStatus == true)
			{
				serverIP = sf::IpAddress::getLocalAddress();
				instructions.setString("Done! Share the IP address with your friends!");
				instructions.setPosition(sf::Vector2f(140, 500));
				IP.setString("Server IP: " + serverIP.toString());
				proceed.enable();
			}
			else if (serverStatus == false)
			{
				instructions.setString("Something went wrong! Please go back and try again");
				instructions.setPosition(sf::Vector2f(75, 500));
				proceed.disable();
			}

			while (window.pollEvent(event))
			{
				proceed.update(mouse);
				back.update(mouse);
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
			proceed.render(&window);
			window.draw(instructions);
			window.draw(IP);
			window.display();
		}

		/*****************************************RENDER SERVER JOIN SCREEN****************************************/
		else if (state == SERVER_SELECT)
		{
			while (window.pollEvent(event))
			{
				back.update(mouse);
				proceed.update(mouse);
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
					if (event.text.unicode == 8 && input.getSize() > 0)
					{
						input.erase(input.getSize() - 1, 1);
						inputDisplay.setString(input);
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
						serverIP = sf::IpAddress(input);
						if (!clientCreated)
						{
							client = new GameClient(serverIP, PORT);
							clientCreated = true;
						}

					}
				}
				case sf::Event::MouseButtonPressed:
				{
					if (proceed.isPressed())
					{
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
				bool clientStatus = client->isSuccessful();
				if (clientStatus == true)
				{
					proceed.enable();
					clientInstructions.setString("Connected to server! Press Continue to proceed");
					clientInstructions.setPosition(sf::Vector2f(225, 450));
					input.clear();
					inputDisplay.setString(input);
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
			proceed.render(&window);
			back.render(&window);
			window.draw(clientInstructions);
			window.draw(inputDisplay);
			window.display();
		}

		/***************************************RENDER CHARACTER SELECT SCREEN*************************************/
		else if (state == CHARACTER_SELECT)
		{
			// If a server was created on this machine, create a client and use threading
			// to have the server wait for clients to connect
			if (!clientCreated && serverCreated)
			{
				serverThread = new thread(acceptPlayers, server);
				serverThread->detach();

				client = new GameClient(serverIP, PORT);
				clientCreated = true;
			}

			// This bit has a bunch of functions:
			// 1. Get the names of characters that are taken and disable the buttons so that they can't be used
			// 2. Get the names of players that have joined and are ready for the game to start
			// 3. Switch the game state to play the game.
			// (I'm well aware this is kinda janky, but it's the best I could come up with given the amount of
			// work still needing to be done and the time constraints)
			sf::Packet takenChars;
			takenChars = client->receiveData();
			int numTaken;
			string taken;
			takenChars >> numTaken;
			for (int i = 0; i < numTaken; i++)
			{
				takenChars >> taken;

				// If the randomly-generated "play the game" signal is sent
				if (taken == "d2WO8CBMC7b9KoMHh@@abO8ci!")
				{
					state = GAME;
				}

				// Or, if i is even, it's a player name
				else if (i == 0 || i % 2 == 0)
				{
					string prevtext = players.getString() + '\n';
					if (prevtext.find(taken) == string::npos)
					{
						players.setString(prevtext + taken);
					}
				}
				
				// Otherwise, it's a character name and needs to be checked to be disabled
				else
				{
					for (int j = 0; j < 6; j++)
					{
						if (characters[j].getName() == taken)
						{
							characters[j].setDisabled();
							characters[j].update(mouse);
						}
					}
				}
			}
			
			// Update the character select buttons if we're past the name entering phase
			if (nameEntered)
			{
				for (int i = 0; i < 6; i++)
				{
					characters[i].update(mouse);
				}
			}

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
						if (event.text.unicode == 8 && input.getSize() > 0)
						{
							input.erase(input.getSize() - 1, 1);
							inputDisplay.setString(input);
						}
						else if (input.getSize() < 25)
						{
							input += event.text.unicode;
							inputDisplay.setString(input);
						}
					}
					case sf::Event::KeyPressed:
					{
						if (event.key.code == sf::Keyboard::Enter)
						{
							name = input;
							nameEntered = true;
							info.setString("Choose your character:");
							info.setPosition(sf::Vector2f(350, 5));
						}
					}
					case sf::Event::MouseButtonPressed:
					{
						for (int i = 0; i < 6; i++)
						{
							if (characters[i].isPressed())
							{
								character = characters[i].getName();
								client->getPlayerData(name, character, clueBoard);
								characterCreated = true;
								info.setString("Waiting for other players...");
							}
						}
					}
					default:
					{
						break;
					}
				}
			}

			window.clear();
			window.draw(info);

			// If the name is entered, move on to the second phase of character selection
			if (nameEntered && !characterCreated)
			{
				for (int i = 0; i < 6; i++)
				{
					characters[i].render(&window);
				}
			}
			else if (characterCreated)
			{
				window.draw(players);
			}
			else
			{
				window.draw(logo);
				window.draw(inputDisplay);
			}
			window.display();
		}

		/**********************RENDER GAME SCREEN (This is where the action takes place)**************************/
		else if (state == GAME)
		{
			info.setString("Game stuff here");
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					default:
					{
						break;
					}
				}
			}
			window.clear();
			window.draw(info);
			window.display();
		}
	}

	return 0;
}