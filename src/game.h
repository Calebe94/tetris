#ifndef _GAME_H_
#define _GAME_H_

#include "graphics.h"
#include "tetromino.h"
#include "score.h"
#include "level.h"
#include "ui.h"

#include <SDL2/SDL_mixer.h>
#include <vector>

#define FPS          60
#define FRAME_DELAY  1000/FPS

class TetrisGame {
public:
    TetrisGame();
    void run();
    virtual ~TetrisGame();

private:
    Graphics graphics;
    Tetromino currentTetromino;
    Tetromino nextTetromino;
    TetrisUI tetrisUI;

    std::vector<std::vector<int>> gameBoard;
    int boardWidth;
    int totalBoardWidth;
    int boardHeight;
    Uint32 lastMoveTime;
    bool gameOver;
    bool quit = false;
    bool pause = false;

    uint32_t frameStart = 0;
    int frameTime = 0;
    uint32_t lastTime;

    Score playerScore;
    Level playerLevel;
    int updateTetrominoTime;
    Mix_Chunk *sound;
    Mix_Chunk *gameoverSound;

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

    void checkState();

    void tickGame();
    void renderGame();

    void displayGrid();
    void renderNextTetromino();

    void increaseScore(int points);
    void levelUp();
    bool checkGameOver();

    void restartGame();
};

#endif
