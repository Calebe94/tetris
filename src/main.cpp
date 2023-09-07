#include <iostream>
#include <time.h>
#include "game.h"

int main(int argc, char *argv[])
{
    std::cout << "Usage: " << argv[0] << " " << argc << std::endl;

    srand (time(NULL));
    TetrisGame tetris = TetrisGame();
    tetris.run();

    return 0;
}
