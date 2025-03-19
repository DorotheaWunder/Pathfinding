#include <iostream>
#include <raylib.h>
#include "Tile.h"
#include "GameGrid.h"
#include "Controls.h"
#include "Enemy.h"
#include "spawning.h"


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int tileSize = 5;
    InitWindow(screenWidth, screenHeight, "Pathfinding Grid");
    SetTargetFPS(60);


    Grid grid(screenWidth,screenHeight, tileSize);
    SpawnManager spawner(grid, 5, 1.0f);//not working



    Tile* goalTile = nullptr;

    Tile* startTile = grid.GetTilePos(5, 5);
    Enemy* enemy = Enemy::GenerateEnemy(startTile, goalTile);

    for (int row = 0; row < grid.height; ++row) {
        for (int col = 0; col < grid.width; ++col) {
            Tile* tile = grid.GetTilePos(row, col);
            if (tile) {
                tile->WalkableStatus(enemy);
            }
        }
    }

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);


        ChangeTile(grid, goalTile);
        StartMovement(grid, startTile, goalTile, *enemy);
        GenerateEnemy(startTile, goalTile, enemy);

        enemy->MoveConstantly();

        spawner.UpdateEnemy();

        grid.DrawGrid();
        enemy->Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
