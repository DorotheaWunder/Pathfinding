# pragma once
# include "tile.h"
# include "raylib.h"

class Enemy
{
public:
    Enemy(Tile* tile);

    void MoveStep();
    void MoveConstantly();
    void Draw();
    bool HasReachedGoal() const;
    Tile* GetCurrentTile() const { return currentTile; }
    void SetTile(Tile* newTile);

private:
    Tile* currentTile;
    int row, col;
    float x, y;
    float speed;
    bool isActive;
};