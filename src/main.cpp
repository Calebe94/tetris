#include <iostream>
#include "game.h"

int main(int argc, char *argv[])
{
    std::cout << "Usage: " << argv[0] << " " << argc << std::endl;

    TetrisGame tetris = TetrisGame();
    tetris.run();

    return 0;
}
