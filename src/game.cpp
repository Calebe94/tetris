#include "seethe.h"
#include "graphics.h"
#include "tetromino.h"
#include <vector>
#include "game.h"

TetrisGame::TetrisGame() : currentTetromino((shape_t)(rand() % 7))
{
    lastTime = SDL_GetTicks();
}

void TetrisGame::run()
{
    initializeGame();

    // TODO: I should find a way to round up numbers, because at this point the height(672) and width(476) is hard coded and 476/32 is 14.93,
    // I need it to be at least 15
    this->boardWidth = (this->graphics.getScreenWidth() / 32);
    this->boardHeight = this->graphics.getScreenHeight() / 32;

    debug("Board width: %d", boardWidth);
    debug("Board height: %d", boardHeight);

    gameBoard.resize(boardHeight, std::vector<int>(boardWidth, 0));
    debug("Board dimensions: %ld %ld", gameBoard.size(), gameBoard[0].size());

    createBorders();

    info("Game initialized!");

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
    debug("Initializing SDL2 graphics...");
    this->quit = !this->graphics.init();
    placeTetromino();
}

void TetrisGame::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
        {
            this->quit = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    debug("Left key!");
                    this->currentTetromino.moveLeft();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveRight();
                    }
                    break;
                case SDLK_RIGHT:
                    debug("Right key!");
                    this->currentTetromino.moveRight();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveLeft();
                    }
                    break;
                case SDLK_DOWN:
                    debug("Down key!");
                    this->currentTetromino.moveDown();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveUp();
                    }
                    break;
                case SDLK_UP:
                    debug("UP key!");
                    this->currentTetromino.rotateClockwise();
                    debug("Tetromino vertical size: %d", this->currentTetromino.getVerticalSize());
                    debug("Tetromino horizontal size: %d", this->currentTetromino.getHorizontalSize());
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
}

void TetrisGame::update()
{
    currentTetromino.tick();
    if (SDL_GetTicks() - lastTime >= 300) {
        lastTime = SDL_GetTicks();
        this->currentTetromino.moveDown();
        // Check for collisions with the bottom border or other tiles
        if (checkBorderCollisions()) {
            // Revert the move if a collision occurs
            currentTetromino.moveUp();

            // Append the shape of the Tetromino to the gameBoard
            appendTetrominoToGameBoard();

            // Check for and clear completed rows (not shown in this code)
            clearRows();

            createBorders();

            // Display the gameBoard
            displayGrid();

            // Place another tetromino
            placeTetromino();
        }
    }
}

void TetrisGame::render()
{
    this->graphics.clear();

    Tile tile = Tile(this->graphics.getRenderer());

    for (int row = 0; row < this->boardHeight; row++)
    {
        for (int col = 0; col < this->boardWidth; col++)
        {
            if(gameBoard[row][col] == 255)
            {
                tile.setColors(BASE_COLORS[0], LIGHT_COLORS[0], DARK_COLORS[0]);
                tile.drawCell(0, 0, col*32, row*32);
            }
            else if(gameBoard[row][col] == 0); // Do nothing, for now
            else
            {
                tile.setColors(BASE_COLORS[gameBoard[row][col]], LIGHT_COLORS[gameBoard[row][col]], DARK_COLORS[gameBoard[row][col]]);
                tile.drawCell(0, 0, col*32, row*32);
            }
        }
    }

    currentTetromino.setTile(tile);
    currentTetromino.applyColors();

    currentTetromino.render();

    this->graphics.render();
}

bool TetrisGame::checkBorderCollisions() {
    std::vector<std::vector<int>> tetrominoShape = currentTetromino.getShape();
    int tetrominoX = currentTetromino.getX();
    int tetrominoY = currentTetromino.getY();

    for (int i = 0; i < currentTetromino.getSize(); i++) {
        for (int j = 0; j < currentTetromino.getSize(); ++j) {
            if (tetrominoShape[i][j]) {
                int gridX = (tetrominoX + j * TILE_SIZE) / TILE_SIZE;
                int gridY = (tetrominoY + i * TILE_SIZE) / TILE_SIZE;

                if (gridX < 0 || gridX >= boardWidth || gridY >= boardHeight || gameBoard[gridY][gridX]) {
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
    debug("Placing a tetromino...");
    // Create a new random Tetromino
    currentTetromino = Tetromino((shape_t)(rand() % 7));
    if(!currentTetromino.isEmpty())
    {
        debug("Empty Tetromino");
        // Alternative technical solution
        placeTetromino();
    }

    currentTetromino.print();

    debug("Placing tetromino at the center top of the screen...");
    currentTetromino.setX((graphics.getScreenWidth()/TILE_SIZE)/2 * TILE_SIZE);
    currentTetromino.setY(TILE_SIZE);
}

void TetrisGame::clearRows() {
    bool rowsCleared;
    std::vector<int> rowsToClear;
    do {
        rowsCleared = false;

        // Iterate through the game board from bottom to top, excluding the top border
        for (int row = boardHeight - 2; row >= 1; --row) {
            bool rowIsFull = true;

            // Check if the current row is full (no empty cells)
            for (int col = 1; col < boardWidth - 1; ++col) {
                if (gameBoard[row][col] == 0) {
                    rowIsFull = false;
                    break;
                }
            }

            // If the row is full, mark it for clearing
            if (rowIsFull) {
                rowsToClear.push_back(row);
                rowsCleared = true;
            }
        }

        // Clear marked rows and shift above rows down
        for (int rowToClear : rowsToClear) {
            for (int row = rowToClear; row >= 1; --row) {
                for (int col = 1; col < boardWidth - 1; ++col) {
                    gameBoard[row][col] = gameBoard[row - 1][col];
                }
            }
        }

        // Clear border tiles
        for (int row = 0; row < this->boardHeight; row++) {
            for (int col = 0; col < this->boardWidth; col++) {
                if (gameBoard[row][col] == 255) {
                    gameBoard[row][col] = 0;
                }
            }
        }

        rowsToClear.clear();
    } while (rowsCleared);
}

void TetrisGame::appendTetrominoToGameBoard() {
    std::vector<std::vector<int>> shape = currentTetromino.getShape();
    int x = currentTetromino.getX();
    int y = currentTetromino.getY();

    for (int i = 0; i < currentTetromino.getSize(); ++i) {
        for (int j = 0; j < currentTetromino.getSize(); ++j) {
            if (shape[i][j]) {
                // Calculate the position of the cell in grid coordinates
                int gridX = (x + j * TILE_SIZE) / TILE_SIZE;
                int gridY = (y + i * TILE_SIZE) / TILE_SIZE;

                // Set the corresponding cell in the gameBoard to 1
                gameBoard[gridY][gridX] = currentTetromino.getColorId();;
            }
        }
    }
}

void TetrisGame::displayGrid()
{
    debug("Displaying the game Grid...");
    for (int row = 0; row < boardHeight; row++)
    {
        for (int col = 0; col < boardWidth; col++)
        {
            if(gameBoard[row][col]==255)
            {
                #if LOG_LEVEL < INFO
                std::cout << "# ";
                #endif
            }
            else
            {
                #if LOG_LEVEL < INFO
                std::cout << gameBoard[row][col] << " ";
                #endif
            }
        }
        #if LOG_LEVEL < INFO
        std::cout << std::endl;
        #endif
    }
    debug("done!");
}

void TetrisGame::createBorders()
{
    // Set border values to 255
    for (int row = 0; row < boardHeight; row++) {
        gameBoard[row][0] = 255;
        gameBoard[row][boardWidth - 1] = 255;
    }

    for (int col = 0; col < boardWidth; col++) {
        gameBoard[0][col] = 255;
        gameBoard[boardHeight - 1][col] = 255;
    }
}
