#include <iostream>
#include <string>
#include "GameClass.h"

using int32 = int;
using FTEXT = std::string;

int main() {
	GameClass ThisGame;
	ThisGame.SetMapSize();
	ThisGame.SetNumberOfMines();
	ThisGame.MakeMap();
	ThisGame.RunGame();

	system("PAUSE");

	return 0;
}