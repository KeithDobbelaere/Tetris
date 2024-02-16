#pragma once

#include "grid.hpp"
#include "blocks.hpp"

#include <raylib.h>
#include <vector>

class Game 
{
public:
    Game();
    ~Game();
    void draw();
    void handleInput();
    void moveBlockDown();
    bool gameOver;
    int score;
    int lineCounter;
    double interval;
    int level;
    Music music;

private:
    void moveBlockLeft();
    void moveBlockRight();
    void rotateBlock();
    bool isBlockOutside();
    bool blockFits();
    void updateScore(int linesCleared);
    void reset();
    void lockBlock();
    Block getRandomBlock();
    Grid m_grid;
    std::vector<Block> m_blocks;
    Block m_currentBlock;
    Block m_nextBlock;
    Sound m_rotateSound;
    Sound m_clearSound;
    int m_levelUpCounter;
    bool m_softDropEnabled;
    bool m_hardDropTriggered;
};