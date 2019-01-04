#pragma once
#include "GameClass.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

using int32 = int;
using FTEXT = std::string;

class GameClass
{
public:
	GameClass();
	void Intro();			// A bit of Ascii art to start the game
	void SetNumberOfMines();// Ask the player for the number of mines in this level
	void SetMapSize();		// Ask the player for the size of the map
	void MakeMap();			// Sets the map after the use of the 2 previows functions
	void PrintMap();		// Prints the visible map on the console
	void RunGame();			// Cicle throgh the game asking the player what to do and check of the game end		
	~GameClass();
private:
	int32 NumberOfMines=1;	// Number of Mines in this level
	int32 MarkedMines = 0;	// Number of Market plots of land
	int32 Higth=3, Wide=3;	// Size of level map
	bool CanPlay = false;	// Checks if RunGame() can be used
	void GameOver();		// Game Over message for when the palyer hits a mine
	void AutoDig(int, int);		// Auto removes empty plots when the player hits a plot of land with no surrounding mines
	bool IsGameEnd();		// Checks if the game ends in vitory
	void GameWin();			// Game Victory message
	std::vector<FTEXT> Map;		// 'M' = mine; ' ' = nothing; n = number of surronding
	std::vector<FTEXT> VisibleMap;	// n = number of surronding mines; M = Suspected mine;
};
