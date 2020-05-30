/********************************************************************************
 * Program Name: Clue.cpp
 * Author: Abigail Minchella (gameplay taken from Adam Pham)
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
#include "StartScreen.hpp"
#include "CreateServerScreen.hpp"
#include "JoinServerScreen.hpp"
#include "CharacterSelectScreen.hpp"
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

	// Clue board
	boardTile*** clueBoard = createBoardArray();

	// create the visual representation of the board
	sf::Texture board_texture;
	if (!board_texture.loadFromFile("res/images/clueboard.png", sf::IntRect(0, 0, 500, 487)))
	{
		cout << "Cannot open clueboard.png" << endl;
	}

	sf::Sprite rendered_board;
	rendered_board.move(sf::Vector2f(390, 161.5));
	rendered_board.setTexture(board_texture);

	// dimensions of each tile on the map
	double height = 20;
	double width = 19.75;

	// create the player tokens
	vector<token*> tokensVect = playerTokens(width, height, clueBoard);
	// [Scarlet, Mustard, Green, Plum, Peacock, White]

	// Load font for texts
	sf::Font font;
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf"))
	{
		std::cout << "Font not loaded" << std::endl;
	}

	// Create start screen
	StartScreen startScreen;

	// Create create server screen
	CreateServerScreen serverScreen(&font);

	// Create server join screen
	JoinServerScreen joinScreen(&font);

	// Create character select screen
	CharacterSelectScreen charScreen(&font);

	sf::Text info;
	info.setFont(font);
	info.setCharacterSize(75);
	info.setPosition(sf::Vector2f(100, 500));

	string name;
	string character;
	bool nameEntered = false;
	bool characterCreated = false;

	// Server creation stuff (not used if client only)
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
				startScreen.updateButtons(mouse);
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (startScreen.makeServerPressed())
					{
						state = SERVER_CREATE;
					}
					else if (startScreen.joinServerPressed())
					{
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
			startScreen.render(&window);
			window.display();
		}

		/************************************RENDER SERVER CREATION SCREEN*****************************************/
		else if (state == SERVER_CREATE)
		{
			// Create server
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
				serverScreen.serverCreated(serverIP);
			}
			else if (serverStatus == false)
			{
				serverScreen.serverNotCreated();
			}

			while (window.pollEvent(event))
			{
				serverScreen.updateButtons(mouse);
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					delete server;
					delete client;
					window.close();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (serverScreen.proceedPressed())
					{
						state = CHARACTER_SELECT;
					}

					// Delete server and reset serverCreated so user can go back and try again
					// or select other option
					else if (serverScreen.backPressed())
					{
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
			serverScreen.render(&window);
			window.display();
		}

		/*****************************************RENDER SERVER JOIN SCREEN****************************************/
		else if (state == SERVER_SELECT)
		{
			while (window.pollEvent(event))
			{
				joinScreen.updateButtons(mouse);

				switch (event.type)
				{
				case sf::Event::Closed:
				{
					delete server;
					delete client;
					window.close();
					break;
				}
				case sf::Event::TextEntered:
				{
					joinScreen.getUserInput(&event);
				}
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Enter)
					{
						serverIP = sf::IpAddress(joinScreen.getIP());
						if (!clientCreated)
						{
							client = new GameClient(serverIP, PORT);
							clientCreated = true;
						}

					}
				}
				case sf::Event::MouseButtonPressed:
				{
					if (joinScreen.proceedPressed())
					{
						state = CHARACTER_SELECT;
					}

					// Delete client and reset clientCreated so user can go back and try again
					// or select other option
					else if (joinScreen.backPressed())
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
					joinScreen.clientCreated();
				}
				else
				{
					joinScreen.clientNotCreated();
					delete client;
					client = nullptr;
					clientCreated = false;
				}
			}
			joinScreen.render(&window);
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
					string prevtext = charScreen.getPlayers() + '\n';
					if (prevtext.find(taken) == string::npos)
					{
						charScreen.setPlayers(prevtext + taken);
					}
				}
				
				// Otherwise, it's a character name and needs to be checked to be disabled
				else
				{
					charScreen.disableCharacters(taken, mouse);
				}
			}
			
			// Update the character select buttons if we're past the name entering phase
			if (nameEntered)
			{
				charScreen.updateCharacters(mouse);
			}

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						delete client;
						delete server;
						window.close();
						break;
					}
					case sf::Event::TextEntered:
					{
						charScreen.getUserInput(&event);
					}
					case sf::Event::KeyPressed:
					{
						if (event.key.code == sf::Keyboard::Enter)
						{
							name = charScreen.getName();
							nameEntered = true;
							charScreen.nameEntered();
						}
					}
					case sf::Event::MouseButtonPressed:
					{
						character = charScreen.characterPressed();
						if (character != "")
						{
							client->getPlayerData(name, character, clueBoard);
							characterCreated = true;
						}

					}
					default:
					{
						break;
					}
				}
			}

			window.clear();

			// If the name is entered, move on to the second phase of character selection
			if (nameEntered && !characterCreated)
			{
				charScreen.renderCharacters(&window);
			}

			// If a character has been created, display the lobby screen
			else if (characterCreated)
			{
				charScreen.renderPlayers(&window);
			}

			// Otherwise, if neither of these things have been done, display the name screen
			else
			{
				charScreen.renderGetInput(&window);
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
						delete server;
						delete client;
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