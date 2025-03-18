#include <cmath>
#include <vector>
# include "enemy.h"
# include "tile.h"
# include "raylib.h"
# include "pathfinding.h"
# include <iostream>

Enemy::Enemy(Tile* startTile, Tile* goalTile, bool isDijkstra)
    : currentTile(startTile), goalTile(goalTile), isActive(true),
    usingDijkstra(isDijkstra), pathIndex(0)
{
    if (startTile)
    {
        row = startTile->position.row;
        col = startTile->position.col;
        x = startTile->position.x;
        y =  startTile->position.y;
    }
}

void Enemy::MoveBFS()
{
    if (!currentTile || !currentTile->vectorDirection) return;

    Tile* nextTile = currentTile->vectorDirection;
    float targetX = nextTile->position.x;
    float targetY = nextTile->position.y;

    float speed = currentTile->speedModifier * GetFrameTime();

    x += (targetX - x) * speed;
    y += (targetY - y) * speed;

    if (fabs(x - targetX) < 1.0f && fabs(y - targetY) <1.0f)
    {
        currentTile =  nextTile;
        x = targetX;
        y = targetY;
    }
}

void Enemy::MoveDijkstra()
{
    if (path.empty() || pathIndex >= path.size()) return;

    Tile* nextTile = path[pathIndex];
    float targetX = nextTile->position.x;
    float targetY = nextTile->position.y;

    float speed = currentTile->speedModifier * GetFrameTime();

    x += (targetX - x) * speed;
    y += (targetY - y) * speed;

    if (fabs(x - targetX) < 1.0f && fabs(y - targetY) <1.0f)
    {
        currentTile =  nextTile;
        x = targetX;
        y = targetY;
        pathIndex++;
    }
}

// void Enemy::MoveDijkstra()
// {
//     std::cout << "--> the enemy is moving" << std::endl;
//     if (!currentTile || !goalTile) return;
//
//     std::vector<Tile*> path = BacktrackPath(currentTile, goalTile);
//     if (path.empty()) return;
//     Tile* nextTile = path[0];
//
//     float targetX = nextTile->position.x;
//     float targetY = nextTile->position.y;
//
//     float speed = currentTile->speedModifier * GetFrameTime();
//
//     x += (targetX - x) * speed;
//     y += (targetY - y) * speed;
//
//     if (fabs(x - targetX) < 1.0f && fabs(y - targetY) <1.0f)
//     {
//         currentTile =  nextTile;
//         x = targetX;
//         y = targetY;
//     }
// }

void Enemy::MoveConstantly()
{
    if (!HasReachedGoal())
    {
        if (usingDijkstra)
        {
            MoveDijkstra();
        }
        else
        {
            MoveBFS();
        }
    }
}

void Enemy::Draw()
{
    if (!isActive) return;

    DrawCircle(x + Tile::SIZE / 2, y + Tile::SIZE / 2,10, RED);
    DrawCircleLines(x + Tile::SIZE / 2, y + Tile::SIZE / 2,10, WHITE);
}

bool Enemy::HasReachedGoal() const
{
    return (currentTile && currentTile->distanceFromGoal == 0);
}

void Enemy::SetTile(Tile* newTile)
{
    currentTile = newTile;
}

void Enemy::SetPath(const std::vector<Tile*>& newPath)
{
    path = newPath;
    pathIndex = 0;
}