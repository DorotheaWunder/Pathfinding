# include "spawning.h"
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "Pathfinding.h"

SpawnManager::SpawnManager(Grid& grid, int maxEnemies, float spawnInterval)
    : grid(grid), maxEnemies(maxEnemies), spawnInterval(spawnInterval), spawnCountdown(0.0f)
{
    std::srand(std::time(nullptr));
    FindSpawnTiles();
    FindGoalTiles();
}

void SpawnManager::SpawnEnemy()
{
    if (spawnTiles.empty())
    {
        FindSpawnTiles();
        if (spawnTiles.empty()) return;
    }

    Tile* spawnTile = GetRandomSpawn();
    if (!spawnTile) return;

    Tile* goalTile = GetClosestGoal(spawnTile);
    if (!goalTile) return;

    std::cout << "--> Enemy is spawning" << std::endl;
    Enemy* enemy = Enemy::GenerateEnemy(spawnTile, goalTile);
    activeEnemies.push_back(enemy);

    for (int row = 0; row < grid.height; row++)
    {
        for (int col = 0; col < grid.width; col++)
        {
            Tile* tile = grid.GetTilePos(row, col);
            if (tile)
            {
                tile->WalkableStatus(enemy);
            }
        }
    }

    grid.ResetTiles();

    if (enemy->usingDijkstra)
    {
        Dijkstra(grid, spawnTile, goalTile, enemy);
    }
    else
    {
        BFS(grid, spawnTile, goalTile, enemy);
    }

    std::vector<Tile*> path =BacktrackPath(spawnTile, goalTile);
    enemy->SetPath(path);
}

void SpawnManager::DespawnEnemy(Enemy* enemy)
{
    auto thisEnemy = std::find(activeEnemies.begin(), activeEnemies.end(), enemy);
    if (thisEnemy != activeEnemies.end())
    {
        std::cout << "--> Enemy disappears" << std::endl;
        delete *thisEnemy;
        activeEnemies.erase(thisEnemy);
    }
}

void SpawnManager::UpdateEnemy()
{
    spawnCountdown += GetFrameTime();

    if (spawnCountdown >= spawnInterval && activeEnemies.size() < maxEnemies)
    {
        SpawnEnemy();
        spawnCountdown = 0.0f;
    }

    for (auto thisEnemy = activeEnemies.begin(); thisEnemy != activeEnemies.end();)
    {
        if ((*thisEnemy)->HasReachedGoal())
        {
            DespawnEnemy(*thisEnemy);
        }
        else
        {
            (*thisEnemy)->MoveConstantly();
            ++thisEnemy;
;
        }
    }
}

void SpawnManager::FindSpawnTiles()
{
    spawnTiles.clear();

    for (int row = 0; row < grid.height; row++)
    {
        for (int col = 0; col < grid.width; col++)
        {
            Tile* tile = grid.GetTilePos(row, col);
            if (tile && tile->terrainType == SPAWN)
            {
                spawnTiles.push_back(tile);
            }
        }
    }
}

Tile* SpawnManager::GetRandomSpawn()
{
    if (spawnTiles.empty()) return nullptr;

    int index = std::rand() % spawnTiles.size();
    return spawnTiles[index];
}

void SpawnManager::FindGoalTiles()
{
    goalTiles.clear();

    for (int row = 0; row < grid.height; row++)
    {
        for (int col = 0; col < grid.width; col++)
        {
            Tile* tile = grid.GetTilePos(row, col);
            if (tile && tile->terrainType == GOAL)
            {
                goalTiles.push_back(tile);
            }
        }
    }
}

Tile* SpawnManager::GetClosestGoal(Tile* startTile)
{
    if (goalTiles.empty()) return nullptr;
    if (goalTiles.size() == 1) return goalTiles[0];

    Tile* closestGoal = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (Tile* goalTile : goalTiles)
    {
        float distance = std::abs(startTile->position.row - goalTile-> position.row) +
                         std::abs(startTile->position.col - goalTile->position.col);

        if (distance < minDistance)
        {
            minDistance = distance;
            closestGoal = goalTile;
        }
    }

    return closestGoal;
}
