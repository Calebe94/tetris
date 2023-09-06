#ifndef _TETROMINO_H_
#define _TETROMINO_H_
#include <iostream>
#include <vector>
#include "colors.h"
#include "tile.h"

typedef enum shape_type {
    I_SHAPE = 0,
    O_SHAPE,
    T_SHAPE,
    Z_SHAPE,
    S_SHAPE,
    J_SHAPE,
    L_SHAPE,
} shape_t;

class Tetromino {
public:
    Tetromino(shape_type shapeType);

    void rotateClockwise();
    void rotateCounterClockwise();

    std::vector<std::vector<int>> getShape() const;
    int getSize() const;

    void setX(const int);
    void setY(const int);
    int getX();
    int getY();

    Tile getTile();
    void setTile(const Tile);

    void render();
    void tick();

    void applyColors();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();

private:
    void setColorByShape(shape_t shape);
    std::vector<std::vector<int>> shape;
    uint32_t size;
    color_t color;
    int x, y;
    Tile tile;
    uint32_t lastTime;
};
#endif
