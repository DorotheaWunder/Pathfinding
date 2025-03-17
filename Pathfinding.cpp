# include "pathfinding.h"
# include "tile.h"
# include "gamegrid.h"
# include <queue>
# include <iostream>
# include <algorithm>
#include <limits>

bool IsWalkable(Tile* tile)
{
    return tile && tile->isWalkable;
}

bool WasVisited(Tile* tile)
{
    return tile && tile->wasVisited;
}

bool IsValid(Tile* tile)
{
    return tile && IsWalkable(tile) && !WasVisited(tile);
}

void MarkVisited(Tile* tile)
{
    if (tile)
    {
        tile->wasVisited = true;
        tile->tileColor = YELLOW;
    }
}

void AddToFrontier(std::queue<Tile*>& frontier, Tile* tile)
{
    if (IsValid(tile))
    {
        frontier.push(tile);
        MarkVisited(tile);
        tile->tileColor = ORANGE;
    }
}

struct CompareTileCost
{
    bool operator()(Tile* tileA, Tile* tileB)
    {
        return tileA->distanceFromGoal > tileB->distanceFromGoal;
    }
};

void InitPriorityQueue(std::priority_queue<Tile*, std::vector<Tile*>, CompareTileCost>& frontier, Tile* startTile)
{
    frontier.push(startTile);
    startTile->vectorDirection = nullptr;
    startTile->wasVisited = true;
}

void InitDijkstraTiles(Grid& grid, Tile* startTile)
{
    for (int row = 0; row < grid.height; row++)
    {
        for (int col = 0; col < grid.width; col++)
        {
            Tile* currentTile = grid.GetTilePos(row, col);
            currentTile->distanceFromGoal = std::numeric_limits<int>::max();
            currentTile->wasVisited = false;
            currentTile->vectorDirection = nullptr;
            currentTile->tileColor = ORANGE;
        }
    }
    startTile->distanceFromGoal = 0;
}

void MeasureDistance(Tile* tile, Tile* parent)
{
    if (tile && parent)
    {
        tile->distanceFromGoal = parent->distanceFromGoal + 1;
    }
}

void ReconstructPath(Tile* startTile, Tile* goalTile)
{
    Tile* current = startTile;
    while (current != nullptr && current != goalTile)
    {
        if (current)
        {
            current->tileColor = GREEN;
            current = current->vectorDirection;
        }
    }
}

float CalculateMovementCosts(Tile* currentTile, Tile* nextTile)
{
    return currentTile->terrainCost + + nextTile->terrainCost;;
}

std::vector<Tile*> GetNeighbors(Tile* tile, Grid& grid)
{
    std::vector<Tile*> neighbors;
    int row = tile->position.row;
    int col = tile->position.col;

    std::vector<std::pair<int, int>> directions =
        {
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1},
        };

    for (auto& direction : directions)
    {
        int newRow = row + direction.first;
        int newCol = col + direction.second;

        Tile* neighbor = grid.GetTilePos(newRow,newCol);
        if (IsValid(neighbor))
        {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

void CompareNeighborCost(Tile* current, Tile* neighbor, std::priority_queue<Tile*, std::vector<Tile*>, CompareTileCost>& frontier)
{
    float newCost = current->distanceFromGoal + CalculateMovementCosts(current, neighbor);

    if (newCost < neighbor->distanceFromGoal)
    {
        neighbor->distanceFromGoal =  newCost;
        neighbor->vectorDirection = current;
        MarkVisited(neighbor);
        frontier.push(neighbor);
    }
}

// std::vector<Tile*> BacktrackPath(Tile* startPos, Tile* goalPos)
// {
//     std::vector<Tile*> path;
//     Tile* current = goalPos;
//
//     while (current != startPos && current != nullptr)
//     {
//         path.push_back(current);
//         current = current->vectorDirection;
//     }
//
//     std::reverse(path.begin(), path.end());
//     return path;;
// }

void BFS(Grid& grid, Tile* startTile, Tile* goalTile)
{
    std::cout << "--> Algorithm Start " << std::endl;
    if (!startTile || !goalTile || !IsValid(goalTile))
        return;

    std::queue<Tile*> frontier;
    frontier.push(goalTile);
    MarkVisited(goalTile);
    goalTile->distanceFromGoal = 0;
    goalTile->tileColor = RED;  // Goal tile
    startTile->tileColor = GRAY; // Start tile

    while (!frontier.empty())
    {
        std::cout << "--> INSIDE while loop " << std::endl;
        Tile* current = frontier.front();
        frontier.pop();

        if (current == startTile)
        {
            std::cout << "--> Start tile reached, exiting BFS loop." << std::endl;
            break;
        }

        std::vector<Tile*> neighbors = GetNeighbors(current, grid);
        for (Tile* neighbor : neighbors)
        {
            std::cout << "--> Neighbor check" << std::endl;
            if (IsValid(neighbor))
            {
                std::cout << "--> Valid neighbor added to frontier" << std::endl;
                AddToFrontier(frontier, neighbor);
                neighbor->vectorDirection = current;
                neighbor->distanceFromGoal = current->distanceFromGoal + 1;
            }
        }
    }
    if (startTile->distanceFromGoal == -1)
    {
        std::cout << "--> No path found." << std::endl;
    }
    else
    {
        ReconstructPath(startTile, goalTile);
    }
}

void Dijkstra(Grid& grid, Tile* startTile, Tile* goalTile)
{
    std::cout << "--> Dijkstra Start " << std::endl;
    if (!startTile || !goalTile || !IsValid(goalTile))
        return;

    InitDijkstraTiles(grid, startTile);
    std::priority_queue<Tile*, std::vector<Tile*>, CompareTileCost> frontierDijkstra;
    InitPriorityQueue(frontierDijkstra, startTile);

    while (!frontierDijkstra.empty())
    {
        std::cout << "--> inside while loop." << std::endl;
        Tile* current = frontierDijkstra.top();
        frontierDijkstra.pop();

        if (current == goalTile)
        {
            std::cout << "--> goal tile reached, exiting Dijkstra loop." << std::endl;
            break;
        }

        std::vector<Tile*> neighbors = GetNeighbors(current, grid);
        for (Tile* neighbor : neighbors)
        {
            CompareNeighborCost(current, neighbor, frontierDijkstra);
        }
    }

    if (goalTile->distanceFromGoal == std::numeric_limits<int>::max())
    {
        std::cout << "--> No path found." << std::endl;
    }
    else
    {
        ReconstructPath(startTile, goalTile);
    }
}

//add movement diagonal

