#pragma once

#include <map>
#include <vector>

struct Position
{
    Position(int r, int c)
        : row(r), col(c)
    {}
    int row;
    int col;
};

class Block
{
public:
    Block();

    void draw(int offsetX, int offsetY);
    void move(int rows, int cols);
    void rotate();
    void undoRotate();
    std::vector<Position> getCellPositions();

    int id;
    std::map<int, std::vector<Position>> cells;

protected:
    enum Style {
        None,
        I,
        J,
        L,
        O,
        S,
        T,
        Z,
    };

private:
    int m_cellSize;
    int m_rotationState;
    int m_rowOffset;
    int m_colOffset;
};