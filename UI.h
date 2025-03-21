#pragma once
#include <raylib.h>
#include "level.h"
#include "gamegrid.h"
#include "enemy.h"
#include "controls.h"

struct Button
{
    Rectangle size;
    const char* text;
    Color buttonColor;

    bool IsClicked()
    {
        return (CheckCollisionPointRec(GetMousePosition(), size) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
    }

    void Draw()
    {
        DrawRectangleRec(size, buttonColor);
        DrawText(text, size.x + 10, size.y + 10, 20, WHITE);
    }
};

void HandleButtons(Grid& grid, Tile*& startTile, Tile*& goalTile, Enemy*& enemy);
void DrawUI();