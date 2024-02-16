#include <raylib.h>
#include <iostream>
#include "game.hpp"
#include "colors.hpp"

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime > interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

float getTextOffset(const Font& font, const char* text, int fontSize)
{
    auto textSize = MeasureTextEx(font, text, fontSize, 2);
    return 320.f + (170.f - textSize.x) / 2;
}

int main()
{
    //********************** INITIALIZE PLAYFIELD *****************
    const int WIDTH = 500;
    const int HEIGHT = 620;
    const int FONT_SIZE = 52;
    InitWindow(WIDTH, HEIGHT, "raylib Tetris");
    SetTargetFPS(60);
    Font font = LoadFontEx("./fonts/Arcade.ttf", FONT_SIZE, 0, 0);
    Game game;
    const float SCORE_POS_Y = 15.f;
    const float SCORE_POS_X = getTextOffset(font, "Score", FONT_SIZE);
    const float LEVEL_POS_Y = 125.f;
    const float LEVEL_POS_X = getTextOffset(font, "Level", FONT_SIZE);
    const float LINES_POS_Y = 235.f;
    const float LINES_POS_X = getTextOffset(font, "Lines", FONT_SIZE);
    auto textSize = MeasureTextEx(font, "GAME OVER", FONT_SIZE + 18, 2);
    const float GAME_OVER_POS_X = WIDTH / 2 - textSize.x / 2;
    int lastScore = -1;
    int lastLevel = -1;
    int lastLines = -1;
    char scoreText[10];
    char levelText[10];
    char linesText[10];
    float scoreValueOffset = 0;
    float levelValueOffset = 0;
    float linesValueOffset = 0;
    unsigned char alpha = 255;
    char fade = 3;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(game.music);
        game.handleInput();
        if (eventTriggered(game.interval))
        {
            game.moveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);

        //****************** DRAW SCORE **************************
        DrawTextEx(font, "Score", {SCORE_POS_X, SCORE_POS_Y}, FONT_SIZE, 2, RAYWHITE);
        DrawRectangleRounded({320, SCORE_POS_Y + 40, 170, 60}, 0.3, 6, lightBlue);
        if (lastScore != game.score)
        {
            sprintf(scoreText, "%d", game.score);
            scoreValueOffset = getTextOffset(font, scoreText, FONT_SIZE);
        }
        DrawTextEx(font, scoreText, {scoreValueOffset, SCORE_POS_Y + 50}, FONT_SIZE, 2, RAYWHITE);

        //****************** DRAW LEVEL **************************
        DrawTextEx(font, "Level", {LEVEL_POS_X, LEVEL_POS_Y}, FONT_SIZE, 2, RAYWHITE);
        DrawRectangleRounded({320, LEVEL_POS_Y + 40, 170, 60}, 0.3, 6, lightBlue);
        if (lastLevel != game.level)
        {
            sprintf(levelText, "%d", game.level);
            levelValueOffset = getTextOffset(font, levelText, FONT_SIZE);
        }
        DrawTextEx(font, levelText, {levelValueOffset, LEVEL_POS_Y + 50}, FONT_SIZE, 2, RAYWHITE);

        //****************** DRAW LINES **************************
        DrawTextEx(font, "Lines", {LINES_POS_X, LINES_POS_Y}, FONT_SIZE, 2, RAYWHITE);
        DrawRectangleRounded({320, LINES_POS_Y + 40, 170, 60}, 0.3, 6, lightBlue);
        if (lastLines != game.lineCounter)
        {
            sprintf(linesText, "%d", game.lineCounter);
            linesValueOffset = getTextOffset(font, linesText, FONT_SIZE);

        }
        DrawTextEx(font, linesText, {linesValueOffset, LINES_POS_Y + 50}, FONT_SIZE, 2, RAYWHITE);

        //****************** DRAW NEXT BOX ***********************
        const int NextPosY = 360;
        DrawTextEx(font, "Next", {350, NextPosY}, FONT_SIZE, 2, RAYWHITE);
        DrawRectangleRounded({320, NextPosY + 40, 170, 180}, 0.3, 6, lightBlue);
        game.draw();

        //**************** DRAW GAME OVER ************************
        if(game.gameOver) {
            Color color = RAYWHITE;
            if (alpha == 255 || alpha == 96) fade = -fade;
            alpha += fade;
            color.a = alpha;
            DrawTextEx(font, "GAME OVER", {GAME_OVER_POS_X, 320}, FONT_SIZE + 18, 2, color);
        }
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}