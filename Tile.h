# pragma once
# include "raylib.h"

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
    GOAL
    //spawnpoint??
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
    static const int SIZE = 30;
    Color tileColor;
    float speedModifier;
    float terrainCost;

    Tile* vectorDirection;
    int distanceFromGoal;
    //--content game object?

    void Draw();

private:
    void WalkableStatus();
};

