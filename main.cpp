#include <iostream>
#include <raylib.h>
#include "Tile.h"
#include "GameGrid.h"
#include "Pathfinding.h"


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pathfinding Grid");
    SetTargetFPS(60);

    Grid grid(20,20);
    Tile* goalTile = nullptr;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 mousePos = GetMousePosition();
        int row = mousePos.y / Tile::SIZE;
        int col = mousePos.x / Tile::SIZE;

        Tile* clickedTile = grid.GetTilePos(row,col);


        if (clickedTile)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (goalTile)
                {
                    goalTile->terrainType = GRASS;
                    goalTile->tileColor = terrainColors[GRASS];
                }

                clickedTile->terrainType = GOAL;
                clickedTile->tileColor = terrainColors[GOAL];
                goalTile = clickedTile;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                clickedTile->terrainType = WATER;
                clickedTile->tileColor = terrainColors[WATER];
                clickedTile->isWalkable = false;
            }
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            Tile* startTile = grid.GetTilePos(0, 0);
            if (startTile && goalTile)
            {
                BFS(grid, startTile, goalTile);
            }
        }

        grid.DrawGrid();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
