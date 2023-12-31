#include <iostream>
#include <vector>
#include <time.h>

#include "seethe.h"
#include "tetromino.h"

// Constructor to create a Tetromino
Tetromino::Tetromino(shape_t shapeType) : tile(NULL){
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
    color = (color_t)(rand() % 8);
    for (uint32_t row = 0; row < size; ++row)
    {
        for (uint32_t col = 0; col < size; ++col)
        {
            if(shape[row][col])
            {
                shape[row][col] = (int)color;
            }
        }
    }

    // Todo: the tetromino should first appear at the top center of the screen
    this->x = 0;
    this->y = 0;

    this->shapeType = shapeType;

    this->setColorByShape(shapeType);
    lastTime = SDL_GetTicks();
}

void Tetromino::setColorByShape(shape_t shape)
{
    switch(shape)
    {
        case I_SHAPE:
            color = CIAN;
            break;
        case O_SHAPE:
            color = YELLOW;
            break;
        case T_SHAPE:
            color = VIOLET;
            break;
        case Z_SHAPE:
            color = RED;
            break;
        case S_SHAPE:
            color = GREEN;
            break;
        case J_SHAPE:
            color = BLUE;
            break;
        case L_SHAPE:
            color = ORANGE;
            break;
        default:
            color = BLACK;
            break;
    }
}
// Rotate the Tetromino clockwise
void Tetromino::rotateClockwise() {
    std::vector<std::vector<int>> rotated(size, std::vector<int>(size));
    for (uint32_t i = 0; i < size; ++i) {
        for (uint32_t j = 0; j < size; ++j) {
            rotated[i][j] = shape[size - 1 - j][i];
        }
    }
    shape = rotated;
    print();
}

// Rotate the Tetromino counterclockwise
void Tetromino::rotateCounterClockwise() {
    std::vector<std::vector<int>> rotated(size, std::vector<int>(size));
    for (uint32_t i = 0; i < size; ++i) {
        for (uint32_t j = 0; j < size; ++j) {
            rotated[i][j] = shape[j][size - 1 - i];
        }
    }
    shape = rotated;
    print();
}

// Get the current shape of the Tetromino
std::vector<std::vector<int>> Tetromino::getShape() const {
    return shape;
}

// Get the size of the Tetromino (e.g., 2 for O-shape, 4 for I-shape)
int Tetromino::getSize() const {
    return size;
}

void Tetromino::render()
{
    std::vector<std::vector<int>> shape = getShape();
    uint32_t size = getSize();
    for (uint32_t row = 0; row < size; ++row)
    {
        for (uint32_t col = 0; col < size; ++col)
        {
            if (shape[row][col])
            {
                getTile().drawCell(row, col, getX(), getY());
            }
        }
    }
}

void Tetromino::tick()
{

}

void Tetromino::setX(const int x)
{
    this->x = x;
}

void Tetromino::setY(const int y)
{
    this->y = y;
}

int Tetromino::getX()
{
    return x;
}

int Tetromino::getY()
{
    return y;
}

void Tetromino::setTile(const Tile tile)
{
    this->tile = tile;
}

Tile Tetromino::getTile()
{
    return tile;
}

void Tetromino::applyColors()
{
    this->tile.setColors(BASE_COLORS[this->color], LIGHT_COLORS[this->color], DARK_COLORS[this->color]);
}

void Tetromino::moveLeft()
{
    setX(this->getX()-TILE_SIZE);

}

void Tetromino::moveRight()
{
    setX(getX()+TILE_SIZE);
}

void Tetromino::moveDown()
{
    setY(getY()+TILE_SIZE);
}

void Tetromino::moveUp()
{
    setY(getY()-TILE_SIZE);
}

color_t Tetromino::getColorId()
{
    return color;
}

int Tetromino::getVerticalSize() const
{
    int verticalSize = 0;

    for (const auto& row : shape) {
        for (int cell : row) {
            if (cell != 0) {
                verticalSize++;
                break; // Only count each row once
            }
        }
    }

    return verticalSize;
}

int Tetromino::getHorizontalSize() const
{
    int horizontalSize = 0;

    for (size_t col = 0; col < shape[0].size(); ++col) {
        for (size_t row = 0; row < shape.size(); ++row) {
            if (shape[row][col] != 0) {
                horizontalSize++;
                break; // Only count each column once
            }
        }
    }

    return horizontalSize;
}

bool Tetromino::isEmpty() const
{
    for (const auto& row : getShape()) {
        for (int value : row) {
            if(value)
                return true;
        }
    }
    return false;
}

void Tetromino::print()
{
    #if LOG_LEVEL < INFO
    for (const auto& row : getShape()) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
    #endif
}

shape_t Tetromino::getShapeType() const
{
    return this->shapeType;
}
