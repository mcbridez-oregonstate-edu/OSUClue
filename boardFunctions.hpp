/*******************************************************************************************************************
**	Descrition: Functions related to the board
********************************************************************************************************************/
#ifndef BOARDFUNCTIONS_HPP
#define BOARDFUNCTIONS_HPP

#include <SFML/Graphics.hpp>
#include "boardTile.h"
#include "token.hpp"
#include "CardButton.hpp"
#include <vector>

using std::vector;

bool isValidMove(boardTile* current_space, boardTile* target_space, int& stepCount);
boardTile*** createBoardArray();
vector<token*> playerTokens(double, double, boardTile***);
vector<CardButton*> createButtonArray(int);


#endif
