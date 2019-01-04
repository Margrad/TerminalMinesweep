#include <iostream>
#include <string>
#include "GameClass.h"

using int32 = int;
using FTEXT = std::string;

int main() {

	FTEXT answer = "n";
    while(1){
	GameClass ThisGame;
	ThisGame.Intro();
	ThisGame.SetMapSize();
	ThisGame.SetNumberOfMines();
	ThisGame.MakeMap();
	ThisGame.RunGame();

	std::cout << "Do you want to  play again?" << std::endl;
    std::getline(std::cin,answer);
    if(answer[0] == 'y' || answer[0] == 'Y') continue;
	break;
    }

	return 0;
}
