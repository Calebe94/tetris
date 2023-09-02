#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "graphics.h"
#include "tetromino.h"

void static_display_tetromino(std::vector<std::vector<int>> shape)
{
    // std::vector<std::vector<int>> rotatedShape = tetromino.getShape();
    for (const auto& row : shape) {
        for (int value : row) {
            std::cout << (value == 1 ? '#' : ' ') << ' ';
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Usage: " << argv[0] << " " << argc << std::endl;

    Graphics graphics;
    bool quit = !graphics.init();

    Tetromino tetromino(T_SHAPE); // Create an I-shape Tetromino

    while(!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        graphics.clear();
    }

    return 0;
}
