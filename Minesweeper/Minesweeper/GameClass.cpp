#include "GameClass.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
using int32 = int;
using FTEXT = std::string;

GameClass::GameClass()
{
}

void GameClass::SetNumberOfMines()
{
	int32 val;
	std::cout << "How Many Mines should the Map have?(Positive and smaller than " << this->Higth*this->Wide << ")." << std::endl;
	do {
		std::cin >> val;
	} while (val > this->Higth*this->Wide || val <= 0);
	this->NumberOfMines = val;
}

void GameClass::SetMapSize()
{
	int32 val;
	std::cout << "How many columns?(between 3 and 20)" << std::endl;
	do {
		std::cin >> val;
	} while (val > 20 || val < 3);
	this->Wide = val;
	std::cout << "How many rows?(between 3 and 20)" << std::endl;
	do {
		std::cin >> val;
	} while (val > 20 || val < 3);
	this->Higth = val;
}


void GameClass::MakeMap()
{
	int32 MaxSize = this->Higth*this->Wide;
	srand(time(NULL));

	std::vector<int32> rows;
	std::vector<int32> columns;

	for (int32 i = 0; i < this->Higth; i++) {
		FTEXT row;
		for (int32 j = 0; j < this->Wide; j++) {
			row += ' ';
			rows.push_back(i);
			columns.push_back(j);
		}
		this->VisibleMap.push_back(row);// Set the visible map as empty(the player can't see anything before the game statrt)
		this->Map.push_back(row);	// Set the map with all the information
	}
	for (int32 i = 0; i < this->NumberOfMines; i++) {// Set the possition for the mines in the map 
		int32 rand_val = rand() % MaxSize;
		this->Map[rows[rand_val]][columns[rand_val]] = 'M';
		rows.erase(rows.begin() + rand_val);
		columns.erase(columns.begin() + rand_val);
		MaxSize--;
	}
	// Start Counting the number of mines in the surrounding area
	// Counting the mines in the center of the map
	for (int32 i = 1; i < this->Higth - 1; i++) {
		for (int32 j = 1; j < this->Wide - 1; j++) {
			if (this->Map[i][j] == ' ') {
				int32 val = 0;
				for (int32 k = i - 1; k <= i + 1; k++) {
					for (int32 l = j - 1; l <= j + 1; l++) {
						if (this->Map[k][l] == 'M') {
							val++;
						}
					}
				}
				this->Map[i][j] = '0' + val;
			}
		}
	}
	// Counting in the sides border 
	for (int32 i = 1; i < this->Higth - 1; i++) {
		if (this->Map[i][0] == ' ') {
			int32 val_top = 0;
			for (int32 k = i - 1; k <= i + 1; k++) {
				if (this->Map[k][0] == 'M') val_top++;
				if (this->Map[k][1] == 'M') val_top++;
			}
			this->Map[i][0] = '0' + val_top;
		}
		if (this->Map[i][this->Wide - 1] == ' ') {
			int32 val_bot = 0;
			for (int32 k = i - 1; k <= i + 1; k++) {
				if (this->Map[k][this->Wide - 1] == 'M') val_bot++;
				if (this->Map[k][this->Wide - 2] == 'M') val_bot++;
			}
			this->Map[i][this->Wide - 1] = '0' + val_bot;
		}

	}
	// Counting in the top/bottom borders
	for (int32 j = 1; j < this->Wide - 1; j++) {
		if (this->Map[0][j] == ' ') {
			int32 val_lef = 0;
			for (int32 l = j - 1; l <= j + 1; l++) {
				if (this->Map[0][l] == 'M') val_lef++;
				if (this->Map[1][l] == 'M') val_lef++;
			}
			this->Map[0][j] = val_lef + '0';
		}
		if (this->Map[this->Higth - 1][j] == ' ') {
			int32 val_rig = 0;
			for (int32 l = j - 1; l <= j + 1; l++) {
				if (this->Map[this->Higth - 1][l] == 'M') val_rig++;
				if (this->Map[this->Higth - 2][l] == 'M') val_rig++;
			}
			this->Map[this->Higth - 1][j] = val_rig + '0';
		}
	}
	//Counting on the edges
	if (this->Map[0][0] == ' ') {
		int32 val = 0;
		if (this->Map[1][0] == 'M') val++;
		if (this->Map[0][1] == 'M') val++;
		if (this->Map[1][1] == 'M') val++;
		this->Map[0][0] = val + '0';
	}
	if (this->Map[0][this->Wide - 1] == ' ') {
		int32 val = 0;
		if (this->Map[1][this->Wide - 1] == 'M') val++;
		if (this->Map[0][this->Wide - 2] == 'M') val++;
		if (this->Map[1][this->Wide - 2] == 'M') val++;
		this->Map[0][this->Wide - 1] = val + '0';
	}
	if (this->Map[this->Higth - 1][this->Wide - 1] == ' ') {
		int32 val = 0;
		if (this->Map[this->Higth - 2][this->Wide - 1] == 'M') val++;
		if (this->Map[this->Higth - 1][this->Wide - 2] == 'M') val++;
		if (this->Map[this->Higth - 2][this->Wide - 2] == 'M') val++;
		this->Map[this->Higth - 1][this->Wide - 1] = val + '0';
	}
	if (this->Map[this->Higth - 1][0] = ' ') {
		int32 val = 0;
		if (this->Map[this->Higth - 2][0] == 'M') val++;
		if (this->Map[this->Higth - 1][1] == 'M') val++;
		if (this->Map[this->Higth - 2][1] == 'M') val++;
		this->Map[this->Higth - 1][0] = val + '0';
	}
	this->CanPlay = true;
}


void GameClass::PrintMap()
{
	std::cout << std::endl;
	std::cout << "  ";
	for (int32 i = 0; i < this->Wide; i++) {
		if (i <= 9) {
			std::cout << " " << i;
		}
		else {
			std::cout << i;
		}
	}
	std::cout << std::endl;
	int32 row_number = 0;
	for (auto row : this->VisibleMap) {
		if (row_number < 10) {
			std::cout << row_number++ << " ";
		}
		else {
			std::cout << row_number++;
		}
		for (auto val : row) {
			std::cout << "|" << val;
		}
		std::cout << "|\n  ";
		for (int32 i = 0; i < this->Wide * 2 + 1; i++) {
			std::cout << "=";
		}
		std::cout << "\n";
	}
	//FTEXT PUFF;
	//std::getline(std::cin, PUFF);
	std::cout << "Mines: " << this->NumberOfMines << "\tMarked: " << this->MarkedMines << std::endl;
	std::cout << std::endl;
}

void GameClass::RunGame()
{
	if (!this->CanPlay) {
		std::cout << "Please make sure you run \"this.MakeMap()\" before \"this.RunGame\"" << std::endl;
		return;
	}
	this->PrintMap();
	int32 row = -1, col = -1;
	char opc = ' ';
	std::cout << "Insert D to dig and M to mark a position. Or Q to abandon this match." << std::endl;
	std::cout << "Insert the value of row and col you want to dig or Mark: " << std::endl;
	while (1) {
		do {
			std::cout << "Option: ";
			std::cin >> opc;
		} while (opc != 'M' && opc != 'D' && opc != 'm' && opc != 'd' && opc != 'q' && opc != 'Q');

		if (opc == 'q' || opc == 'Q') {
			FTEXT CIN_CLEANER; // used to clean the std input
			std::getline(std::cin, CIN_CLEANER);
			break;
		}
		while (row < 0 || row >= this->Wide) {
			std::cout << "Row: ";
			std::cin >> row;
		}
		while (col < 0 || col >= this->Higth) {
			std::cout << "Column: ";
			std::cin >> col;
		}
		FTEXT CIN_CLEANER; // used to clean the std input
		std::getline(std::cin, CIN_CLEANER);
		if (opc == 'D' || opc == 'd') {
			if (this->VisibleMap[row][col] == 'M') {
				std::cout << "You are digging where you marked as a mine, are you sure you want to dig here?(n to Not dig here)"<<std::endl;
				FTEXT answer = "";
				std::getline(std::cin, answer);
				if (answer[0] == 'n' or answer[0] == 'N') continue;
			}
			if (Map[row][col] == 'M') {
				this->GameOver();
				break;
			}
			else if (this->VisibleMap[row][col] == ' ') {
				AutoDig(row, col);
			}
		}
		if (opc == 'M' || opc == 'm') {
			this->VisibleMap[row][col] = 'M';
		}

		this->PrintMap();
		if (IsGameEnd()) break;
		opc = ' ';
		row = -1;
		col = -1;
	}
}

bool GameClass::IsGameEnd()
{
	int32 MapFillness = 0;
	int32 MinesMarked = 0;
	for (int32 i = 0; i < this->Higth; i++) {
		for (int32 j = 0; j < this->Wide; j++) {
			if (this->VisibleMap[i][j] != ' ') {
				MapFillness++;
			}
			if (this->VisibleMap[i][j] == 'M') {
				MinesMarked++;
			}
		}
	}
	this->MarkedMines = MinesMarked;
	if (MapFillness == this->Higth*this->Wide && MinesMarked == this->NumberOfMines) {
		GameWin();
		return true;
	}
	if (MinesMarked > this->NumberOfMines) {
		std::cout << "Too many Marked mines on the map!" << std::endl;
	}
	return false;
}

void GameClass::GameWin()
{
	std::cout << "wWWwwwWWwWWWWwwwWWw" << std::endl;
	std::cout << "WWwwwwWwwWWwWwwwwwW" << std::endl;
	std::cout << "WWwwwww\\/WWwwWWWww" << std::endl;
	std::cout << "  #=============#" << std::endl;
	std::cout << "  |   YOU WON   |" << std::endl;
	std::cout << "  #=============#" << std::endl;
	std::cout << "W And vegetagions w" << std::endl;
	std::cout << "wWwW recovers WwwWw" << std::endl;
	std::cout << "wwwwwwwwwwwwwwwwwww" << std::endl;
}


GameClass::~GameClass()
{
}

void GameClass::GameOver()  //Show the defeat screan
{
	std::cout << "    BOOOMMM!!!!" << std::endl;
	std::cout << "BOOOMMM!!!!" << std::endl;
	std::cout << "          BOOOMMM!!!!\n" << std::endl;
	std::cout << "#=============#" << std::endl;
	std::cout << "|  GAME OVER  |" << std::endl;
	std::cout << "#=============#" << std::endl;
	std::cout << "     BOOOMMM!!!!" << std::endl;
	std::cout << "BOOOMMM!!!!" << std::endl;
	std::cout << "          BOOOMMM!!!!\n" << std::endl;
}

void GameClass::AutoDig(int row, int col)
{
	
	this->VisibleMap[row][col] = this->Map[row][col];
	int32 new_row=row,new_col=col;

	if (this->VisibleMap[row][col] == '0') {
		if (row != 0 && col != 0) { // Check the top left corner 
			new_row = row - 1;
			new_col = col - 1;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
		if (row != 0 && col != (this->Wide - 1)) { // Check the top rigth corner 
			new_row = row - 1;
			new_col = col + 1;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
		if (row != (this->Higth - 1) && col != (this->Wide - 1)) { // Check the bottom rigth corner 
			new_row = row + 1;
			new_col = col + 1;
			if (VisibleMap[new_row][new_col] != Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
		if (row != (this->Higth - 1) && col != 0) { // Check the bottom left corner 
			new_row = row + 1;
			new_col = col - 1;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}

		if (row != 0) { // Check the top center corner 
			new_row = row - 1;
			new_col = col;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
		if (row != (this->Wide-1)) { // Check the bottom center corner 
			new_row = row + 1;
			new_col = col;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
		if ( col != 0) { // Check the center left corner 
			new_row = row;
			new_col = col - 1;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
		if (col != (this->Wide - 1)) { // Check the center rigth corner 
			new_row = row;
			new_col = col + 1;
			if (this->VisibleMap[new_row][new_col] != this->Map[new_row][new_col]) {
				AutoDig(new_row, new_col);
			}
		}
	}
}
