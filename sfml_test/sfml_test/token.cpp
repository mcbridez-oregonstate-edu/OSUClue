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
**	Name: get_token()
**	Descrition: returns the player's token
********************************************************************************************************************/
sf::CircleShape token::get_token()
{
	return player_token;
}

void token::move_token(double row, double col, int row_index, int col_index)
{
	sf::Vector2f pos = player_token.getPosition();
	player_token.setPosition(pos.x + row, pos.y + col);
	tile_row += row_index;
	tile_col += col_index;
	
}

int token::get_row() {
	return tile_row;
}


int token::get_col() {
	return tile_col;
}