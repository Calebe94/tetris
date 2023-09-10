#include <iostream>
#include <time.h>
#include "seethe.h"
#include "game.h"

TetrisGame tetris = TetrisGame();

void loop()
{
    #ifndef __EMSCRIPTEN__
    while(!tetris.isRunning())
    {
        tetris.loop();
    }
    #else
    tetris.loop();
    #endif
}

int main(int argc, char *argv[])
{
    info("Initializing Tetris!");

    if(argc > 1)
    {
        info("Command line arguments not implemented yet!");
        info("Usage: %s", argv[0]);
        info("If you have any questions or want to point something out, here is some personal information about the developer:");
        info("Author: Edimar Calebe Castanho");
        info("Email: contato@calebe.dev.br");
        info("Issues: https://github.com/Calebe94/tetris/issues");
    }

    srand (time(NULL));

    tetris.run();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&loop, 0, 1);
#else
    loop();
#endif
    return 0;
}
