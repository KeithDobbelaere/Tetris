#include "block.hpp"
#include "colors.hpp"

Block::Block()
    : m_cellSize(30), m_rotationState(0),
    m_rowOffset(0), m_colOffset(0),
    id(Style::None)
{

}

void Block::draw(int offsetX, int offsetY)
{
    const auto& tiles = getCellPositions();
    for (auto& item : tiles)
    {
        DrawRectangle(item.col * m_cellSize + offsetX, item.row * m_cellSize + offsetY, m_cellSize - 1, m_cellSize - 1, colors[id]);
    }
}

void Block::move(int rows, int cols)
{
    m_rowOffset += rows;
    m_colOffset += cols;
}

void Block::rotate()
{
    if(++m_rotationState == (int)cells.size())
        m_rotationState = 0;
    
}

void Block::undoRotate()
{
    if(--m_rotationState == -1)
        m_rotationState = (int)cells.size() - 1;
}

std::vector<Position> Block::getCellPositions()
{
    auto& tiles = cells[m_rotationState];
    std::vector<Position> movedTiles;
    for (auto& item : tiles)
    {
        Position newPos = Position(item.row + m_rowOffset, item.col + m_colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}