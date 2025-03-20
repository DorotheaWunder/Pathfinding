#include <cmath>
#include <vector>
# include "enemy.h"
# include "tile.h"
# include "raylib.h"
# include "pathfinding.h"
# include <iostream>

Enemy::Enemy(Tile* startTile, Tile* goalTile, EnemySize size,
    MovementType movement, MovementDirection direction,
    bool isDijkstra)
    : currentTile(startTile), goalTile(goalTile), isActive(true),
    enemySize(size), movementType(movement), movementDirection(direction),
    usingDijkstra(isDijkstra), pathIndex(0)
{
    if (startTile)
    {
        row = startTile->position.row;
        col = startTile->position.col;
        x = startTile->position.x;
        y =  startTile->position.y;
    }
    enemySpeed = Enemy::calculateEnemySpeed(size);
}

float Enemy::calculateEnemySpeed(EnemySize size)
{
    switch (size)
    {
        case SMALL: return 1.0f; break;
        case MEDIUM: return 0.7f; break;
        case LARGE: return 0.3f; break;
        default: return 1.0f;
    }
}

Enemy* Enemy::GenerateEnemy(Tile* startTile, Tile* goalTile)
{
    int sizeIndex = rand() % 3;
    EnemySize size = static_cast<EnemySize>(sizeIndex);

    int moveIndex = rand() % 3;
    MovementType movementType = static_cast<MovementType>(moveIndex);

    Enemy* newEnemy = new Enemy(startTile, goalTile, size, movementType, CROSS, false);

    return newEnemy;
}


void Enemy::Draw()
{
    if (!isActive) return;

    Color enemyColor;
    switch (movementType)
    {
    case GROUND:
        enemyColor = RED;
        break;
    case AQUATIC:
        enemyColor = DARKBLUE;
        break;
    case FLYING:
        enemyColor = BLACK;
        break;
    }

    float sizeMultiplier;
    switch (enemySize)
    {
    case SMALL:
        sizeMultiplier = 0.5f;
        break;
    case MEDIUM:
        sizeMultiplier = 1.0f;
        break;
    case LARGE:
        sizeMultiplier = 2.0f;
        break;
    }
    float enemyRadius = 10 * sizeMultiplier;
    DrawCircle(x + Tile::SIZE / 2, y + Tile::SIZE / 2, enemyRadius, enemyColor);
    DrawCircleLines(x + Tile::SIZE / 2, y + Tile::SIZE / 2,enemyRadius, WHITE);
}

void Enemy::MoveBFS()
{
    if (!currentTile || !currentTile->vectorDirection) return;

    Tile* nextTile = currentTile->vectorDirection;
    float targetX = nextTile->position.x;
    float targetY = nextTile->position.y;

    float calculatedSpeed = enemySpeed * currentTile->speedModifier * GetFrameTime();

    x += (targetX - x) * calculatedSpeed;
    y += (targetY - y) * calculatedSpeed;

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
            MoveDijkstra();
            //MoveBFS();
        }
    }
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