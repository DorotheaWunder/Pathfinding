#include "Controls.h"
#include "GameGrid.h"
#include "Enemy.h"
#include "Pathfinding.h"
#include "level.h"
#include "raylib.h"


void ChangeTile(Grid& grid, Tile*& goalTile)
{
    Vector2 mousePos = GetMousePosition();
    int row = mousePos.y / Tile::SIZE;
    int col = mousePos.x / Tile::SIZE;

    Tile* clickedTile = grid.GetTilePos(row, col);


    if (clickedTile)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (goalTile)
            {
                goalTile->terrainType = GRASS;
                goalTile->tileColor = terrainColorVal[GRASS];
            }

            clickedTile->terrainType = GOAL;
            clickedTile->tileColor = terrainColorVal[GOAL];
            goalTile = clickedTile;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            clickedTile->terrainType = WATER;
            clickedTile->tileColor = terrainColorVal[WATER];
            clickedTile->isWalkable = false;
        }
    }
}

void StartMovement(Grid& grid, Tile*& startTile, Tile*& goalTile, Enemy& enemy)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        grid.ResetTiles();
        startTile = enemy.GetCurrentTile();

        if (startTile && goalTile)
        {
            if (enemy.usingDijkstra)
            {
                Dijkstra(grid, startTile, goalTile, &enemy);
            }
            else
            {
                BFS(grid, startTile, goalTile, &enemy);
            }
            std::vector<Tile*> computedPath = BacktrackPath(startTile, goalTile);
            enemy.SetPath(computedPath);
        }
    }
}

void GenerateEnemy(Tile*& startTile, Tile*& goalTile, Enemy*& enemy)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        delete enemy;
        enemy = Enemy::GenerateEnemy(startTile, goalTile);
    }
}

void GenerateTerrainAnchors(Grid& grid)
{
    int anchorMinDist = 3;
    int anchorMaxDist = 10;

    std::vector<Tile*> anchors = SelectAnchorTiles(grid, anchorMinDist, anchorMaxDist);
    AssignTerrain(anchors, terrainDistribution, grid);
}

void GenerateMap(Grid& grid)
{
    if (IsKeyPressed(KEY_M))
    {
        grid.InitializeGrid();
        GenerateTerrainAnchors(grid);
    }
}
