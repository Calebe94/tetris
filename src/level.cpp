#include "level.h"

Level::Level() : level(1), linesCleared(0) {}

int Level::getCurrentLevel() const {
    return level;
}

void Level::levelUp()
{
    level++;
}

int Level::getLinesCleared() const {
    return linesCleared;
}

void Level::linesClearedEvent(int lines) {
    linesCleared += lines;

    // Adjust the level based on the number of lines cleared
    // You can define your own logic here for level progression
    // For example, you may increase the level every 10 lines.
    level = (linesCleared / 10) + 1;
}

void Level::reset() {
    level = 1;
    linesCleared = 0;
}
