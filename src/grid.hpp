#pragma once

class Grid {
public:
    Grid();
    void initialize();
    void print();
    void draw();
    bool isCellOutside(int row, int col);
    bool isCellEmpty(int row, int col);
    bool rowIsFilled(int row);
    void moveRowDown(int row, int numRows);
    void clearRow(int row);
    int clearFullRows();
    
    int grid[20][10];

private:
    int m_numRows;
    int m_numCols;
    int m_cellSize;
};