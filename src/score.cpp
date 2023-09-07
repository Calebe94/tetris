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
