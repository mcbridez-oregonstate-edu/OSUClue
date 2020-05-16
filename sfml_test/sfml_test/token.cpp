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
	player_token.setFillColor(color);
	player_token.setRadius(9);
	player_token.setPointCount(4);
	player_token.setPosition(row_start, col_start);
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
	double row_start = 0;
	double col_start = 0;
	int row = 0;
	int col = 0;
	if (name == "mustard")
	{
		color = sf::Color(225, 173, 1);
		row_start = 155 + (width * 17);
		col_start = 165 + (height * 23);
		row = 24;
		col = 18;
	}

	if (name == "scarlett")
	{
		color = sf::Color(139, 0, 0);
		row_start = 155 + (width * 24);
		col_start = 165 + (height * 16);
		row = 17;
		col = 25;
	}

	if (name == "green")
	{
		color = sf::Color(0, 128, 0);
		row_start = 155 + (width * 0);
		col_start = 165 + (height * 9);
		row = 10;
		col = 1;
	}

	if (name == "plum")
	{
		color = sf::Color(221, 160, 221);
		row_start = 155 + (width * 19);
		col_start = 165 + (height * 0);
		row = 1;
		col = 20;
	}

	if (name == "peacock")
	{
		color = sf::Color(0, 0, 255);
		row_start = 155 + (width * 6);
		col_start = 165 + (height * 0);
		row = 1;
		col = 7;
	}

	if (name == "white")
	{
		color = sf::Color(128, 128, 128);
		row_start = 155 + (width * 0);
		col_start = 165 + (height * 14);
		row = 15;
		col = 1;
	}
	
	player_token.setFillColor(color);
	player_token.setRadius(9);
	player_token.setPointCount(4);
	player_token.setPosition(row_start, col_start);
	tile_row = row;
	tile_col = col;
	current_space = board[tile_row][tile_col];
	current_space->setOccupied(1);
}

/*******************************************************************************************************************
**	Name: get_token()
**	Descrition: returns the player's token
********************************************************************************************************************/
sf::CircleShape token::get_token()
{
	return player_token;
}

void token::move_token(double row, double col, int row_index, int col_index, boardTile*** board)
{
	sf::Vector2f pos = player_token.getPosition();
	player_token.setPosition(pos.x + row, pos.y + col);
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