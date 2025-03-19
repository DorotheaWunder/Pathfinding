# pragma once
# include "raylib.h"
# include "enemy.h"

class Enemy;

extern Color terrainColorVal[];
extern float terrainSpeedVal[];
extern float terrainCostVal[];

enum TerrainType
{
    NONE,
    GRASS,
    WATER,
    SWAMP,
    DESERT,
    MOUNTAIN,
    ICE,
    GOAL,
    SPAWN
};

struct TileGridPosition
{
    int x, y;
    int col, row;

    TileGridPosition(int row = 0, int col = 0);
};


class Tile
{
public:
    Tile(int row = 0, int col = 0, TerrainType terrain = NONE);

    TileGridPosition position;
    bool isWalkable;
    bool wasVisited;
    TerrainType terrainType;
    static int SIZE;
    Color tileColor;
    float speedModifier;
    float terrainCost;

    Tile* vectorDirection;
    int distanceFromGoal;

    void Draw();
    void WalkableStatus(Enemy* enemy);
};

