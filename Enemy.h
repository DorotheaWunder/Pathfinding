# pragma once
# include "tile.h"
# include "raylib.h"
#include <vector>

class Enemy
{
public:
    Enemy(Tile* startTile, Tile* goalTile, bool isDijkstra = false);

    void MoveBFS();
    void MoveDijkstra();
    void MoveConstantly();
    void Draw();
    bool HasReachedGoal() const;
    bool usingDijkstra;
    Tile* GetCurrentTile() const { return currentTile; }
    void SetTile(Tile* newTile);
    void SetPath(const std::vector<Tile*>& newPath);


private:
    Tile* currentTile;
    Tile* goalTile;
    int row, col;
    float x, y;
    float speed;
    bool isActive;
    std::vector<Tile*> path;
    size_t pathIndex;
};