# include "tile.h"
# include "raylib.h"
# include "enemy.h"



Tile::Tile(int row, int col, TerrainType terrain)
    : position(row, col), terrainType(terrain), wasVisited(false),
    vectorDirection(nullptr), distanceFromGoal(-1),
    tileColor(terrainColorVal[terrain]),
    speedModifier(terrainSpeedVal[terrain]),
    terrainCost(terrainCostVal[terrain])
{
    WalkableStatus();
}


Color terrainColorVal [] =
{
    BLACK,
    DARKGREEN,
    BLUE,
    LIME,
    BEIGE,
    DARKGRAY,
    SKYBLUE,
    RED
};

float terrainSpeedVal [] =
{
    0.0f,
    15.0f,
    15.0f,
    2.0f,
    5.0f,
    3.0f,
    25.0f,
    1.0f,
};

float terrainCostVal[] =
{
    999.0f,
    0.1f,
    1.0f,
    2.0f,
    1.0f,
    3.0f,
    2.0f,
    0.0f,
};

TileGridPosition::TileGridPosition(int row, int col)
    : row(row), col(col)
{
    x = col * Tile::SIZE;
    y = row * Tile::SIZE;
}

void Tile::WalkableStatus()
{
    isWalkable = (terrainType != WATER && terrainType != NONE);
}


void Tile::Draw()
{
    DrawRectangle(position.x, position.y, SIZE, SIZE, tileColor);
    DrawRectangleLines(position.x, position.y, SIZE, SIZE, BLACK);
}

