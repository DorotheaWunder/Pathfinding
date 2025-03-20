#include <algorithm>
#include <cmath>
#include <queue>
#include <random>
#include "level.h"

std::vector<std::pair<TerrainType, float>> terrainDistribution
{
    {GRASS, 25.0f},
    {WATER, 20.0f},
    {SWAMP, 13.0f},
    {DESERT, 12.0f},
    {MOUNTAIN, 15.0f},
    {ICE, 13.0f}
};

std::vector<Tile*> GetAllTiles(Grid& grid)
{
    std::vector<Tile*> allTiles;

    for (int row = 0; row < grid.height; row++)
    {
        for (int col = 0; col < grid.width; col++)
        {
            Tile* tile = grid.GetTilePos(row, col);

            if (tile)
            {
                allTiles.push_back(tile);
            }
        }
    }
    return allTiles;
}

void ShuffleTiles(std::vector<Tile*>& tiles)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tiles.begin(), tiles.end(), g);
}

bool isValidDistance(const std::vector<Tile*>& anchors, Tile* candidate, int minDistance, int maxDistance)
{
    if (anchors.empty()) return true;

    bool withinMax = false;
    for (Tile* anchor : anchors)
    {
        int distX = candidate->position.col - anchor->position.col;
        int distY = candidate->position.row - anchor->position.row;
        float distance = std::sqrt(distX * distX + distY * distY);

        if (distance < minDistance) return false;
        if (distance <= maxDistance) withinMax = true;
    }

    return !withinMax;
}

std::vector<Tile*> SelectAnchorTiles(Grid& grid, int minDistance, int maxDistance)
{
    std::vector<Tile*> anchors;
    std::vector<Tile*> allTiles = GetAllTiles(grid);
    ShuffleTiles(allTiles);

    for (Tile* candidate : allTiles)
    {
        if (isValidDistance(anchors, candidate, minDistance, maxDistance))
        {
            anchors.push_back(candidate);
        }
    }
    return anchors;
}

TerrainType PickRandomTerrain(const std::vector<std::pair<TerrainType, float>>& spawnPercentage)
{
    float percentage = 0.0f;
    for (const auto& terrainDistribution : spawnPercentage)
    {
        percentage += terrainDistribution.second;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, percentage);
    float randomWeight = dist(gen);

    for (const auto& pair : spawnPercentage)
    {
        if (randomWeight < pair.second)
        {
            return pair.first;
        }
        randomWeight -= pair.second;
    }
    return terrainDistribution.back().first;
}

void AssignTerrain(std::vector<Tile*>& anchors, const std::vector<std::pair<TerrainType, float>>& percentage, Grid& grid)
{
    if (anchors.empty()) return;

    anchors[0]->terrainType = GOAL;
    anchors[0]->tileColor = terrainColorVal[GOAL];

    if (anchors.size() > 1)
    {
        anchors[1]->terrainType = SPAWN;
        anchors[1]->tileColor = terrainColorVal[SPAWN];
    }

    const int minAnchorDistance = 2;
    const int maxAnchorDistance = 8;

    const int spreadMinDistance = 2;
    const int spreadMaxDistance = 6;

    for (size_t i = 2; i < anchors.size(); i++)
    {
        TerrainType terrain = PickRandomTerrain(percentage);
        anchors[i]->terrainType = terrain;
        anchors[i]->tileColor = terrainColorVal[terrain];

        TerrainBFS(&grid, anchors[i], terrain, spreadMinDistance, spreadMaxDistance);
    }
}

void TerrainBFS(Grid* grid, Tile* startTile, TerrainType terrain, int spreadMinDistance, int spreadMaxDistance)
{
    if (!startTile || !grid) return;

    std::queue<std::pair<Tile*, int>> tileQueue;
    tileQueue.push({startTile, 0});
    startTile->terrainType = terrain;
    startTile->tileColor = terrainColorVal[terrain];

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distX(spreadMinDistance, spreadMaxDistance);
    std::uniform_int_distribution<int> distY(spreadMinDistance, spreadMaxDistance);

    while (!tileQueue.empty())
    {
        Tile* current = tileQueue.front().first;
        int currentDistance = tileQueue.front().second;
        tileQueue.pop();

        if (currentDistance >= spreadMaxDistance) continue;

        int maxDistX = distX(gen);
        int maxDistY = distY(gen);

        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            int newRow = current->position.row + (dRow[i] * maxDistY);
            int newCol = current->position.col + (dCol[i] * maxDistX);

            if (newRow >= 0 && newRow < grid->height && newCol >= 0 && newCol < grid->width)
            {
                Tile* neighbor = grid->GetTilePos(newRow, newCol);

                if (neighbor && neighbor->terrainType != terrain && neighbor->terrainType != GOAL)
                {
                    neighbor->terrainType = terrain;
                    neighbor->tileColor = terrainColorVal[terrain];
                    neighbor->speedModifier = terrainSpeedVal[terrain];

                    tileQueue.push({neighbor, currentDistance + 1});
                }
            }
        }
    }
}