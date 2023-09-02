#include <iostream>
#include <vector>

#include "tetromino.h"

// Constructor to create a Tetromino
Tetromino::Tetromino(shape_t shapeType) {
    // Define Tetromino shapes (example shapes)
    // 1 represents the block, 0 represents empty space
    std::vector<std::vector<int>> shapes[7] = {
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}, // I-shape

        {{1, 1},
         {1, 1}}, // O-shape

        {{0, 1, 0},
         {1, 1, 1},
         {0, 0, 0}}, // T-shape

        {{0, 1, 1},
         {1, 1, 0},
         {0, 0, 0}}, // Z-shape

        {{1, 1, 0},
         {0, 1, 1},
         {0, 0, 0}}, // S-shape

        {{1, 1, 1},
         {0, 0, 1},
         {0, 0, 0}}, // J-shape

        {{1, 1, 1},
         {1, 0, 0},
         {0, 0, 0}} // L-shape
    };

    if (shapeType >= 0 && shapeType < 7) {
        shape = shapes[shapeType];
        size = shape.size();
    } else {
        // Invalid shapeType, set to default O-shape
        shape = shapes[1];
        size = shape.size();
    }
}

// Rotate the Tetromino clockwise
void Tetromino::rotateClockwise() {
    std::vector<std::vector<int>> rotated(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            rotated[i][j] = shape[size - 1 - j][i];
        }
    }
    shape = rotated;
}

// Rotate the Tetromino counterclockwise
void Tetromino::rotateCounterClockwise() {
    std::vector<std::vector<int>> rotated(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            rotated[i][j] = shape[j][size - 1 - i];
        }
    }
    shape = rotated;
}

// Get the current shape of the Tetromino
std::vector<std::vector<int>> Tetromino::getShape() const {
    return shape;
}

// Get the size of the Tetromino (e.g., 2 for O-shape, 4 for I-shape)
int Tetromino::getSize() const {
    return size;
}
