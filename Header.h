#pragma once
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Random.h"
using namespace sf;
using namespace std; 

struct Tile { //structure to represent an individual tile
	unsigned int xPos; //tile's x position
	unsigned int yPos; //tile's y position
	Sprite tileSprite; //the sprite that represents the tile
	bool isRevealed; //boolean to represent if the tile has been revealed
	bool existanceTest; //if the current tile exists or not 
	bool hasMine; //bool for if the tile is a mine or not
	bool isFlagged; //if the tile has been flagged for mines
	int numberOnTile; //the number that is on the current tile (if any)
	Tile* neighbors[8]; //an array to track the number of neighbors around a tile and pointers to them
	int numNeighbors; //the number of neighbors there are 
	int neighborMines; 

	Tile(unsigned int xPos, unsigned int yPos, Sprite& tileSprite) { //constructor to create a tile, must have x and y coordinates and assigns them to their variables 
		this->xPos = xPos;
		this->yPos = yPos;
		this->tileSprite = tileSprite;
		isRevealed = false; 
		hasMine = false;
		existanceTest = false; 
		isFlagged = false; 
		numNeighbors = 0; 
		numberOnTile = 0; 
		neighborMines = 0; 
	}
};


struct Board {
	unsigned int boardWidth; //width of the entire board
	unsigned int boardHeight; //height of the entire board
	unsigned int minesCount; //number of mines on the board total
	unsigned int tileCount; //total number of tiles 
	unsigned int windowWidth; //width of the window
	unsigned int windowHeight; //height of the window

	Board() {
		ifstream boardSize; //creates a file input
		boardSize.open("boards/config.cfg"); //opens the config file to get the dimensions of the board 
		string temp = ""; //creates a temp string to use in getline

		getline(boardSize, temp); //reads the width 

		boardWidth = stoi(temp); //assigns the width to the proper variable, width is also number of columns

		getline(boardSize, temp); //reads the height

		boardHeight = stoi(temp); //assigns the height to the proper variable, height is also number of rows

		getline(boardSize, temp); //reads the number of mines 

		minesCount = stoi(temp); //assigns the number of mines to the correct variable

		tileCount = boardWidth * boardHeight; //calculates the total number of tiles


		windowWidth = boardWidth * 32; //calculates the width of the window in pixels 
		windowHeight = (boardHeight * 32) + 100; //calculates the height of the window in pixels

		//cout << "Board width: " << boardWidth << endl;
		//cout << "Board height: " << boardHeight << endl;
		//cout << "Tile Count: " << tileCount << endl;

	} 

	void setUp(RenderWindow& window, vector<vector<Tile*>>& tileList) { //used to set up the game board when first booting the game up 
		Texture emptyTileTexture;
		emptyTileTexture.loadFromFile("images/tile_revealed.png");

		Texture hiddenTileTexture;
		hiddenTileTexture.loadFromFile("images/tile_hidden.png");

		for (unsigned int i = 0; i < boardWidth; i++) { //goes through the entire width of each row
			
			vector<Tile*> tempVector; //used to be added to the tileList vector later on to make a 2d vector
			
			for (unsigned int j = 0; j < boardHeight; j++) { //goes through most of the height of the board except 100 at the bottom for the main buttons
				Sprite hiddenTile; //creates a sprite that represents the unrevealed tile above an empty tile
				
				
				hiddenTile.setTexture(hiddenTileTexture);
				hiddenTile.setPosition(i * 32, j * 32); //sets the unrevealed tile in a proper location

				window.draw(hiddenTile); //draws the unrevealed tile to the screen

				Tile* currentTile = nullptr; //creates a pointer to represent a tile


				if (tileList.size() < 400) {
					currentTile = new Tile(i * 32, j * 32, hiddenTile); //pointer that stores the tile

					tempVector.push_back(currentTile);
				}
			}

			tileList.push_back(tempVector); //adds the tempVector to the tileList vector

		}
	}

	void placeMines(vector<vector<Tile*>>& tileList) { //method used one time to set up the mine's position on the board
		srand((unsigned)time(0));
		
		for (unsigned int i = 0; i < minesCount; i++) { //goes through the number of mines we want on the board
			int mineX = Random::Int(0, boardWidth - 1); //gets a random x location 
			int mineY = Random::Int(0, boardHeight - 1); //gets a random x location 

			if (tileList[mineX][mineY]->hasMine) { //if the random tile already has a mine on it
				int mineX2; //create two new placeholder variables 
				int mineY2; 

				do { //while these random locations have mines, keep getting random locations until one is found that does not have a mine
					mineX2 = Random::Int(0, boardWidth - 1); //gets a random x location 
					mineY2 = Random::Int(0, boardHeight - 1); //gets a random x location 

				} while (tileList[mineX2][mineY2]->hasMine);

				tileList[mineX2][mineY2]->hasMine = true; //set the tile at this location to now have a mine
			}
			else //if the location does not have a mine, it now has a mine
			{
				tileList[mineX][mineY]->hasMine = true; //sets the location to now have a mine
			}

		}
	
	}

	

};

