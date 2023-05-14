// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <vector>

const int ROWS = 5;
const int COLS = 5;

class Tile
{
public:
	int value;
	bool discovered;
	int neighborCount;
	int xPos;
	int yPos;

	Tile()
	{
		xPos = -1;
		yPos = -1;
		value = 0;
		discovered = false;
		neighborCount = -1;
	}

	Tile(int _value, bool _discovered, int _neighborCount, int _xPos, int _yPos)
	{
		xPos = _xPos;
		yPos = _yPos;
		value = _value;
		discovered = _discovered;
		neighborCount = _neighborCount;
	}
};

// Type alias for a 2D vector of Tiles
using TileMap = std::vector<std::vector<Tile>>;


bool PositionIsValid(int x, int y)
{
	return (x >= 0) && (y >= 0) && (x < ROWS) && (y < COLS);
}

struct GameState {
	TileMap gameMap;  // This is public
	bool gameOver = false;
};

TileMap AddNeighborCounts(TileMap& uncountedMap)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int count = 0;
			if (PositionIsValid(i,j))
			{
				//Check neighbours.
				//N*
				if (PositionIsValid(i, j+1))
					if (uncountedMap[i][j + 1].value == 1)
						count++;
				//NE*
				if (PositionIsValid(i+1, j + 1))
					if (uncountedMap[i + 1][j + 1].value == 1)
						count++;
				//E
				if (PositionIsValid(i + 1, j))
					if (uncountedMap[i + 1][j].value == 1)
						count++;
				//SE
				if (PositionIsValid(i + 1, j - 1))
					if (uncountedMap[i + 1][j - 1].value == 1)
						count++;
				//S
				if (PositionIsValid(i, j - 1))
					if (uncountedMap[i][j - 1].value == 1)
						count++;
				//SW
				if (PositionIsValid(i - 1, j - 1))
					if (uncountedMap[i - 1][j - 1].value == 1)
						count++;
				//W
				if (PositionIsValid(i - 1, j))
					if (uncountedMap[i - 1][j].value == 1)
						count++;
				//NW
				if (PositionIsValid(i - 1, j + 1))
					if (uncountedMap[i - 1][j + 1].value == 1)
						count++;
			}
			uncountedMap[i][j].neighborCount = count;
		}
	}

	return uncountedMap;
}


TileMap BuildMap()
{
	TileMap map(ROWS, std::vector<Tile>(COLS));

	srand(time(NULL));

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if ((rand() % 100) >= 50)
			{
				std::cout << "Placing mine at location: " << i << " - " << j << "\n";
				map[i][j] = Tile(1, false, -1, i, j);
			}
			else
			{
				std::cout << "Placing blank at location: " << i << " - " << j << "\n";
				map[i][j] = Tile(0, false, -1, i, j);
			}			
		}
	}
	TileMap newCountedMap = AddNeighborCounts(map);
	return newCountedMap;
}

GameState RevealTile(TileMap currentMap,int x, int y)
{
	bool isGameOver = false;
	currentMap[x][y].discovered = true;
	
	if (currentMap[x][y].value == 1)
	{
		std::cout << "BOOM! GAME OVER!" << "\n";
		isGameOver = true;
	}
	else
	{
		std::cout << "Good job, that tile was safe." << "\n";
	}


	GameState currState;
	currState.gameMap = currentMap;
	currState.gameOver = isGameOver;
	return currState;
}

void PrintMap(TileMap currentMap)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (currentMap[i][j].discovered)
			{
				if (currentMap[i][j].value != 1)
				{
					std::cout << currentMap[i][j].neighborCount << " ";

				}
				else
				{
					std::cout << "* ";
				}
			}
			else
			{
				std::cout << "[]";
			}
			
		}
		std::cout << "\n";
	}
}

int main()
{
    std::cout << "Generating Map!\n";
	GameState gameState;
	gameState.gameMap = BuildMap();
	PrintMap(gameState.gameMap);
	while (true)
	{

		int colSelected = -1;

		std::cout << "Select a column: ";
		//Take Input
		std::cin >> colSelected;

		int rowSelected = -1;
		std::cout << "Select a row: ";
		std::cin >> rowSelected;
		//Take Input

		gameState = RevealTile(gameState.gameMap, rowSelected, colSelected);
		PrintMap(gameState.gameMap);
		if (gameState.gameOver)
			break;
	}

	
}