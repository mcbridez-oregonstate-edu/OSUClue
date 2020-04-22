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
	boardTile** boardArray = new boardTile * [27];
	for (int i = 0; i < 27; i++) {
		boardArray[i] = new boardTile[27];
	}
	boardTile room = boardTile("r");
	boardTile floor = boardTile("f");
	boardTile wall = boardTile("w");

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

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	
	//making textures
	sf::Texture room_texture;
	if (!room_texture.loadFromFile("room.bmp"))
	{
		// error...
	}

	sf::Texture wall_texture;
	if (!wall_texture.loadFromFile("wall.bmp"))
	{
		// error...
	}

	sf::Texture floor_texture;
	if (!floor_texture.loadFromFile("floor.bmp"))
	{
		// error...
	}
	
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
			double x_position = 24.0 * i;
			double y_position = 24.0 * j;

			rendered_board[i][j].setOrigin(sf::Vector2f(x_position, y_position));

			char currentRoom = boardArray[i][j].charTile();

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


    while (window.isOpen())
    {
        
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
		
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 27; j++)
			{
				window.draw(rendered_board[i][j]);
			}
		}

        window.display();
    }

    return 0;
}

void writeToLog(string message, string variable) {
	ofstream log;
	log.open("log.txt", ios::app);
	log << message << " " << variable << endl;
	log.close();
}