/*****************************************************************************
 * Program Name: threadFunctions.cpp
 * Date: 5/27/2020
 * Author: Abigail Minchella
 * Description: A file containing all the functions the thread needs to 
 * execute
*****************************************************************************/
#include "threadFunctions.hpp"

void acceptPlayers(GameServer* server)
{
	server->acceptPlayers();
	server->setPlayerOrder();
    server->startGame();
}

void playGame(GameServer* server)
{
	server->dealPlayers();
    server->playGame();
}