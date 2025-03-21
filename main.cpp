#include <iostream>
#include <raylib.h>
#include "Tile.h"
#include "GameGrid.h"
#include "Controls.h"
#include "Enemy.h"
#include "spawning.h"
#include "ui.h"


int main()
{
    const int screenWidth = 1500;
    const int screenHeight = 800;
    const int tileSize = 5;
    InitWindow(screenWidth, screenHeight, "Pathfinding Grid");
    SetTargetFPS(60);


    Grid grid(screenWidth,screenHeight, tileSize);
    Tile* goalTile = nullptr;
    Tile* startTile = grid.GetTilePos(15, 15);
    Enemy* enemy = Enemy::GenerateEnemy(startTile, goalTile);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        grid.DrawGrid();

        HandleButtons(grid, startTile, goalTile, enemy);
        DrawUI();

        ChangeTile(grid, goalTile);
        StartMovement(grid, startTile, goalTile, *enemy);//press SPACE

        enemy->MoveConstantly();
        enemy->Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
