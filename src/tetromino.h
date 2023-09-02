#include <iostream>
#include <vector>

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

private:
    std::vector<std::vector<int>> shape;
    int size;
};
