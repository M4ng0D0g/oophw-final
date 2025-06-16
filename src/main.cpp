#include <iostream>
#include <string>
#include "Game.h"
#include "Unit.h"
#include "view/AnsiPrint.h"
/**
 * Print my id
 * */
void
PrintMyID(std::string studId) {

    std::string str = "ID: " + studId;
    std::cout << AnsiPrint(
        str.c_str(),
        
        AnsiColor::Basic(3),
        AnsiColor::Basic(1),
        true,
        true
    ) << std::endl << std::endl;
}



int main(){
    // TODO 
    // Integrate the Simple MVC Pattern to run the program.
    Size2 fieldSize = {6, 6};

    Game game(fieldSize);
    game.start();

    // TODO
    // change to your student ID.
    PrintMyID("113703026");
}
