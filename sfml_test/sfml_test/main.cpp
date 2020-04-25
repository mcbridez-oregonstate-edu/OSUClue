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

			//setting the origin of each sprite
			rendered_board[i][j].move(sf::Vector2f(x_position, y_position));

			char currentRoom = boardArray[i][j].charTile();

			//setting textures according to the tile's type
			//room
			if (currentRoom == 'R')
			{
				rendered_board[i][j].setTexture(room_texture);
			}

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

	cout << "Press the right arrow key to move the piece." << endl;

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

		//sf::Sprite sprite;
		//sprite.setTexture(wall_texture);
		//window.draw(sprite);
		
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
			triangle.move(sf::Vector2f(100.0, 100.0));
			window.display();
			pieceMoved = true;
		}*/

		//test code for moving a piece
		//right arrow will move the piece to the bottom right
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				//window.clear();
				triangle.move(sf::Vector2f(25.0, 25.0));
				window.display();
			}
		}

    }
    return 0;
}

void writeToLog(string message, string variable) {
	ofstream log;
	log.open("log.txt", ios::app);
	log << message << " " << variable << endl;
	log.close();
}