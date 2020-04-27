#include "Token.hpp"

#include <string>
#include <vector>
#include <tuple>

Token::Token()
{
	this->name = "N/A";
	this->position = std::make_tuple(-1, -1);
}

Token::Token(std::string tokenName, TokenType tokenType, std::tuple<int, int> position)
{
	this->name = tokenName;
	this->type = tokenType;
	this->position = position;
}

std::string Token::getName()
{
	return this->name;
}

TokenType Token::getType()
{
	return this->type;
}

std::tuple<int, int> Token::getPosition()
{
	return this->position;
}

void Token::updatePosition(std::tuple<int, int> pos)
{
	this->position = pos;
}
