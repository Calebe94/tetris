#include "seethe.h"
#include "graphics.h"
#include "tetromino.h"
#include <vector>
#include "game.h"

static void display_tetromino(std::vector<std::vector<int>> shape)
{
    for (const auto& row : shape) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}

TetrisGame::TetrisGame() : currentTetromino((shape_t)(rand() % 7))
{

}

void TetrisGame::run()
{
    initializeGame();

    while(!this->quit)
    {
        this->frameStart = SDL_GetTicks(); // Get the current time

        this->handleEvents();
        this->update();
        this->render();

        this->frameTime = SDL_GetTicks() - this->frameStart; // Calculate frame time

        // Limit frame rate
        if (this->frameTime < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - this->frameTime);
        }
    }
}

void TetrisGame::initializeGame()
{
    this->quit = !this->graphics.init();
    display_tetromino(this->currentTetromino.getShape());
    srand (time(NULL));
}

void TetrisGame::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
        {
            this->quit = true;
            // exit(0);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    info("Left key!");
                    break;
                case SDLK_RIGHT:
                    info("Right key!");
                    break;
                case SDLK_DOWN:
                    info("Down key!");
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
}

void TetrisGame::update()
{

}

void TetrisGame::render()
{
    this->graphics.clear();

    Tile tile = Tile(this->graphics.getRenderer());
    currentTetromino.setTile(tile);
    currentTetromino.applyColors();

    currentTetromino.tick();
    currentTetromino.render();

    this->graphics.render();
}

bool TetrisGame::isCollision()
{
    return true;
}

void TetrisGame::placeTetromino()
{

}

void TetrisGame::clearRows()
{

}
