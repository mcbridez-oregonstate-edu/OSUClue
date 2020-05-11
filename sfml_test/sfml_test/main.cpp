#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include "clueBoard.h"
using namespace std;
void writeToLog(string message, string variable);

int main()
{
	//making a matrix representing the board
	boardTile** boardArray = new boardTile * [27];
	for (int i = 0; i < 27; i++) {
		boardArray[i] = new boardTile[27];
	}
	boardTile room = boardTile("r");
	boardTile floor = boardTile("f");
	boardTile wall = boardTile("w");

	//opening csv file to fill board data
	ifstream dataSource;
	dataSource.open("ClueBoardCSV.csv");
	if (dataSource.fail()) {
		cout << "Failed to open csv." << endl;
		return 0;
	}
	ofstream log;
	log.open("log.txt", ofstream::out | ofstream::trunc);
	if (log.fail()) {
		cout << "Failed to open log" << endl;
		return 0;
	}
	log.close();
	string line, word, temp;
	int row = 0;
	int col = 0;
	
	//filling the board based on data from the CSV
	while (!dataSource.eof()) {
		string tempStringArray[27];
		col = 0;
		getline(dataSource, line);
		writeToLog("Grabbed line of:", line);
		stringstream tempstream(line);
		while (getline(tempstream, word, ',')) {
			boardTile tempTile(word, row, col);
			writeToLog("Grabbed tile type:", word);
			boardArray[row][col] = tempTile;
			col++;
		}
		row++;
	}
	clueBoard gameBoard(boardArray);
	cout << "Board of chars: " << endl;
	gameBoard.charBoard();

	//graphical output section
	//creating a render window with SFML
	sf::RenderWindow window(sf::VideoMode(810, 810), "Clue!", sf::Style::Default);
	

	//making textures
	sf::Texture room_texture;
	if (!room_texture.loadFromFile("room.bmp", sf::IntRect(0, 0, 30, 30)))
	{
		cout << "Cannot open room.bmp" << endl;
	}

	sf::Texture wall_texture;
	if (!wall_texture.loadFromFile("wall.bmp", sf::IntRect(0, 0, 30, 30)))
	{
		cout << "Cannot open wall.bmp" << endl;
	}

	sf::Texture floor_texture;
	if (!floor_texture.loadFromFile("floor.bmp", sf::IntRect(0, 0, 30, 30)))
	{
		cout << "Cannot open floor.bmp" << endl;
	}

	//making mustard colored test piece
	sf::CircleShape triangle(30, 3);
	triangle.setFillColor(sf::Color(225, 173, 1));
	
	//making a matrix of empty sprites
	sf::Sprite** rendered_board = new sf::Sprite * [27];
	for (int i = 0; i < 27; i++)
	{
		rendered_board[i] = new sf::Sprite[27];
	}

	//filling the sprites
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			//setting coordinates in window
			double x_position = 30.0 * i;
			double y_position = 30.0 * j;

<<<<<<< Updated upstream
			//setting the origin of each sprite
			rendered_board[i][j].move(sf::Vector2f(x_position, y_position));
=======
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				//move a piece right
				if (event.key.code == sf::Keyboard::Right)
				{
					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()], boardArray[players[current_player]->get_row()][players[current_player]->get_col() + 1])) {
						players[current_player]->move_token(width, 0, 0, 1);
					}

					break;
				}

				//move a piece left
				if (event.key.code == sf::Keyboard::Left)
				{
					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()], boardArray[players[current_player]->get_row()][players[current_player]->get_col() - 1])) {
						players[current_player]->move_token(-width, 0, 0, -1);
					}

					break;
				}

				//movve a piece down
				if (event.key.code == sf::Keyboard::Down)
				{
					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()], boardArray[players[current_player]->get_row() + 1][players[current_player]->get_col()])) {
						players[current_player]->move_token(0, height, 1, 0);
					}

					break;
				}

				//move a piece up
				if (event.key.code == sf::Keyboard::Up)
				{
					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()],
						boardArray[players[current_player]->get_row() - 1][players[current_player]->get_col()])) {
						players[current_player]->move_token(0, -height, -1, 0);
					}

					break;
				}

				//change player control
				if (event.key.code == sf::Keyboard::Enter)
				{
					current_player++;

					if (current_player > num_players)
					{
						current_player = 0;
					}
				}
>>>>>>> Stashed changes

			char currentRoom = boardArray[i][j].charTile();

			//setting textures according to the tile's type
			//room
			if (currentRoom == 'R')
			{
				rendered_board[i][j].setTexture(room_texture);
			}
<<<<<<< Updated upstream

			//wall
			if (currentRoom == 'W')
			{
				rendered_board[i][j].setTexture(wall_texture);
			}

			//floor
			if (currentRoom == 'F')
			{
				rendered_board[i][j].setTexture(floor_texture);
			}
		}
	}

	cout << "Move the piece with arrow keys or left click." << endl;

	//rendering window
    while (window.isOpen())
    {
		//sf::Time move_delay = sf::seconds(0.1f);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		
		//drawing board's sprites
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 27; j++)
			{
				window.draw(rendered_board[i][j]);
			}
		}

		//putting test piece on board
		//order matters on SFML
		//last sprite drawn is on top
		window.draw(triangle);
        window.display();

		//commented out this block of code
		//it was testing time based movement delays
		/*sf::Time elapsed = clock.getElapsedTime();
		//testing moving the piece
		if ((pieceMoved == false) && (elapsed > sf::seconds(1.0f)))
		{
			window.clear();
			triangle.move(sf::Vector2f(10.0, 10.0));
			window.display();
			pieceMoved = true;
		}*/

		//test code for moving a piece with mouse input
		//function sets the triangles positions
		//to where the mouse cursor is when clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			triangle.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		}

		//test code for moving a piece
		//arrow keys will move a piece in that direction
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				triangle.move(sf::Vector2f(10.0, 0));
			}

			if (event.key.code == sf::Keyboard::Left)
			{
				triangle.move(sf::Vector2f(-10.0, 0));
			}

			if (event.key.code == sf::Keyboard::Down)
			{
				triangle.move(sf::Vector2f(0, 10.0));
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				triangle.move(sf::Vector2f(0, -10.0));
			}
=======
		}

		window.clear();

		window.draw(rendered_board);
		window.draw(mustard.get_token());
		window.draw(scarlett.get_token());
		window.draw(green.get_token());
		window.draw(plum.get_token());
		window.draw(peacock.get_token());
		window.draw(white.get_token());
		window.display();
>>>>>>> Stashed changes
		}

    }
    return 0;
}

void writeToLog(string message, string variable) {
	ofstream log;
	log.open("log.txt", ios::app);
	log << message << " " << variable << endl;
	log.close();
<<<<<<< Updated upstream
=======
}

bool isValidMove(boardTile current_space, boardTile target_space) {
	if (target_space.isOccupied())
	{
		return false;
	}

	if (target_space.isPassable()) {
		if ((current_space.getTile_type() == Room && target_space.getTile_type() == Floor) || (current_space.getTile_type() == Floor && target_space.getTile_type() == Room)) {

			if (current_space.hasDoor() && target_space.hasDoor()) {

				return true;
			}
			else {

				return false;
			}
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}

>>>>>>> Stashed changes
}