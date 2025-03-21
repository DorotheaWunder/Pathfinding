#include <raylib.h>
# include <iostream>
#include "ui.h"
#include "level.h"
#include "gamegrid.h"
#include "enemy.h"
#include "controls.h"

Button generateTerrain = {{50, 10, 230, 40}, " Generate Terrain", DARKGRAY};
Button generateEnemy = {{450, 10, 230, 40}, "   Create Enemy", DARKGRAY};
Button startPath = {{850, 10, 230, 40}, " Start Pathfinding", DARKGRAY};
Button toggleDijkstra = {{1250, 10, 230, 40}, "   Switch Algorithm", DARKGRAY};

void HandleButtons(Grid& grid, Tile*& startTile, Tile*& goalTile, Enemy*& enemy)
{

    if (startPath.IsClicked())
    {
        grid.ResetTiles();
        startTile = enemy->GetCurrentTile();

        if (startTile && goalTile)
        {
            if (enemy->usingDijkstra)
            {
                Dijkstra(grid, startTile, goalTile, enemy);
            }
            else
            {
                BFS(grid, startTile, goalTile, enemy);
            }
            std::vector<Tile*> computedPath = BacktrackPath(startTile, goalTile);
            enemy->SetPath(computedPath);
        }
    }

    if (generateEnemy.IsClicked())
    {
        delete enemy;
        enemy = Enemy::GenerateEnemy(startTile, goalTile);
    }

    if (toggleDijkstra.IsClicked())
    {
        enemy->usingDijkstra = !enemy->usingDijkstra;

        if (enemy->usingDijkstra)
        {
            std::cout << "Algorithm is --> Dijkstra" << std::endl;
        }
        else
        {
            std::cout << "Algorithm is --> BFS" << std::endl;
        }
    }

    if (generateTerrain.IsClicked())
    {
        grid.InitializeGrid();
        GenerateTerrainAnchors(grid);
    }
}

void DrawUI()
{
    DrawRectangle(0,0, 1500,60, BLACK);
    generateTerrain.Draw();
    generateEnemy.Draw();
    startPath.Draw();
    toggleDijkstra.Draw();
}