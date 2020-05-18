/*******************************************************************************************************************
**	Description: This is the header file for the token class. Represents the player's token. Holds the sprite for
**				the player's token as well as the indexes of the row/col of the tile the token is on. Has methods
**				to move the token and to return the position of it's location
********************************************************************************************************************/
#ifndef TOKEN_H
#define TOKEN_H
#include <SFML/Graphics.hpp>
#include "boardTile.h"
#include <string>

class token {
private:
	sf::CircleShape piece;
	std::string name;
	boardTile* current_space;
	int tile_row;
	int tile_col;
		
public:

	token(sf::Color color, double row_start, double col_start, int row, int col);
	token(std::string name, double width, double height, boardTile*** board);
	sf::CircleShape get_token();
	void move_token(double row, double col, int row_index, int col_index, boardTile*** board);
	boardTile* get_space();
	int get_row();
	int get_col();
	std::string getName();
	
};


#endif