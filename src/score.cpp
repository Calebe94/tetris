#include "score.h"

Score::Score() : score(0) {}

int Score::getScore() const {
    return score;
}

void Score::addPoints(int points) {
    score += points;
}

void Score::reset() {
    score = 0;
}

int Score::calculatePoints(int linesCleared) {
    switch (linesCleared) {
        case 1:
            return 100; // Single line clear
        case 2:
            return 300; // Double line clear
        case 3:
            return 500; // Triple line clear
        case 4:
            return 800; // Tetris line clear
        default:
            return 0;   // No points for other cases
    }
}
