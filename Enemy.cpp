# include "enemy.h"
# include "tile.h"
# include "raylib.h"
# include <iostream>

Enemy::Enemy(Tile* startTile)
    : currentTile(startTile), speed(2.0f), isActive(true)
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

    std::cout << "--> enemy is moving." << std::endl;
    currentTile = currentTile->vectorDirection;
    row = currentTile->position.row;
    col = currentTile->position.col;
    x = currentTile->position.x;
    y = currentTile->position.y;
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