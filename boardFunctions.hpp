/*******************************************************************************************************************
**	Descrition: Functions related to the board
********************************************************************************************************************/
#ifndef BOARDFUNCTIONS_HPP
#define BOARDFUNCTIONS_HPP

#include <SFML/Graphics.hpp>
#include "boardTile.h"
#include "token.hpp"
#include "CardButton.hpp"
#include "NotebookButton.hpp"
#include <vector>
#include <string>
using std::string;

using std::vector;

bool isValidMove(boardTile* current_space, boardTile* target_space, int& stepCount);
boardTile*** createBoardArray();
vector<token*> playerTokens(double, double, boardTile***);
void move(sf::Event*, boardTile***, token*, int*);
vector<CardButton*> createButtonArray(int);
vector<NotebookButton*> createNotebookButtons();

int secretPassage(token* token, boardTile*** board);
void moveSuggestion(std::string room, token* token, boardTile*** board);

bool checkDoors(boardTile***, string);
bool isSecretPassage(token* token);

#endif
