/********************************************************************************
** Created by: Devin Mourrain
** Date: 4/17/2020
** Description: This is the Player class header file. It establishes the 
				attributes that a player can have.
********************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include"Card.hpp"
#include "Token.hpp"
#include <SFML/Graphics.hpp>
#include "token.hpp"
#include<string>
#include<vector>
#include<tuple>
using std::string;
using std::vector;



enum NotebookEntities {
	GREEN_N, MUSTARD_N, PEACOCK_N, PLUM_N, SCARLET_N, WHITE_N,
	CANDLESTICK_N, KNIFE_N, REVOLVER_N, ROPE_N, PIPE_N, WRENCH_N,
	CONSERVATORY_N, BALLROOM_N, KITCHEN_N, DINING_N, LOUNGE_N, HALL_N, STUDY_N, LIBRARY_N, BILLIARD_N
};

class Player {
private:
	std::string name;							//the name of the player
	token* playerToken;							//the token that the player has chosen; see PlayerToken for the choices
	std::vector<Card*> hand;
	std::tuple<int, int> position;				//the player's token's current (x,y) coordinate
	std::vector<std::vector<int>> notebook;

	bool hasSuggested;

public:
	Player();
	Player(std::string, token*, std::tuple<int, int>);
	std::string getName();
	token* getToken();
	std::string getTokenName();
	void removeCard(std::string);
	void addCard(Card*);
	std::vector<Card*> getHand();
	void printHand();				// For testing purposes only, to be removed 
	std::tuple<int, int> getPosition();
	void updatePosition(std::tuple<int, int>);
	std::vector<std::vector<int>> getNotebook();
	NotebookEntities nCard(std::string cardName);
	int notebookRowNum(NotebookEntities input);
	void updateNotebook(NotebookEntities, int, int);
	void printNotebook();
	string sNotebook();
	vector<string> makeSuggestion();
	bool containsCard(vector<string>);
	string showCard(vector<string>);
	//void takeTurn();				// Location logic needs to be implemented so that this can check if certain conditions are met
									// before presenting the player with their options.
};

#endif