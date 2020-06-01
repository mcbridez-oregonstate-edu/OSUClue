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
#include "Player.hpp"
#include <vector>

using std::vector;

bool isValidMove(Player* current_player, boardTile* target_space, int& stepCount);
boardTile*** createBoardArray();
vector<token*> playerTokens(double, double, boardTile***);
vector<CardButton*> createButtonArray(int);
vector<NotebookButton*> createNotebookButtons();

int secretPassage(token* token, boardTile*** board);
void moveSuggestion(std::string room,token* token, boardTile*** board);


#endif
