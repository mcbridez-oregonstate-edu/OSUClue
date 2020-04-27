/********************************************************************************
** Created by: Devin Mourrain
** Date: 4/26/2020
** Description: This is the Token class header file. It establishes the 
				attributes that a Token can have. It essentially the same as the card class
********************************************************************************/

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include<string>
#include<string>
#include<vector>
#include<tuple>

enum TokenType { WEAPON_T, SUSPECT_T, PLACE_T };

class Token {
private:
	std::string name;
	TokenType type;
	std::tuple<int, int> position;				//the player's token's current (x,y) coordinate

public:
	Token();
	Token(std::string tokenName, TokenType tokenType, std::tuple<int, int> position);
	std::string getName();
	TokenType getType();
	std::tuple<int, int> getPosition();
	void updatePosition(std::tuple<int, int>);
};



#endif