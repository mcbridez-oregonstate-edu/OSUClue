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
#include "NotebookButton.hpp"
#include "boardFunctions.hpp"
#include "threadFunctions.hpp"
#include "StartScreen.hpp"
#include "CreateServerScreen.hpp"
#include "JoinServerScreen.hpp"
#include "CharacterSelectScreen.hpp"
#include "Suggestion.hpp"
#include "Accusation.hpp"
#include "Die.hpp"
#include "Sidebar.hpp"
#include <iostream>
#include <thread>
using std::cin;
using std::cout;
using std::endl;
using std::thread;

const int PORT = 3456;
enum joinState { START, SERVER_CREATE, SERVER_SELECT, CHARACTER_SELECT, GAME, GAME_OVER, DEAD};
enum suggestState {NO_SUGGEST, CHOOSE_SUSPECT, CHOOSE_WEAPON, SHOW_SUGGEST, SEND_SUGGEST, GET_REVEAL};
enum accuseState{NO_ACCUSE, CONFIRM, ACCUSE_SUSPECT, ACCUSE_WEAPON, ACCUSE_ROOM, SHOW_ACCUSE, SEND_ACCUSE};

int main()
{
	// Set initial state and create window
	joinState state = START;
	suggestState suggest = NO_SUGGEST;
	accuseState accuse = NO_ACCUSE;
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

	// Create accusation functionality
	Accusation accuseScreen(&font);

	// Create notebook buttons and Labels
	vector<NotebookButton*> notebook = createNotebookButtons();
	vector<sf::Text> labels = createNotebookLabels(&font);
	sf::Text title;
	title.setFont(font);
	title.setString("Notebook");
	title.setCharacterSize(30);
	title.setPosition(sf::Vector2f(1000, 150));

	string suspect;
	string weapon;
	string room;
	string playerTurnName;
	bool suspectEntered = false;
	bool weaponEntered = false;
	bool roomEntered = false;

	// Stuff for game screen
	sf::Text gameStatus;
	gameStatus.setFont(font);
	gameStatus.setCharacterSize(50);
	gameStatus.setPosition(sf::Vector2f(300, 30));

	Sidebar* sidebar = nullptr;
	bool sidebarCreated = false;

	bool isTurn = false;
	bool getTurn = true;
	bool movedBySuggest = false;
	bool usedPassage = false;
	Die die(6);
	int roll = 0;
	int steps = 0;

	// Buttons to allow the user to make a suggestion if they've been moved to a room by another player's suggestion
	SimpleButton yes("Yes", sf::Vector2f(450, 500), 75);
	SimpleButton no("No", sf::Vector2f(750, 500), 75);

	sf::Text stepCounterText;
	string stepCounterString;
	stepCounterText.setFont(font);
	stepCounterText.setCharacterSize(35);
	stepCounterText.setPosition(sf::Vector2f(50, 620));

	// Winner and solution for game over screen
	sf::Text gameOver;
	gameOver.setFont(font);
	gameOver.setString("GAME OVER");
	gameOver.setCharacterSize(150);
	gameOver.setPosition(300, 200);

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

			// Create sidebar with character and player name
			if (!sidebarCreated)
			{
				sidebar = new Sidebar(&font, name, character);
				sidebarCreated = true;
			}

			sidebar->updateButtons(mouse);

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
							if (!checkDoors(clueBoard, client->getToken()->get_space()->getName()))
							{
								if (movedBySuggest)
								{
									gameStatus.setString("You were moved into the " + client->getToken()->get_space()->getName() +
										"\n by another player. Would you like to make a suggestion?");
									gameStatus.setPosition(sf::Vector2f(300, 300));
									bool chosen = false;
									while (!chosen)
									{
										while (window.pollEvent(event))
										{
											mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
											yes.update(mouse);
											no.update(mouse);
											switch (event.type)
											{
												case sf::Event::Closed:
												{
													if (serverCreated)
													{
														delete server;
													}
													delete sidebar;
													delete client;
													window.close();
													break;
												}
												case sf::Event::MouseButtonPressed:
												{
													if (event.mouseButton.button == sf::Mouse::Left)
													{
														if (yes.isPressed())
														{
															chosen = true;
															suggest = CHOOSE_SUSPECT;
															client->updateInfo(isTurn, true, false);
															movedBySuggest = false;
															steps = 0;
														}
														else if (no.isPressed())
														{
															chosen = true;
															movedBySuggest = false;
														}
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
										window.draw(gameStatus);
										yes.render(&window);
										no.render(&window);
										window.display();
									}
								}
								gameStatus.setString("It's your turn! Move using the arrow keys \nor choose another action from the sidebar");
								gameStatus.setPosition(sf::Vector2f(300, 30));
								roll = die.roll() + die.roll();
								steps = roll;
								stepCounterString = "Steps Remaining: " + std::to_string(steps) +
									"\nLocation: " + client->getToken()->get_space()->getName();
								stepCounterText.setString(stepCounterString);
							}
							else
							{
								gameStatus.setString("You're blocked in the room! \nPick an action from the sidebar");
							}
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

			sidebar->disableButtons(isTurn);
			if (isTurn)
			{
				sidebar->enablePassage(isSecretPassage(client->getToken()) && !usedPassage && steps == roll);
				sidebar->enableEndTurn(steps, isTurn);
			}

			// Poll window for events
			while (window.pollEvent(event))
			{
				// Normal gameplay events
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
							delete sidebar;
							delete client;
							window.close();
							break;
						}

						case sf::Event::KeyReleased:
						{
							if (isTurn && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) && steps > 0)
							{
								move(&event, clueBoard, client->getToken(), &steps);
								stepCounterString = "Steps Remaining: " + std::to_string(steps) +
									"\nLocation: " + client->getToken()->get_space()->getName();
								stepCounterText.setString(stepCounterString);
								if (steps == 0 && client->getToken()->get_space()->isRoom())
								{
									client->updateInfo(isTurn, true, false);
									suggest = CHOOSE_SUSPECT;
								}
								else
								{
									client->updateInfo(isTurn, false, false);
								}
							}

							// This is all accusation stuff
							if (event.key.code == sf::Keyboard::Enter)
							{
								if (accuse == ACCUSE_SUSPECT && suspectEntered)
								{
									accuse = ACCUSE_WEAPON;
								}
								else if (accuse == ACCUSE_WEAPON && weaponEntered)
								{
									accuse = ACCUSE_ROOM;
								}
								else if (accuse == ACCUSE_ROOM && roomEntered)
								{
									accuse = SHOW_ACCUSE;
								}
								else if (accuse == SHOW_ACCUSE)
								{
									accuse = SEND_ACCUSE;
								}
							}
						}

						case sf::Event::MouseButtonPressed:
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								for (int i = 0; i < notebook.size(); i++) 
								{
									if (notebook[i]->isPressed()) 
									{
										notebook[i]->flipColor();
									}
								}

								if (sidebar->endTurnPressed())
								{
									client->updateInfo(false, false, false);
								}

								else if (sidebar->passagePressed())
								{
									if (client->getToken()->get_space()->getName() == "Kitchen") 
									{
										client->getToken()->move_passage(824.5, 225, 4, 23, clueBoard);
									}
									else if (client->getToken()->get_space()->getName() == "Study") 
									{
										client->getToken()->move_passage(449.25, 585, 22, 4, clueBoard);
									}
									else if (client->getToken()->get_space()->getName() == "Lounge") 
									{
										client->getToken()->move_passage(449.25, 205, 3, 4, clueBoard);
									}
									else if (client->getToken()->get_space()->getName() == "Conservatory")
									{
										client->getToken()->move_passage(804.75, 565, 21, 22, clueBoard);
									}
									usedPassage = true;
									steps = 0;
									client->updateInfo(isTurn, true, false);
									suggest = CHOOSE_SUSPECT;
								}

								else if (sidebar->accusePressed())
								{
									accuse = CONFIRM;
								}

								// If in accusation mode
								if (accuse == CONFIRM)
								{
									if (accuseScreen.yesPressed())
									{
										accuse = ACCUSE_SUSPECT;
										client->updateInfo(isTurn, false, true);
										sidebar->disableAccuse();
									}

									if (accuseScreen.noPressed())
									{
										accuse = NO_ACCUSE;
										sidebar->resetAccuse();
									}
								}
								else if (accuse == ACCUSE_SUSPECT)
								{
									accuseScreen.suggestSuspect(mouse);
									suspect = accuseScreen.getSuspect();
									if (suspect != "NONE")
									{
										suspectEntered = true;
									}
								}
								else if (accuse == ACCUSE_WEAPON)
								{
									accuseScreen.suggestWeapon(mouse);
									weapon = accuseScreen.getWeapon();
									if (weapon != "NONE")
									{
										weaponEntered = true;
									}
								}
								else if (accuse == ACCUSE_ROOM)
								{
									accuseScreen.suggestRoom(mouse);
									room = accuseScreen.getRoom();
									if (room != "NONE")
									{
										roomEntered = true;
									}
								}
							}
						}

						default:
						{
							break;
						}
					}
				}

				// Suggestion state events
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
							delete sidebar;
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
								else if (suggest == GET_REVEAL)
								{
									suggestScreen.reset();
									suspectEntered = false;
									weaponEntered = false;
									suspect = "NONE";
									weapon = "NONE";
									room = "NONE";
									suggest = NO_SUGGEST;
								}
							}
						}

						case sf::Event::MouseButtonReleased:
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								for (int i = 0; i < notebook.size(); i++)
								{
									if (notebook[i]->isPressed())
									{
										notebook[i]->flipColor();
									}
								}

								if (suggest == CHOOSE_SUSPECT)
								{
									suggestScreen.suggestSuspect(mouse);
									suspect = suggestScreen.getSuspect();
									if (suspect != "NONE")
									{
										suspectEntered = true;
									}		
								}

								else if (suggest == CHOOSE_WEAPON)
								{
									suggestScreen.suggestWeapon(mouse);
									weapon = suggestScreen.getWeapon();
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

			sidebar->updateButtons(mouse);
			for (int i = 0; i < notebook.size(); i++)
			{
				notebook[i]->update(mouse);
			}

			string revealedCard;
			string revealingPlayer;

			// If it is time to send the suggestion
			if (suggest == SEND_SUGGEST)
			{
				sf::Packet suggestionPacket;
				suggestionPacket << suspect << weapon << room;
				client->sendData(suggestionPacket);

				// Wait for reveal to be returned
				gameStatus.setString("Waiting for a card to be revealed...");
				gameStatus.setPosition(sf::Vector2f(400, 30));
				sf::Packet revealData;
				bool packetReceived = false;
				while (!packetReceived)
				{
					revealData = client->receiveData();
					if (revealData >> revealedCard >> revealingPlayer)
					{
						packetReceived = true;
					}

					// Put the render functions and event poll in here so that it doesn't get stuck
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
								delete sidebar;
								window.close();
								break;
							}
							case sf::Event::MouseButtonReleased:
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									for (int i = 0; i < notebook.size(); i++)
									{
										if (notebook[i]->isPressed())
										{
											notebook[i]->flipColor();
										}
									}
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
					window.draw(rendered_board);
					window.draw(gameStatus);
					sidebar->render(&window);
					for (int i = 0; i < tokensVect.size(); i++)
					{
						window.draw(tokensVect[i]->get_token());
					}
					for (int i = 0; i < notebook.size(); i++)
					{
						notebook[i]->update(mouse);
						notebook[i]->render(&window);
					}
					for (int i = 0; i < labels.size(); i++)
					{
						window.draw(labels[i]);
					}
					window.draw(title);
					client->displayHand(&window);
					window.display();
				}
				if (revealedCard == "DONE" && revealingPlayer == "")
				{
					gameStatus.setString(client->getResults());
					suggest = NO_SUGGEST;
				}
				else
				{
					suggestScreen.showRevealCard(revealedCard, revealingPlayer);
					string done = client->getPrompt();
					if (done == "DONE")
					{
						gameStatus.setString(client->getResults());
						gameStatus.setPosition(sf::Vector2f(275, 30));
					}
					suggest = GET_REVEAL;
					suspectEntered = false;
					weaponEntered = false;
					suspect = "NONE";
					weapon = "NONE";
					room = "NONE";
				}
			}

			// If it is time to send the accusation
			if (accuse == SEND_ACCUSE)
			{
				sf::Packet accusationPacket;
				accusationPacket << suspect << weapon << room;
				client->sendData(accusationPacket);

				bool gameOver;
				string playerName;
				string character;
				string suspect;
				string weapon;
				string room;
				bool resultsReceived = false;

				while (!resultsReceived)
				{
					sf::Packet results;
					results = client->receiveData();
					if (results >> gameOver >> playerName >> character >> suspect >> weapon >> room)
					{
						resultsReceived = true;
						if (gameOver)
						{
							gameStatus.setString("         You win!    \n" +
								suspect + " with the " + weapon + " in the " + room);
							gameStatus.setPosition(sf::Vector2f(300, 700));
							accuse = NO_ACCUSE;
							state = GAME_OVER;
							if (serverCreated)
							{
								serverThread->join();
							}
						}
						else
						{
							gameStatus.setString(playerName + " has incorrectly accused:\n" +
								suspect + " with the " + weapon + " in the " + room +
								"\n           YOU LOSE");
							gameStatus.setPosition(sf::Vector2f(400, 10));
							client->getToken()->setBlack();
							steps = 0;
							accuse = NO_ACCUSE;
						}
					}
					window.clear();
					window.draw(rendered_board);
					window.draw(gameStatus);
					window.draw(stepCounterText);
					sidebar->render(&window);
					for (int i = 0; i < tokensVect.size(); i++)
					{
						window.draw(tokensVect[i]->get_token());
					}
					client->displayHand(&window);
					window.display();
				}
			}

			// Get updated positional/turn/suggestion info
			sf::Packet updatedInfo;
			updatedInfo = client->receiveData();
			string tokenName;
			int tokenCol;
			int tokenRow;
			bool isSuggest;
			bool isAccuse;
			if (updatedInfo >> tokenName >> tokenCol >> tokenRow >> getTurn >> isSuggest >> isAccuse)
			{
				if (!isTurn)
				{
					cout << "Is accuse is: " << isAccuse << endl;
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
					}

					// If the player whose turn it is has made a suggestion, handle that
					if (isSuggest)
					{
						// Update status text to reflect suggestion mode
						gameStatus.setString(playerTurnName + " is making a suggestion");
						gameStatus.setPosition(sf::Vector2f(400, 30));
						window.clear();
						window.draw(rendered_board);
						sidebar->render(&window);
						window.draw(gameStatus);
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

						// Wait for the player's suggestion
						while (!suggestReceived)
						{
							sf::Packet suggestion;
							suggestion = client->receiveData();
							if (suggestion >> playerName >> playerSuspect >> playerWeapon >> playerRoom)
							{
								suggestReceived = true;
								gameStatus.setString("           " + playerName + " has suggested:\n" + playerSuspect + " with the " + playerWeapon + " in the " + playerRoom);
								gameStatus.setPosition(sf::Vector2f(400, 30));
								for (int i = 0; i < tokensVect.size(); i++)
								{
									if (tokensVect[i]->getName() == playerSuspect)
									{
										moveSuggestion(playerRoom, tokensVect[i], clueBoard);
										if (playerSuspect == client->getToken()->getName())
										{
											movedBySuggest = true;
										}
									}
								}
							}

							for (int i = 0; i < notebook.size(); i++)
							{
								notebook[i]->update(mouse);
							}

							// Put in event loop and render functs so things don't get stuck
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
									delete sidebar;
									window.close();
									break;
								}
								case sf::Event::MouseButtonReleased:
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										for (int i = 0; i < notebook.size(); i++)
										{
											if (notebook[i]->isPressed())
											{
												notebook[i]->flipColor();
											}
										}
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
							window.draw(rendered_board);
							window.draw(gameStatus);
							sidebar->render(&window);
							for (int i = 0; i < tokensVect.size(); i++)
							{
								window.draw(tokensVect[i]->get_token());
							}
							client->displayHand(&window);
							window.display();
						}

						while (!promptedForCards && !suggestDisproved)
						{
							mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

							string prompt = client->getPrompt();
							if (prompt == "CARDS")
							{
								promptedForCards = true;
							}
							else if (prompt == "DONE")
							{
								suggestDisproved = true;
							}

							for (int i = 0; i < notebook.size(); i++)
							{
								notebook[i]->update(mouse);
							}

							// Put in event loop and render functs so things don't get stuck
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
									delete sidebar;
									window.close();
									break;
								}
								case sf::Event::MouseButtonReleased:
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										for (int i = 0; i < notebook.size(); i++)
										{
											if (notebook[i]->isPressed())
											{
												notebook[i]->flipColor();
											}
										}
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
							window.draw(rendered_board);
							window.draw(gameStatus);
							sidebar->render(&window);
							for (int i = 0; i < tokensVect.size(); i++)
							{
								window.draw(tokensVect[i]->get_token());
							}
							client->displayHand(&window);
							window.display();
						}

						if (promptedForCards)
						{
							client->sendHand();
							bool match = client->receiveMatch();
							if (match)
							{
								// Find which cards match the suggestion in prep for the choice screen
								suggestScreen.findRevealCards(playerSuspect, playerWeapon, playerRoom, client->getHand());

								bool cardChosen = false;
								bool cardEntered = false;
								string chosenCard;
								while (!cardChosen)
								{
									// Need this in here because this is its own mini game loop and otherwise the buttons can't detect mouse pos
									mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

									for (int i = 0; i < notebook.size(); i++)
									{
										notebook[i]->update(mouse);
									}

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
											delete sidebar;
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
											break;
										}

										case sf::Event::MouseButtonReleased:
										{
											if (event.mouseButton.button == sf::Mouse::Left)
											{
												suggestScreen.chooseRevealCard(mouse);
												chosenCard = suggestScreen.getRevealCard();
												if (chosenCard != "NONE")
												{
													cardEntered = true;
												}
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
									suggestScreen.renderRevealChoice(&window);
									window.display();
								}
								client->sendReveal(chosenCard);
								suggestScreen.reset();
							}
							string donePrompt = client->getPrompt();
							while (donePrompt != "DONE")
							{
								donePrompt = client->getPrompt();
								window.clear();
								window.draw(rendered_board);
								sidebar->render(&window);
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
						gameStatus.setString(client->getResults());
						gameStatus.setPosition(sf::Vector2f(275, 30));
					}


					// Handle accusation if it is not your turn
					else if (isAccuse)
					{
						gameStatus.setString(playerTurnName + " is making an accusation!");
						gameStatus.setPosition(sf::Vector2f(400, 30));

						bool gameOver;
						string playerName;
						string character;
						string suspect;
						string weapon;
						string room;
						bool resultsReceived = false;

						while (!resultsReceived)
						{
							sf::Packet results;
							results = client->receiveData();
							if (results >> gameOver >> playerName >> character >> suspect >> weapon >> room)
							{
								resultsReceived = true;
								if (gameOver)
								{
									gameStatus.setString("                  " + playerName + " wins! \n" +
										suspect + " with the " + weapon + " in the " + room);
									gameStatus.setPosition(sf::Vector2f(300, 700));
									state = GAME_OVER;
									if (serverCreated)
									{
										serverThread->join();
									}
								}
								else
								{
									gameStatus.setString("  " + playerName + " has incorrectly accused:\n" +
										suspect + " with the " + weapon + " in the " + room +
										"\n           The game is still on!");
									gameStatus.setPosition(sf::Vector2f(400, 10));
									for (int i = 0; i < tokensVect.size(); i++)
									{
										if (tokensVect[i]->getName() == character)
										{
											tokensVect[i]->setBlack();
										}
									}
								}
							}
							window.clear();
							window.draw(rendered_board);
							window.draw(gameStatus);
							window.draw(stepCounterText);
							sidebar->render(&window);
							for (int i = 0; i < tokensVect.size(); i++)
							{
								window.draw(tokensVect[i]->get_token());
							}
							client->displayHand(&window);
							window.display();
						}
					}
				}
			}

			window.clear();

			// Render proper suggestion screen if applicable
			if (suggest == CHOOSE_SUSPECT)
			{
				suggestScreen.renderSuspects(&window);

				for (int i = 0; i < notebook.size(); i++)
				{	
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}	
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			else if (suggest == CHOOSE_WEAPON)
			{
				suggestScreen.renderWeapons(&window);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			else if (suggest == SHOW_SUGGEST)
			{
				suggestScreen.renderSuggestion(&window, room);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			else if (suggest == GET_REVEAL)
			{
				suggestScreen.renderReveal(&window);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			// Render proper Accusation screen if applicable
			else if (accuse == CONFIRM)
			{
				accuseScreen.renderConfirmation(&window);
				accuseScreen.updateButtons(mouse);
			}

			else if (accuse == ACCUSE_SUSPECT)
			{
				accuseScreen.renderSuspects(&window);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			else if (accuse == ACCUSE_WEAPON)
			{
				accuseScreen.renderWeapons(&window);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			else if (accuse == ACCUSE_ROOM)
			{
				accuseScreen.renderRooms(&window);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}
			else if (accuse == SHOW_ACCUSE)
			{
				accuseScreen.renderSuggestion(&window);
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			else
			{
				window.draw(rendered_board);
				window.draw(gameStatus);
				window.draw(stepCounterText);
				sidebar->render(&window);
				for (int i = 0; i < tokensVect.size(); i++)
				{
					window.draw(tokensVect[i]->get_token());
				}

				// Only draw the cards if the hand has something in it
				if (!client->handIsEmpty())
				{
					client->displayHand(&window);
				}
				for (int i = 0; i < notebook.size(); i++)
				{
					notebook[i]->update(mouse);
					notebook[i]->render(&window);
				}
				for (int i = 0; i < labels.size(); i++)
				{
					window.draw(labels[i]);
				}
				window.draw(title);
			}

			window.display();
		}

		// Display game over screen
		else if (state == GAME_OVER)
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
						delete sidebar;
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
			window.draw(gameOver);
			window.draw(gameStatus);
			window.display();
		}
	}

	return 0;
}