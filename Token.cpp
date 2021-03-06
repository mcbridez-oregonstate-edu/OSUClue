/*******************************************************************************************************************
**	Descrition: This is the implentation file for the token class. Represents the player's token. Holds the sprite for
**				the player's token as well as the indexes of the row/col of the tile the token is on. Has methods
**				to move the token and to return the position of it's location
********************************************************************************************************************/
#include <SFML/Graphics.hpp>
#include "token.hpp"




/*******************************************************************************************************************
**	Name: token(sf::Color color, double row_start, double col_start, int row, int col)
**	Descrition: Constructor for the token class. Takes as arguments, the color of the token, the coordinantes in pixels
**				of it's starting location, and the indexes of the tile of it's logical location.
********************************************************************************************************************/
token::token(sf::Color color, double row_start, double col_start, int row, int col)
{
	piece.setFillColor(color);
	piece.setRadius(9);
	piece.setPointCount(4);
	piece.setPosition(row_start, col_start);
	tile_row = row;
	tile_col = col;
}

/*******************************************************************************************************************
**	Name: token(std::string)
**	Descrition: Constructor for the token class. Takes a string as an argument. It will initialize the color
                and the starting location based on the string.
********************************************************************************************************************/
token::token(std::string name, double width, double height, boardTile*** board)
{
	sf::Color color;
	int row = 0;
	int col = 0;
	if (name == "Colonel Mustard")
	{
		color = sf::Color(225, 173, 1);
		row_start = 390 + (width * 17);
		col_start = 165 + (height * 23);
		row = 24;
		col = 18;
	}

	if (name == "Miss Scarlet")
	{
		color = sf::Color(139, 0, 0);
		row_start = 390 + (width * 24);
		col_start = 165 + (height * 16);
		row = 17;
		col = 25;
	}

	if (name == "Mr. Green")
	{
		color = sf::Color(0, 128, 0);
		row_start = 390 + (width * 0);
		col_start = 165 + (height * 9);
		row = 10;
		col = 1;
	}

	if (name == "Professor Plum")
	{
		color = sf::Color(221, 160, 221);
		row_start = 390 + (width * 19);
		col_start = 165 + (height * 0);
		row = 1;
		col = 20;
	}

	if (name == "Mrs. Peacock")
	{
		color = sf::Color(0, 0, 255);
		row_start = 390 + (width * 6);
		col_start = 165 + (height * 0);
		row = 1;
		col = 7;
	}

	if (name == "Mrs. White")
	{
		color = sf::Color(128, 128, 128);
		row_start = 390 + (width * 0);
		col_start = 165 + (height * 14);
		row = 15;
		col = 1;
	}
	
	piece.setFillColor(color);
	piece.setRadius(9);
	piece.setPointCount(4);
	piece.setPosition(row_start, col_start);
	tile_row = row;
	tile_col = col;
	current_space = board[tile_row][tile_col];
	current_space->setOccupied(1);
	this->name = name;
}

/*******************************************************************************************************************
**	Name: get_token()
**	Descrition: returns the player's token
********************************************************************************************************************/
sf::CircleShape token::get_token()
{
	return piece;
}

void token::move_token(double row, double col, int row_index, int col_index, boardTile*** board)
{
	sf::Vector2f pos = piece.getPosition();
	piece.setPosition(pos.x + row, pos.y + col);
	tile_row += row_index;
	tile_col += col_index;
	current_space = board[tile_row][tile_col];
}

int token::get_row() {
	return tile_row;
}


int token::get_col() {
	return tile_col;
}

/*******************************************************************************************************************
**	Name: boardTile get_space()
**	Descrition: returns the player's current space
********************************************************************************************************************/
boardTile* token::get_space() {
	
	return current_space;
}

/*******************************************************************************************************************
**	Name: string getName()
**	Descrition: returns the token's name
********************************************************************************************************************/
std::string token::getName() {
	return name;
}

void token::move_passage(double row, double col, int row_index, int col_index, boardTile*** board)
{
	piece.setPosition(row, col);
	tile_row = row_index;
	tile_col = col_index;
	current_space = board[row_index][col_index];

}

// set token color to black (no longer in game)
void token::setBlack() 
{
	piece.setPosition(sf::Vector2f(row_start, col_start));
	piece.setFillColor(sf::Color::Black);
}