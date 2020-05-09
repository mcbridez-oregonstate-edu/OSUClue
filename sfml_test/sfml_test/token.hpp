/*******************************************************************************************************************
**	Descrition: This is the header file for the token class. Represents the player's token. Holds the sprite for
**				the player's token as well as the indexes of the row/col of the tile the token is on. Has methods
**				to move the token and to return the position of it's location
********************************************************************************************************************/
#ifndef TOKEN_H
#define TOKEN_H
#include <SFML/Graphics.hpp>

class token {
private:
	sf::CircleShape player_token;
	int tile_row;
	int tile_col;
		
public:

	token(sf::Color color, double row_start, double col_start, int row, int col);
	sf::CircleShape get_token();
	void move_token(double row, double col, int row_index, int col_index);
	int get_row();
	int get_col();
	
};


#endif