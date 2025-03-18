# pragma once
# include "tile.h"
# include "raylib.h"
#include <vector>

enum MovementType
{
    GROUND,
    AQUATIC,
    FLYING
};

enum EnemySize
{
    SMALL,
    MEDIUM,
    LARGE
};

enum MovementDirection
{
    CROSS,
    DIAGONAL
};

class Enemy
{
public:
    Enemy(Tile* startTile, Tile* goalTile, EnemySize size,
    MovementType movement = GROUND, MovementDirection direction = CROSS,
    bool isDijkstra = false);

    static Enemy* GenerateEnemy(Tile* startTile, Tile* goalTile);

    void MoveBFS();
    void MoveDijkstra();
    bool usingDijkstra;

    void MoveConstantly();
    bool HasReachedGoal() const;
    void SetTile(Tile* newTile);
    void SetPath(const std::vector<Tile*>& newPath);
    Tile* GetCurrentTile() const { return currentTile; }

    float calculateEnemySpeed(MovementType movement, EnemySize size);
    MovementType GetMovementType() const {return movementType;}
    void Draw();

private:
    bool isActive;

    Tile* currentTile;
    Tile* goalTile;
    int row, col;
    float x, y;

    std::vector<Tile*> path;
    size_t pathIndex;

    float enemySpeed;
    EnemySize enemySize;
    MovementType movementType;
    MovementDirection movementDirection;
};