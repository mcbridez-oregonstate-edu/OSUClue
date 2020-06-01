/********************************************************************************
** Created by: Devin Mourrain
** Suggestion function by: Abigail Minchella
** Date: 4/17/2020
** Description: This is the implementation of the Player class. See "Player.hpp"
				for a full list of the Player's attributes.
********************************************************************************/

#include "Player.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <time.h>
#include <cstdlib>
#include <limits>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::srand;
using std::rand;

//The default constructor for the player class; not sure how/if this will be used
Player::Player()
{
	this->name = "N/A";
	this->position = std::make_tuple(-1, -1);
}

//An overloaded constructor for the Player class to set its attributes
Player::Player(std::string name, token* inputToken, std::tuple<int, int> position)
{
	this->name = name;
	this->playerToken = inputToken;
	this->position = position;
	// -1 is empty, 0 is an "No", and 1 is a "Yes"; The initial layout is all empty
	std::vector<std::vector<int>> initialNotebook{	{-1, -1, -1, -1, -1},					//0Green
													{-1, -1, -1, -1, -1},			//1Mustard
													{-1, -1, -1, -1, -1},			//2Peacock
													{-1, -1, -1, -1, -1},			//3Plum
													{-1, -1, -1, -1, -1},			//4Scarlet
													{-1, -1, -1, -1, -1},			//5White
													{-1, -1, -1, -1, -1},			//6Candlestick
													{-1, -1, -1, -1, -1},			//7Knife
													{-1, -1, -1, -1, -1},			//8Revolver
													{-1, -1, -1, -1, -1},			//9Lead Pipe
													{-1, -1, -1, -1, -1},			//10Rope
													{-1, -1, -1, -1, -1},			//11Wrench
													{-1, -1, -1, -1, -1},			//12Conservatory
													{-1, -1, -1, -1, -1},			//13Ballroom
													{-1, -1, -1, -1, -1},			//14Kitchen
													{-1, -1, -1, -1, -1},			//15Dining Room
													{-1, -1, -1, -1, -1},			//16Lounge
													{-1, -1, -1, -1, -1},			//17Hall
													{-1, -1, -1, -1, -1},			//18Study
													{-1, -1, -1, -1, -1},			//19Library
													{-1, -1, -1, -1, -1},			//20Billiard Room
	};


	this->notebook = initialNotebook;
	/*int notebookInit[21];
	for (int i = 0; i < 21; i++) {
		notebookInit[i] = 0;
	}*/
	this->newNotebook/* = notebookInit;*/;
	this->hasSuggested = 0;
	this->alive = 1;
}

//Gets the player's name
std::string Player::getName()
{
	return this->name;
}

//Gets the player's token (represented as a number)
token* Player::getToken()
{
	return this->playerToken;
}

//Gets the player's token (represented as text)
//If the token isn't set or is another unexpected value, returns "Unknown Character"
std::string Player::getTokenName()
{
	return playerToken->getName();
}

//Removes the first instance of a card from a player's hand given its name
void Player::removeCard(std::string cardName)
{
	for (std::size_t i = 0; i < this->hand.size(); i++) {
		if (this->hand.at(i)->getName() == cardName) {
			this->hand.erase(this->hand.begin() + i);
			break;
		}
	}
}

//Adds a specific card to hand
void Player::addCard(Card* card)
{
	this->hand.push_back(card);
}

//Gets the player's hand as a vector of Cards
std::vector<Card*> Player::getHand()
{
	return this->hand;
}

// Prints the Player's hand. For testing only, to be removed after UI integration
void Player::printHand()
{
	for (int i = 0; i < hand.size(); i++)
	{
		cout << hand[i]->getName() << endl;
	}
}

//Returns the Player's current position as a tuple (x, y)
std::tuple<int, int> Player::getPosition()
{
	return this->position;
}

//Updates the Player's current position to a specific x, y coordinate
void Player::updatePosition(std::tuple<int, int> pos)
{
	this->position = pos;
}

//Gets the Player's handbook
//WIP in terms of how we want the notebook implemented; can probably parse over newlines currently
std::vector<std::vector<int>> Player::getNotebook()
{
	return this->notebook;
	
}

//Returns notebook entity name for updating notebook
NotebookEntities Player::nCard(std::string cardName) {
	if (cardName == "Mr. Green") {
		return GREEN_N;
	}
	else if (cardName == "Colonel Mustard") {
		return MUSTARD_N;
	}
	else if (cardName == "Mrs. Peacock") {
		return PEACOCK_N;
	}
	else if (cardName == "Professor Plum") {
		return PLUM_N;
	}
	else if (cardName == "Miss Scarlet") {
		return SCARLET_N;
	}
	else if (cardName == "Mrs. White") {
		return WHITE_N;
	}
	else if (cardName == "Candlestick") {
		return CANDLESTICK_N;
	}
	else if (cardName == "Knife") {
		return KNIFE_N;
	}
	else if (cardName == "Revolver") {
		return REVOLVER_N;
	}
	else if (cardName == "Lead Pipe") {
		return PIPE_N;
	}
	else if (cardName == "Rope") {
		return ROPE_N;
	}
	else if (cardName == "Wrench") {
		return WRENCH_N;
	}
	else if (cardName == "Conservatory") {
		return CONSERVATORY_N;
	}
	else if (cardName == "Ballroom") {
		return BALLROOM_N;
	}
	else if (cardName == "Kitchen") {
		return KITCHEN_N;
	}
	else if (cardName == "Dining Room") {
		return DINING_N;
	}
	else if (cardName == "Lounge") {
		return LOUNGE_N;
	}
	else if (cardName == "Hall") {
		return HALL_N;
	}
	else if (cardName == "Study") {
		return STUDY_N;
	}
	else if (cardName == "Library") {
		return LIBRARY_N;
	}
	else if (cardName == "Billiard Room") {
		return BILLIARD_N;
	}
	else {
		std::cout << "Something went wrong trying to return nName." << std::endl;
		std::cout << cardName << std::endl;
	}
}

//returns row number of journal array for corresponding Notebook Entity
int Player::notebookRowNum(NotebookEntities input) {
	if (input == GREEN_N) {
		return 0;
	}
	else if (input == MUSTARD_N) {
		return 1;
	}
	else if (input == PEACOCK_N) {
		return 2;
	}
	else if (input == PLUM_N) {
		return 3;
	}
	else if (input == SCARLET_N) {
		return 4;
	}
	else if (input == WHITE_N) {
		return 5;
	}
	else if (input == CANDLESTICK_N) {
		return 6;
	}
	else if (input == KNIFE_N) {
		return 7;
	}
	else if (input == REVOLVER_N) {
		return 8;
	}
	else if (input == PIPE_N) {
		return 9;
	}
	else if (input == ROPE_N) {
		return 10;
	}
	else if (input == WRENCH_N) {
		return 11;
	}
	else if (input == CONSERVATORY_N) {
		return 12;
	}
	else if (input == BALLROOM_N) {
		return 13;
	}
	else if (input == KITCHEN_N) {
		return 14;
	}
	else if (input == DINING_N) {
		return 15;
	}
	else if (input == LOUNGE_N) {
		return 16;
	}
	else if (input == HALL_N) {
		return 17;
	}
	else if (input == STUDY_N) {
		return 18;
	}
	else if (input == LIBRARY_N) {
		return 19;
	}
	else if (input == BILLIARD_N) {
		return 20;
	}
	else {
		std::cout << "Something went wrong with rowNum." << std::endl;
	}
}

//Adds an entry to the notebook, delimited by a newline and a "-"
void Player::updateNotebook(NotebookEntities row, int col, int change)
{
	int numRow = this->notebookRowNum(row);
	this->notebook[numRow][col] = change;
}

//debug function; not likely for game use
void Player::printNotebook() {
	for (int i = 0; i < this->notebook.size(); i++) {
		for (int j = 0; j < this->notebook[i].size(); j++) {
			std::cout << this->notebook[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//takes Notebook and outputs a useful string
string Player::sNotebook() {
	string output;
	string rowNames[] = { 
		"Green_____________", 
		"Mustard___________", 
		"Peacock___________", 
		"Plum______________", 
		"Scarlet____________", 
		"White_____________", 
		"Candlestick________", 
		"Knife______________", 
		"Revolver___________", 
		"Lead Pipe__________", 
		"Rope______________", 
		"Wrench___________", 
		"Conservatory_______", 
		"Ballroom___________", 
		"Kitchen____________", 
		"Dining Room________", 
		"Lounge____________", 
		"Hall_______________", 
		"Study_____________", 
		"Library____________", 
		"Billiard Room_______" };
	for (int i = 0; i < this->notebook.size(); i++) {
		output += rowNames[i];
		for (int j = 0; j < this->notebook[i].size(); j++) {
			//output += std::to_string(this->notebook[i][j]);
			if (this->notebook[i][j] == -1) {
				output += " ";
			}
			else if (this->notebook[i][j] == 0) {
				output += "No";
			}
			else {
				output += "Yes";
			}
			output += " ";
		}
		output += '\n';
	}
	return output;
}

/*******************************************************************************************
							vector<string> Player::makeSuggestion()
* Description: Prompts the player for suggestion input and returns their answers for
* comparison with other players' hands in the calling function. Also provides functionality 
* for the player to view their hand and notebook so that they are able to make an educated
* guess. Currently implemented with console IO, to be integrated with a UI later
*******************************************************************************************/
vector<string> Player::makeSuggestion()
{
	// Output instructions
	vector<string> suggestion;
	cout << "Choose a suspect to suggest by typing a number or type 'Notebook' or 'Hand' to view your notebook or hand" << endl;
	cout << "1. Miss Scarlet" << endl;
	cout << "2. Mr. Green" << endl;
	cout << "3. Mrs. White" << endl;
	cout << "4. Professor Plum" << endl;
	cout << "5. Colonel Mustard" << endl;
	cout << "6. Mrs. Peacock" << endl;

	// Get input
	string input1;
	cin >> input1;

	// Set up validation loop--Won't be necessary if the UI incorporates buttons for the user to click when
	// suggesting
	bool valid = false;
	while (!valid)
	{
		if (input1 == "Notebook")
		{
			printNotebook();
			// This is essentially a placeholder
			cout << "Notebook printed. Please make a suspect selection:" << endl;
			cin >> input1;
		}
		else if (input1 == "Hand")
		{
			cout << "Your hand contains:" << endl;
			printHand();
			cout << "Hand printed. Please make a suspect selection:" << endl;
			cin >> input1;
		}
		// I understand this is a bit clunky but this is mainly for testing so idc
		else if (input1 == "1" || input1 == "2" || input1 == "3" || input1 == "4" || input1 == "5" || input1 == "6")
		{
			valid = true;
		}
		else
		{
			cout << "Input invalid. Please select a number or type Notebook or Hand to view those options" << endl;
			cin >> input1;
		}
	}

	// Change input to an int so that a switch statement can be used and my life can be made easier
	int choice1 = stoi(input1);

	// Add the suspect name to the suggestion based on the player's choice
	switch (choice1)
	{
		case 1:
		{
			suggestion.push_back("Miss Scarlet");
			break;
		}
		case 2:
		{
			suggestion.push_back("Mr. Green");
			break;
		}
		case 3:
		{
			suggestion.push_back("Mrs. White");
			break;
		}
		case 4:
		{
			suggestion.push_back("Professor Plum");
			break;
		}
		case 5:
		{
			suggestion.push_back("Colonel Mustard");
			break;
		}
		case 6:
		{
			suggestion.push_back("Mrs. Peacock");
			break;
		}
	}

	// Prompt user for weapon choice
	cout << "Choose a weapon to suggest by typing a number or type 'Notebook' or 'Hand' to view your notebook or hand" << endl;
	cout << "1. Rope" << endl;
	cout << "2. Wrench" << endl;
	cout << "3. Lead Pipe" << endl;
	cout << "4. Knife" << endl;
	cout << "5. Candlestick" << endl;
	cout << "6. Revolver" << endl;

	// Get input
	string input2;
	cin >> input2;

	// Set up validation loop--Won't be necessary if the UI incorporates buttons for the user to click when
	// suggesting
	valid = false;
	while (!valid)
	{
		if (input2 == "Notebook")
		{
			printNotebook();
			// This is essentially a placeholder
			cout << "Notebook printed. Please make a suspect selection:" << endl;
			cin >> input2;
		}
		else if (input2 == "Hand")
		{
			cout << "Your hand contains:" << endl;
			
			cout << "Hand printed. Please make a suspect selection:" << endl;
			cin >> input2;
		}
		// I understand this is a bit clunky but this is mainly for testing so idc
		else if (input2 == "1" || input2 == "2" || input2 == "3" || input2 == "4" || input2 == "5" || input2 == "6")
		{
			valid = true;
		}
		else
		{
			cout << "Input invalid. Please select a number or type Notebook or Hand to view those options" << endl;
			cin >> input2;
		}
	}

	// Change input to an int so that a switch statement can be used and my life can be made easier
	int choice2;
	choice2 = stoi(input2);

	// Add the suspect name to the suggestion based on the player's choice
	switch (choice2)
	{
		case 1:
		{
			suggestion.push_back("Rope");
			break;
		}
		case 2:
		{
			suggestion.push_back("Wrench");
			break;
		}
		case 3:
		{
			suggestion.push_back("Lead Pipe");
			break;
		}
		case 4:
		{
			suggestion.push_back("Knife");
			break;
		}
		case 5:
		{
			suggestion.push_back("Candlestick");
			break;
		}
		case 6:
		{
			suggestion.push_back("Revolver");
			break;
		}
	}

	// Pick a random room to make the suggestion out of since we don't have positional info yet and 
	// the player doesn't get to choose this

	suggestion.push_back(playerToken->get_space()->getName());


	return suggestion;
}

//returns true if any card from the suggestion exists in the player's hand; returns false if no cards from the suggestion exist
bool Player::containsCard(vector<string> suggestionList)
{
	for (int i = 0; i < this->hand.size(); i++) {
		if ((this->hand[i])->getName().compare(suggestionList[0]) == 0 || (this->hand[i])->getName().compare(suggestionList[1]) == 0 || (this->hand[i])->getName().compare(suggestionList[2]) == 0) {
			return true;
		}
	}
	return false;
}

//a player responds to another player's suggestion by showing one of their cards
//returns the name (string) of the card that they want to show
string Player::showCard(vector<string> suggestionList)
{
	vector<string> possibleChoices;
	int playerChoice;
	cout << "Which of the following cards would you like to share?" << endl;
	//create a temporary vector of matching cards that a player can choose from (ignores cards from the player's hand that weren't a part of the suggestion)
	for (int i = 0; i < this->hand.size(); i++) {
		if ((this->hand[i])->getName().compare(suggestionList[0]) == 0 || (this->hand[i])->getName().compare(suggestionList[1]) == 0 || (this->hand[i])->getName().compare(suggestionList[2]) == 0) {
			cout << this->hand[i]->getName() << endl;
			possibleChoices.push_back(hand[i]->getName());
		}
	}

	//list choices by number
	for (int i = 0; i < possibleChoices.size(); i++) {
		cout << i + 1 << ". " << possibleChoices[i] << endl;
	}

	cin >> playerChoice;
	while (!cin || playerChoice <= 0 || playerChoice > possibleChoices.size()) {		//validating that we want an integer response
		cout << "Please select a valid option." << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> playerChoice;
	}
	return possibleChoices[playerChoice-1];	
}

// change whether the player can make a suggestion or not
void Player::setSuggested(int flag){
	// 0 means the player can make a suggestion, 1 means they can't. Cant make a suggest in the same room that they started in.
	hasSuggested = flag;
}
 // return hasSuggested variable
bool Player::getSuggested(){
	return hasSuggested;
}

// return notebook array
int* Player::getNewNotebook()
{
	return newNotebook;
}

// flip notebook entry to 0 or 1;
void Player::flipNotebook(int entry)
{
	if (newNotebook[entry] == 0) {
		newNotebook[entry] = 1;
		cout << "1" << endl;
	}
	else {
		newNotebook[entry] = 0;
		cout << "0" << endl;
	}
}

// set alive status
void Player::setAlive(int status){
	alive = status;
}

// get alive status
bool Player::getAlive() {
	return alive;
}


