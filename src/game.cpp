#include "seethe.h"
#include "graphics.h"
#include "tetromino.h"
#include <vector>
#include "ui.h"
#include "game.h"
#include "gamestate.h"
#include "imgui_impl_sdl2.h"

TetrisGame::TetrisGame() :
    currentTetromino((shape_t)(rand() % 7)),
    nextTetromino((shape_t)(rand() % 7)),
    tetrisUI(nullptr, nullptr)
{
    lastTime = SDL_GetTicks();
    updateTetrominoTime = 300;
}

void TetrisGame::run()
{
    initializeGame();

    tetrisUI = TetrisUI(graphics.getWindow(), graphics.getRenderer());
    tetrisUI.init();
    // TODO: I should find a way to round up numbers, because at this point the height(672) and width(476) is hard coded and 476/32 is 14.93,
    // I need it to be at least 15
    this->totalBoardWidth = (this->graphics.getScreenWidth() / 32);
    this->boardWidth = (this->totalBoardWidth)*0.75;
    this->boardHeight = this->graphics.getScreenHeight() / 32;
    info("The board width is 80%% of the total width, which is: %d", this->boardWidth);

    debug("Board width: %d", boardWidth);
    debug("Board height: %d", boardHeight);

    gameBoard.resize(boardHeight, std::vector<int>(totalBoardWidth, 0));
    debug("Board dimensions: %ld %ld", gameBoard.size(), gameBoard[0].size());

    createBorders();
    GameStateManager::getInstance().transitionTo(GameState::MENU);

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
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            tetrisUI.setQuit(true);
            this->quit = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    debug("Left key!");
                    if(GameStateManager::getInstance().getCurrentState() == GameState::GAME)
                        this->currentTetromino.moveLeft();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveRight();
                    }
                    break;
                case SDLK_RIGHT:
                    debug("Right key!");
                    if(GameStateManager::getInstance().getCurrentState() == GameState::GAME)
                        this->currentTetromino.moveRight();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveLeft();
                    }
                    break;
                case SDLK_DOWN:
                    debug("Down key!");
                    if(GameStateManager::getInstance().getCurrentState() == GameState::GAME)
                        this->currentTetromino.moveDown();
                    if(checkBorderCollisions())
                    {
                        this->currentTetromino.moveUp();
                    }
                    break;
                case SDLK_UP:
                    debug("UP key!");
                    if(GameStateManager::getInstance().getCurrentState() == GameState::GAME)
                        this->currentTetromino.rotateClockwise();
                    debug("Tetromino vertical size: %d", this->currentTetromino.getVerticalSize());
                    debug("Tetromino horizontal size: %d", this->currentTetromino.getHorizontalSize());
                    break;

                case SDLK_ESCAPE:
                    pause = !pause;
                    if(GameStateManager::getInstance().getCurrentState() == GameState::GAME)
                        GameStateManager::getInstance().transitionTo(GameState::PAUSED);
                    else if(GameStateManager::getInstance().getCurrentState() == GameState::PAUSED)
                        GameStateManager::getInstance().transitionTo(GameState::GAME);
                    info("Game status: %s", pause?"Paused":"Resumed");
                    tetrisUI.ToggleMenu();
                    break;

                case SDLK_SPACE:
                    break;
            }
        }
    }
}

void TetrisGame::update()
{
    if (GameStateManager::getInstance().getCurrentState() == GameState::GAME)
    {
        tickGame();
    }
    if(GameStateManager::getInstance().getCurrentState() == GameState::EXIT)
    {
        this->quit = true;
    }
}

void TetrisGame::render()
{
    this->graphics.clear();

    if (GameStateManager::getInstance().getCurrentState() == GameState::MENU || GameStateManager::getInstance().getCurrentState() == GameState::PAUSED)
    {
        tetrisUI.Render();
    }

    if (GameStateManager::getInstance().getCurrentState() == GameState::GAME)
    {
        tetrisUI.renderPlayerScore();
        renderGame();
    }
    if (GameStateManager::getInstance().getCurrentState() == GameState::GAME_OVER) {
        // Render game over message or take other actions
        tetrisUI.showGameOver();
    }
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

    currentTetromino = nextTetromino;
    nextTetromino = Tetromino((shape_t)(rand() % 7));
    if(!nextTetromino.isEmpty() || !currentTetromino.isEmpty())
    {
        debug("Empty Tetromino");
        // Alternative technical solution
        placeTetromino();
    }

    if (nextTetromino.getShapeType() == I_SHAPE)
    {
        nextTetromino.rotateClockwise();
    }
    currentTetromino.print();

    debug("Placing tetromino at the center top of the screen...");
    currentTetromino.setX((this->boardWidth/2) * TILE_SIZE);
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

        // Calculate the points based on the number of rows cleared
        int linesCleared = rowsToClear.size();
        if(linesCleared > 0)
        {
            int pointsToAdd = playerScore.calculatePoints(linesCleared);
            increaseScore(pointsToAdd);
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
        gameBoard[row][totalBoardWidth - 1] = 255;
    }

    for (int col = 0; col < totalBoardWidth; col++) {
        gameBoard[0][col] = 255;
        gameBoard[boardHeight - 1][col] = 255;
    }

    // Creating borders for the score UI
    for (int row = boardWidth; row < totalBoardWidth; row++)
    {
        gameBoard[5][row] = 255;
    }

    // Creating borders for the player level UI
    for (int row = boardWidth; row < totalBoardWidth; row++)
    {
        gameBoard[10][row] = 255;
    }

    // for (int col = 0; col < this->totalBoardWidth; col++) {
    //     gameBoard[0][col] = 255;
    //     gameBoard[totalBoardWidth-1][col] = 255;
    // }
}

void TetrisGame::increaseScore(int points) {
    playerScore.addPoints(points);

    info("Score: %d", playerScore.getScore());
    tetrisUI.setPlayerScore(playerScore.getScore());
    // Check if the player should level up based on your criteria
    if (playerScore.getScore() >= (playerLevel.getCurrentLevel()*1000))
    {
        levelUp();
        tetrisUI.setPlayerLevel(playerLevel.getCurrentLevel());
    }
}

void TetrisGame::levelUp() {
    // Increase the player's level
    playerLevel.levelUp();

    // TODO: Add logic to make the game more challenging at higher levels
    // For example, increase the game speed or introduce new Tetrominoes

    // You can print a message or perform any actions specific to leveling up here
    info("Level Up! You are now at Level %d", playerLevel.getCurrentLevel());
}

void TetrisGame::checkState()
{
    switch (GameStateManager::getInstance().getCurrentState()) {
        case GameState::MENU:
            // Handle MENU state logic
            std::cout << "In MENU state" << std::endl;
            // Check for transitions to other states (e.g., NEW_GAME)
            tetrisUI.Render();
            break;

        case GameState::GAME:
            // Handle GAME state logic
            std::cout << "In GAME state" << std::endl;
            // Check for transitions to other states (e.g., PAUSED)
            // tickGame();
            // renderGame();
            break;

        case GameState::PAUSED:
            // Handle PAUSED state logic
            std::cout << "In PAUSED state" << std::endl;
            // Check for transitions to other states (e.g., MENU or GAME)
            tetrisUI.Render();
            break;

        case GameState::SETTINGS:
            // Handle SETTINGS state logic
            std::cout << "In SETTINGS state" << std::endl;
            // Check for transitions to other states (e.g., MENU)
            break;

        // Add more cases for other states as needed

        default:
            break;
    }
}

void TetrisGame::renderGame()
{
    Tile tile = Tile(this->graphics.getRenderer());

    for (int row = 0; row < this->boardHeight; row++)
    {
        for (int col = 0; col < this->totalBoardWidth; col++)
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

    renderNextTetromino();
}

void TetrisGame::tickGame()
{
    if (SDL_GetTicks() - lastTime >= (uint32_t)(updateTetrominoTime - playerLevel.getCurrentLevel()*15)) {
        currentTetromino.tick();
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

    tetrisUI.setPlayerScore(playerScore.getScore());
    tetrisUI.setPlayerLevel(playerLevel.getCurrentLevel());
    if (checkGameOver()) {
        // Game over logic
        // For example, transition to the game over state or display a game over message
        GameStateManager::getInstance().transitionTo(GameState::GAME_OVER);
        info("Game over");
        restartGame();
        // return;
    }
}

void TetrisGame::renderNextTetromino()
{
    Tile tile = Tile(this->graphics.getRenderer());
    nextTetromino.setX(this->boardWidth*32 + 32);
    nextTetromino.setY(32 * 15);
    nextTetromino.setTile(tile);
    nextTetromino.applyColors();
    nextTetromino.render();
}

bool TetrisGame::checkGameOver()
{
    std::vector<std::vector<int>> tetrominoShape = currentTetromino.getShape();
    int tetrominoX = currentTetromino.getX();
    int tetrominoY = currentTetromino.getY();

    for (int i = 0; i < currentTetromino.getSize(); i++) {
        for (int j = 0; j < currentTetromino.getSize(); ++j) {
            if (tetrominoShape[i][j]) {
                int gridX = (tetrominoX + j * TILE_SIZE) / TILE_SIZE;
                int gridY = (tetrominoY + i * TILE_SIZE) / TILE_SIZE;

                if (gridY >= boardHeight || gameBoard[gridY][gridX]) {
                    return true; // Game over if the Tetromino can't be placed
                }
            }
        }
    }

    return false; // Not game over
}

void TetrisGame::restartGame()
{
    for (int row = 0; row < this->boardHeight; row++)
    {
        for (int col = 0; col < this->boardWidth; col++)
        {
            gameBoard[row][col] = 0;
        }
    }
    createBorders();
    displayGrid();
    playerLevel.reset();
    playerScore.reset();
    placeTetromino();
}
