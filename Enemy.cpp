#include <cmath>

# include "enemy.h"
# include "tile.h"
# include "raylib.h"
# include <iostream>

Enemy::Enemy(Tile* startTile)
    : currentTile(startTile), isActive(true)
{
    if (startTile)
    {
        row = startTile->position.row;
        col = startTile->position.col;
        x = startTile->position.x;
        y =  startTile->position.y;
    }
}

void Enemy::MoveStep()
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

void Enemy::MoveConstantly()
{
    if (!HasReachedGoal())
    {
        MoveStep();
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