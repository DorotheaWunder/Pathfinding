# include "pathfinding.h"
# include "tile.h"
# include "gamegrid.h"
# include <queue>
# include <iostream>
# include <algorithm>

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
    while (current != goalTile)
    {
        if (current)
        {
            current->tileColor = GREEN;
            current = current->vectorDirection;
        }
    }
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
            neighbor->tileColor = SKYBLUE;
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

std::vector<Tile*> BacktrackPath(Tile* startPos, Tile* goalPos)
{
    std::vector<Tile*> path;
    Tile* current = startPos;

    while (current != goalPos)
    {
        path.push_back(current);
        current = current->vectorDirection;
        if (!current) break;
    }

    path.push_back(goalPos);
    std::reverse(path.begin(), path.end());
    path;
}

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

