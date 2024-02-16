#include "game.hpp"
#include <raylib.h>
#include <random>
#include <cmath>


Game::Game()
{
    srand(time(0));
    reset();
    InitAudioDevice();
    music = LoadMusicStream("./sounds/music.mp3");
    PlayMusicStream(music);
    m_rotateSound = LoadSound("./sounds/rotate.mp3");
    m_clearSound = LoadSound("./sounds/clear.mp3");
}

Game::~Game()
{
    UnloadSound(m_rotateSound);
    UnloadSound(m_clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

void Game::draw()
{
    m_grid.draw();
    m_currentBlock.draw(11, 11);
    switch(m_nextBlock.id)
    {
    case 1:
        m_nextBlock.draw(255, 475);
        break;
    case 4:
        m_nextBlock.draw(255, 455);
        break;
    default:
        m_nextBlock.draw(270, 455);
        break;
    }
}
namespace{
    static double lastTimePressed[18] = {0};
    static double delay = 0;
    int GetButtonPressed()
    {
        int buttonPressed = GAMEPAD_BUTTON_UNKNOWN;
        if (IsGamepadAvailable(0))
        {
            const double repeatDelay = 0.5;
            for (int button = 1; button < 19; button++)
            {
                if (IsGamepadButtonPressed(0, button))
                {
                    lastTimePressed[button] = GetTime();
                    delay = repeatDelay;
                    buttonPressed = button;
                }
            }
        }
        return buttonPressed;
    }

    bool IsButtonPressedRepeat(int button)
    {
        if (IsGamepadAvailable(0) && GetGamepadButtonPressed() == button)
        {
            const double repeatInterval = 0.033333333;
            auto time = GetTime();
            if(time - lastTimePressed[button] > delay)
            {
                lastTimePressed[button] = time;
                delay = repeatInterval;
                return true;
            }
        }
        return false;
    }
}

void Game::handleInput()
{
    int buttonPressed = GetButtonPressed();
    int keyPressed = GetKeyPressed();
    if(gameOver) {
        if(keyPressed || buttonPressed)
        {
            reset();
        }
        return;
    }
    if(m_hardDropTriggered)
    {
        moveBlockDown();
    }
    switch (buttonPressed)
    {
    case GAMEPAD_BUTTON_RIGHT_FACE_RIGHT:
    case GAMEPAD_BUTTON_LEFT_FACE_UP:
        rotateBlock();
        break;
    case GAMEPAD_BUTTON_LEFT_FACE_DOWN:
        m_softDropEnabled = true;
        moveBlockDown();
        break;
    case GAMEPAD_BUTTON_LEFT_FACE_LEFT:
        moveBlockLeft();
        break;
    case GAMEPAD_BUTTON_LEFT_FACE_RIGHT:
        moveBlockRight();
        break;
    case GAMEPAD_BUTTON_RIGHT_FACE_DOWN:
        m_hardDropTriggered = true;
        break;
    }
    if(IsButtonPressedRepeat(GAMEPAD_BUTTON_LEFT_FACE_DOWN))
    {
        if(m_softDropEnabled) moveBlockDown();
    }

    switch(keyPressed)
    {
    case KEY_LEFT:
        moveBlockLeft();
        break;
    case KEY_RIGHT:
        moveBlockRight();
        break;
    case KEY_SPACE:
    case KEY_UP:
        rotateBlock();
        break;
    case KEY_DOWN:
        moveBlockDown();
        m_softDropEnabled = true;
        break;
    case KEY_LEFT_CONTROL:
        m_hardDropTriggered = true;
        break;
    }
    if (IsKeyPressedRepeat(KEY_DOWN) || IsKeyPressedRepeat(KEY_SPACE))
    {
        if(m_softDropEnabled) moveBlockDown();
    }
}

void Game::moveBlockLeft()
{
    m_currentBlock.move(0, -1);
    if (isBlockOutside() || !blockFits())
    {
        m_currentBlock.move(0, 1);
    }
}

void Game::moveBlockRight()
{
    m_currentBlock.move(0, 1);
    if (isBlockOutside() || !blockFits())
    {
        m_currentBlock.move(0, -1);
    }
}

void Game::moveBlockDown()
{
    m_currentBlock.move(1, 0);
    if (isBlockOutside() || !blockFits())
    {
        m_currentBlock.move(-1, 0);
        lockBlock();
    }
}

void Game::rotateBlock()
{
    m_currentBlock.rotate();
    if (isBlockOutside() || !blockFits())
    {
        m_currentBlock.undoRotate();
    }
    else
    {
        PlaySound(m_rotateSound);
    }
}

bool Game::isBlockOutside()
{
    const auto& tiles = m_currentBlock.getCellPositions();
    for (auto& item : tiles)
    {
        if (m_grid.isCellOutside(item.row, item.col))
            return true;
    }
    return false;
}

bool Game::blockFits()
{
    const auto& tiles = m_currentBlock.getCellPositions();
    for (auto& item : tiles)
    {
        if (!m_grid.isCellEmpty(item.row, item.col))
            return false;
    }
    return true;
}

void Game::updateScore(int linesCleared)
{
    int baseIncrease = 0;
    switch(linesCleared)
    {
    case 1:
        baseIncrease = 40;
        break;
    case 2:
        baseIncrease = 100;
        break;
    case 3:
        baseIncrease = 300;
        break;
    case 4:
        baseIncrease = 1200;
        break;
    default:
        break;
    }

    score += baseIncrease * (level + 1);
}

void Game::reset()
{
    gameOver = false;
    m_grid.initialize();
    m_blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
    m_currentBlock = getRandomBlock();
    m_nextBlock = getRandomBlock();
    m_softDropEnabled = false;
    m_hardDropTriggered = false;
    score = 0;
    level = 0;
    lineCounter = 0;
    interval = 1;
}

void Game::lockBlock()
{
    m_softDropEnabled = false;
    m_hardDropTriggered = false;
    const auto& tiles = m_currentBlock.getCellPositions();
    for (auto& item : tiles)
    {
        m_grid.grid[item.row][item.col] = m_currentBlock.id;
    }
    m_currentBlock = m_nextBlock;
    if (!blockFits())
    {
        gameOver = true;
    }
    if (!gameOver)
    {
        m_nextBlock = getRandomBlock();
        int rowsCleared = m_grid.clearFullRows();
        if (rowsCleared)
        {
            PlaySound(m_clearSound);
            updateScore(rowsCleared);
            lineCounter += rowsCleared;
            m_levelUpCounter += rowsCleared;
            if (m_levelUpCounter >= 10)
            {
                m_levelUpCounter = m_levelUpCounter % 10;
                level++;
                interval = pow((0.8-((level)*0.007)), level);
            }
        }
    }
}

Block Game::getRandomBlock()
{
    if (m_blocks.empty())
        m_blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };

    int randomIndex = rand() % (int)m_blocks.size();
    Block block = m_blocks[randomIndex];
    m_blocks.erase(m_blocks.begin() + randomIndex);
    return block;
}
