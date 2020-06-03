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
#include "Suggestion.hpp"
#include "Die.hpp"
#include <iostream>
#include <thread>
using std::cin;
using std::cout;
using std::endl;
using std::thread;

const int PORT = 3456;
enum joinState { START, SERVER_CREATE, SERVER_SELECT, CHARACTER_SELECT, GAME };
enum suggestState {NO_SUGGEST, CHOOSE_SUSPECT, CHOOSE_WEAPON, SHOW_SUGGEST, SEND_SUGGEST};

int main()
{
	// Set initial state and create window
	joinState state = START;
	suggestState suggest = NO_SUGGEST;
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

	// Create suggestion functionality
	Suggestion suggestScreen(&font);

	string suspect;
	string weapon;
	string room;
	string playerTurnName;
	bool suspectEntered = false;
	bool weaponEntered = false;

	// Stuff for game screen
	sf::Text gameStatus;
	gameStatus.setFont(font);
	gameStatus.setCharacterSize(50);
	gameStatus.setPosition(sf::Vector2f(300, 30));

	bool isTurn = false;
	bool getTurn = true;
	Die die(6);
	int roll = 0;
	int steps = 0;

	sf::Text stepCounterText;
	string stepCounterString;
	stepCounterText.setFont(font);

	// Name and character creation storage/indicators
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
				cout << "About to create server" << endl;
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
			int numTaken = 0;
			string taken;
			takenChars >> numTaken;
			for (int i = 0; i < numTaken; i++)
			{
				takenChars >> taken;

				// If the randomly-generated "play the game" signal is sent
				if (taken == "d2WO8CBMC7b9KoMHh@@abO8ci!")
				{
					cout << "Client: Signal received, changing to GAME" << endl;
					if (serverCreated)
					{
						serverThread->join();
						serverThread = nullptr;
					}
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
						if (serverCreated)
						{
							delete server;
						}
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
							token* charToken = nullptr;
							for (int i = 0; i < 6; i++)
							{
								if (tokensVect[i]->getName() == character)
								{
									charToken = tokensVect[i];
								}
							}
							client->getPlayerData(name, charToken, clueBoard);
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
			// Create a new server thread to play the game (since we joined the last one to ensure it was done
			// accepting players)
			if (serverCreated && serverThread == nullptr)
			{
				serverThread = new thread(playGame, server);
			}

			// Keep trying to receive a hand until the client gets one
			while (client->handIsEmpty())
			{
				client->receiveHand();
			}

			// Get whose turn it is
			if (getTurn)
			{
				sf::Packet turnPacket;
				turnPacket = client->receiveData();
				string playerTurnCharacter;
				bool packetReceived = false;
				while (!packetReceived)
				{
					if (turnPacket >> playerTurnName >> playerTurnCharacter)
					{
						packetReceived = true;
						getTurn = false;
						if (playerTurnCharacter == character)
						{
							isTurn = true;
							gameStatus.setString("It's your turn! Make your move!");
							gameStatus.setPosition(sf::Vector2f(400, 30));
							roll = die.roll() + die.roll();
							steps = roll;
							stepCounterString = "Steps: " + std::to_string(steps) +
								"\nLocation: " + client->getToken()->get_space()->getName();
							stepCounterText.setString(stepCounterString);
						}
						else
						{
							isTurn = false;
							gameStatus.setString(playerTurnName + " (" + playerTurnCharacter + ") is taking their turn...");
							gameStatus.setPosition(sf::Vector2f(300, 30));
							stepCounterText.setString("");
						}
					}
				}
			}

			// Poll window for events
			while (window.pollEvent(event))
			{
				if (suggest == NO_SUGGEST)
				{
					switch (event.type)
					{
						case sf::Event::Closed:
						{
							if (serverCreated)
							{
								delete server;
							}
							delete client;
							window.close();
							break;
						}

						case sf::Event::KeyReleased:
						{
							if (isTurn && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up))
							{
								move(&event, clueBoard, client->getToken(), &steps);
								stepCounterString = "Steps: " + std::to_string(steps) +
									"\nLocation: " + client->getToken()->get_space()->getName();
								stepCounterText.setString(stepCounterString);
								if (steps == 0 && !client->getToken()->get_space()->isRoom())
								{
									client->updateInfo(false, false);
								}
								else if (steps == 0 && client->getToken()->get_space()->isRoom())
								{
									client->updateInfo(isTurn, true);
									suggest = CHOOSE_SUSPECT;
								}
								else
								{
									client->updateInfo(isTurn, false);
								}
							}
						}

						default:
						{
							break;
						}
					}
				}

				else
				{
					switch (event.type)
					{
						case sf::Event::Closed:
						{
							if (serverCreated)
							{
								delete server;
							}
							delete client;
							window.close();
							break;
						}

						case sf::Event::KeyReleased:
						{
							if (event.key.code == sf::Keyboard::Enter)
							{
								if (suggest == CHOOSE_SUSPECT && suspectEntered)
								{
									suggest = CHOOSE_WEAPON;
								}

								else if (suggest == CHOOSE_WEAPON && weaponEntered)
								{
									suggest = SHOW_SUGGEST;
									room = client->getToken()->get_space()->getName();
									cout << "Room: " << room << endl;
								}
								else if (suggest == SHOW_SUGGEST)
								{
									suggest = SEND_SUGGEST;
									for (int i = 0; i < tokensVect.size(); i++)
									{
										if (tokensVect[i]->getName() == suspect)
										{
											moveSuggestion(room, tokensVect[i], clueBoard);
										}
									}
								}
							}
						}

						case sf::Event::MouseButtonReleased:
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								if (suggest == CHOOSE_SUSPECT)
								{
									suggestScreen.suggestSuspect(mouse);
									suspect = suggestScreen.getSuspect();
									cout << "suspect is " << suspect << endl;
									if (suspect != "NONE")
									{
										suspectEntered = true;
									}		
								}

								else if (suggest == CHOOSE_WEAPON)
								{
									suggestScreen.suggestWeapon(mouse);
									weapon = suggestScreen.getWeapon();
									cout << "weapon is " << weapon << endl;
									if (weapon != "NONE")
									{
										weaponEntered = true;
									} 
								}
							}
						}
					}
				}
			}

			// If it is time to send the suggestion
			if (suggest == SEND_SUGGEST)
			{
				sf::Packet suggestionPacket;
				suggestionPacket << suspect << weapon << room;
				client->sendData(suggestionPacket);
			}

			// Get updated positional/turn/suggestion info
			sf::Packet updatedInfo;
			updatedInfo = client->receiveData();
			string tokenName;
			int tokenCol;
			int tokenRow;
			bool isSuggest;
			if (updatedInfo >> tokenName >> tokenCol >> tokenRow >> getTurn >> isSuggest)
			{
				if(!isTurn)
				{ 
					for (int i = 0; i < tokensVect.size(); i++)
					{
						if (tokensVect[i]->getName() == tokenName)
						{
							// Figure out how the player moved
							int colIndex = tokenCol - tokensVect[i]->get_col();
							int rowIndex = tokenRow - tokensVect[i]->get_row();

							// Move right
							if (colIndex > 0)
							{
								tokensVect[i]->move_token(width, 0, 0, 1, clueBoard);
							}

							// Move left
							else if (colIndex < 0)
							{
								tokensVect[i]->move_token(-width, 0, 0, -1, clueBoard);
							}

							// Move down
							else if (rowIndex > 0)
							{
								tokensVect[i]->move_token(0, height, 1, 0, clueBoard);
							}

							// Move up
							else if (rowIndex < 0)
							{
								tokensVect[i]->move_token(0, -height, -1, 0, clueBoard);
							}
						}

						// If the player whose turn it is has made a suggestion, handle that
						if (isSuggest)
						{
							cout << "Suggestion is being made" << endl;
							// Update status text to reflect suggestion mode
							gameStatus.setString(playerTurnName + " is making a suggestion");
							gameStatus.setPosition(sf::Vector2f(400, 30));
							window.clear();
							window.draw(rendered_board);
							window.draw(gameStatus);
							window.draw(stepCounterText);
							for (int i = 0; i < tokensVect.size(); i++)
							{
								window.draw(tokensVect[i]->get_token());
							}
							client->displayHand(&window);
							window.display();

							string playerName, playerSuspect, playerWeapon, playerRoom;
							bool suggestReceived = false;
							bool promptedForCards = false;
							bool suggestDisproved = false;

							while (!suggestReceived)
							{
								sf::Packet suggestion;
								suggestion = client->receiveData();
								if (suggestion >> playerName >> playerSuspect >> playerWeapon >> playerRoom)
								{
									cout << "Suggestion Received" << endl;
									suggestReceived = true;
									gameStatus.setString(playerName + " has suggested " + playerSuspect + " with the " + playerWeapon + " in the " + playerRoom);
									cout << playerName + " has suggested " + playerSuspect + " with the " + playerWeapon + " in the " + playerRoom << endl;
									for (int i = 0; i < tokensVect.size(); i++)
									{
										if (tokensVect[i]->getName() == playerSuspect)
										{
											moveSuggestion(playerRoom, tokensVect[i], clueBoard);
										}
									}
									window.clear();
									window.draw(rendered_board);
									window.draw(gameStatus);
									window.draw(stepCounterText);
									for (int i = 0; i < tokensVect.size(); i++)
									{
										window.draw(tokensVect[i]->get_token());
									}
									client->displayHand(&window);
									window.display();
								}
							}

							while (!promptedForCards || suggestDisproved)
							{
								string prompt = client->getPrompt();
								if (prompt == "CARDS")
								{
									promptedForCards = true;
								}
							}

							if (promptedForCards)
							{
								client->sendHand();
								bool match = client->receiveMatch();
								if (match)
								{
									bool cardChosen = false;
									bool cardEntered = false;
									string chosenCard;
									while (!cardChosen)
									{
										while (window.pollEvent(event))
										{
											switch (event.type)
											{
												case sf::Event::Closed:
												{
													if (serverCreated)
													{
														delete server;
													}
													delete client;
													window.close();
													break;
												}

												case sf::Event::KeyReleased:
												{
													if (event.key.code == sf::Keyboard::Enter && cardEntered)
													{
														cardChosen = true;
													}
												}

												case sf::Event::MouseButtonReleased:
												{
													if (event.mouseButton.button == sf::Mouse::Left)
													{
														suggestScreen.chooseRevealCard(mouse, playerSuspect, playerWeapon, playerRoom);
														chosenCard = suggestScreen.getRevealCard();
														if (chosenCard != "NONE")
														{
															cardEntered = true;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			window.clear();

			// Render proper suggestion screen if applicable
			if (suggest == CHOOSE_SUSPECT)
			{
				suggestScreen.renderSuspects(&window);
			}

			else if (suggest == CHOOSE_WEAPON)
			{
				suggestScreen.renderWeapons(&window);
			}

			else if (suggest == SHOW_SUGGEST)
			{
				suggestScreen.renderSuggestion(&window, suspect, weapon, room);
			}

			else
			{
				window.draw(rendered_board);
				window.draw(gameStatus);
				window.draw(stepCounterText);
				for (int i = 0; i < tokensVect.size(); i++)
				{
					window.draw(tokensVect[i]->get_token());
				}

				// Only draw the cards if the hand has something in it
				if (!client->handIsEmpty())
				{
					client->displayHand(&window);
				}
			}

			window.display();
		}
	}

	return 0;
}