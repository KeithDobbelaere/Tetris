#include "grid.hpp"

#include "colors.hpp"

#include <iostream>

Grid::Grid() :
    m_numRows(20), m_numCols(10), m_cellSize(30)
{
    initialize();
}

void Grid::initialize()
{
    for(int row = 0; row < m_numRows; row++)
    {
        for (int col = 0; col < m_numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::print()
{
    for(int row = 0; row < m_numRows; row++)
    {
        for (int col = 0; col < m_numCols; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << '\n';
    }
}

void Grid::draw()
{
    for(int row = 0; row < m_numRows; row++)
    {
        for (int col = 0; col < m_numCols; col++)
        {
            auto& cellValue = grid[row][col];
            DrawRectangle(col * m_cellSize + 11, row * m_cellSize + 11, m_cellSize - 1, m_cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::isCellOutside(int row, int col)
{
    return (row < 0 || row >= m_numRows || col < 0 || col >= m_numCols);
}

bool Grid::isCellEmpty(int row, int col)
{
    return grid[row][col] == 0;
}

bool Grid::rowIsFilled(int row)
{
    for (int col = 0; col < m_numCols; col++)
    {
        if(grid[row][col] == 0)
            return false;
    }
    return true;
}

void Grid::moveRowDown(int row, int numRows)
{
    for (int col = 0; col < m_numCols; col++)
    {
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

void Grid::clearRow(int row)
{
    for (int col = 0; col < m_numCols; col++)
    {
        grid[row][col] = 0;
    }
}

int Grid::clearFullRows()
{
    int completed = 0;
    for (int row = m_numRows - 1; row >= 0; row--)
    {
        if(rowIsFilled(row))
        {
            clearRow(row);
            completed++;
        } else if (completed > 0)
        {
            moveRowDown(row, completed);
        }
    }
    return completed;
}
