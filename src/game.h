#ifndef _GAME_H_
#define _GAME_H_

#include "graphics.h"
#include "tetromino.h"
#include "score.h"
#include "level.h"
#include <vector>

#define FPS          60
#define FRAME_DELAY  1000/FPS

class TetrisGame {
public:
    TetrisGame();
    void run();

private:
    Graphics graphics;
    Tetromino currentTetromino;
    std::vector<std::vector<int>> gameBoard;
    int boardWidth;
    int boardHeight;
    Uint32 lastMoveTime;
    bool gameOver;
    bool quit = false;

    uint32_t frameStart = 0;
    int frameTime = 0;
    uint32_t lastTime;

    Score playerScore;
    Level playerLevel;
    int updateTetrominoTime;

    void initializeGame();
    void handleEvents();
    void update();
    void render();
    bool isCollision();
    void placeTetromino();
    void clearRows();
    bool checkBorderCollisions();
    void appendTetrominoToGameBoard();
    void createBorders();

    void displayGrid();

    void increaseScore(int points);
    void levelUp();
};

#endif
