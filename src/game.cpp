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

    // TODO: I should find a way to round up numbers, because at this point the height(672) and width(476) is hard coded and 476/32 is 14.93,
    // I need it to be at least 15
    this->boardWidth = (this->graphics.getScreenWidth() / 32)+1;
    this->boardHeight = this->graphics.getScreenHeight() / 32;

    std::cout << "Board width: " << boardWidth << std::endl;
    std::cout << "Board height: " << boardHeight << std::endl;

    gameBoard.resize(boardHeight, std::vector<int>(boardWidth, 0));
    std::cout << "Board dimensions: " << gameBoard.size() << " " << gameBoard[0].size() << std::endl;

    for (int row = 0; row < boardHeight; row++)
    {
        gameBoard[row][0] = 255;
    }

    for (int row = 0; row < boardHeight; row++)
    {
        gameBoard[row][boardWidth-1] = 255;
    }

    for (int col = 0; col < boardWidth; col++)
    {
        gameBoard[0][col] = 255;
    }

    for (int col = 0; col < boardWidth; col++)
    {
        gameBoard[boardHeight-1][col] = 255;
    }

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
                    if(this->currentTetromino.getX()-30 <= 0)
                    {
                        this->currentTetromino.setX(0);
                    }
                    else
                    {
                        this->currentTetromino.setX(this->currentTetromino.getX()-30);
                    }
                    break;
                case SDLK_RIGHT:
                    if(this->currentTetromino.getX()+30+30 > this->graphics.getScreenWidth())
                    {
                        this->currentTetromino.setX(this->graphics.getScreenWidth()-60);
                    }
                    else
                    {
                        this->currentTetromino.setX(this->currentTetromino.getX()+30);
                    }
                    info("Right key!");
                    break;
                case SDLK_DOWN:
                    info("Down key!");
                    this->currentTetromino.setY(this->currentTetromino.getY()+30);
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
    tile.setColors(BASE_COLORS[0], LIGHT_COLORS[0], DARK_COLORS[0]);

    for (int row = 0; row < this->boardHeight; row++)
    {
        for (int col = 0; col < this->boardWidth; col++)
        {
            if(gameBoard[row][col] == 255)
            {
                tile.drawCell(0, 0, col*32, row*32);
            }
        }
    }

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
