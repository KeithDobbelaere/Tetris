#pragma once

#include "block.hpp"

class LBlock : public Block
{
public:
    LBlock()
    {
        id = Block::Style::L;

        cells[0] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
        cells[1] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
        cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
        cells[3] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
        move(0, 3);
    }
};

class JBlock : public Block
{
public:
    JBlock()
    {
        id = Block::Style::J;

        cells[0] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
        cells[1] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
        cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
        cells[3] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
        move(0, 3);
    }
};

class IBlock : public Block
{
public:
    IBlock()
    {
        id = Block::Style::I;

        cells[0] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
        cells[1] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
        cells[2] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
        cells[3] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
        move(-1, 3);
    }
};

class OBlock : public Block
{
public:
    OBlock()
    {
        id = Block::Style::O;

        cells[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        move(0, 4);
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = Block::Style::S;

        cells[0] = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
        cells[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
        cells[2] = {{1, 1}, {1, 2}, {2, 0}, {2, 1}};
        cells[3] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        move(0, 3);
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = Block::Style::T;

        cells[0] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
        cells[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 1}};
        cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
        cells[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
        move(0, 3);
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = Block::Style::Z;

        cells[0] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
        cells[1] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
        cells[2] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
        cells[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 0}};
        move(0, 3);
    }
};