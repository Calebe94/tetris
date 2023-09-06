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
    this->boardWidth = (this->graphics.getScreenWidth() / 32);
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
    currentTetromino.setX((graphics.getScreenWidth()/TILE_SIZE)/2 * TILE_SIZE);
    currentTetromino.setY(TILE_SIZE * 2);
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
                    this->currentTetromino.moveLeft();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveRight();
                    }
                    break;
                case SDLK_RIGHT:
                    info("Right key!");
                    this->currentTetromino.moveRight();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveLeft();
                    }
                    break;
                case SDLK_DOWN:
                    info("Down key!");
                    this->currentTetromino.moveDown();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveUp();
                    }
                    break;
                case SDLK_UP:
                    info("UP key!");
                    this->currentTetromino.moveUp();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveDown();
                    }
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
    if(this->isCollision())
    {

    }

    this->graphics.render();
}

bool TetrisGame::checkBorderCollisions()
{
    for (int i = 0; i < currentTetromino.getSize(); ++i) {
        for (int j = 0; j < currentTetromino.getSize(); ++j) {
            if (currentTetromino.getShape()[i][j]) {
                int initial_gridX = (currentTetromino.getX() + j) / TILE_SIZE;
                int end_gridX = initial_gridX+currentTetromino.getSize()-1;
                int initial_gridY = (currentTetromino.getY() + i) / TILE_SIZE;
                int end_gridY = initial_gridY+currentTetromino.getSize()-1;

                if(gameBoard[initial_gridY][initial_gridX] == 255 && gameBoard[initial_gridY][end_gridX] == 255)
                {
                    std::cout << "top" << std::endl;
                    return true;
                }
                if(gameBoard[initial_gridY][initial_gridX] == 255 && gameBoard[end_gridY][initial_gridX] == 255)
                {
                    std::cout << "left" << std::endl;
                    return true;
                }

                if(gameBoard[initial_gridY][end_gridX] == 255 && gameBoard[end_gridY][end_gridX] == 255)
                {
                    std::cout << "right" << std::endl;
                    return true;
                }

                if(gameBoard[end_gridY][initial_gridX] == 255 && gameBoard[end_gridY][end_gridX] == 255)
                {
                    std::cout << "bottom" << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
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
