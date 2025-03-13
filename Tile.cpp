# include "tile.h"
# include "raylib.h"



Tile::Tile(int row, int col, TerrainType terrain)
    : position(row, col), terrainType(terrain), wasVisited(false),
    vectorDirection(nullptr), distanceFromGoal(-1), tileColor(terrainColors[terrain])
{
    WalkableStatus();
}


Color terrainColors [] =
{
    BLACK,
    DARKGREEN,
    BLUE,
    RED
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
    //tileColor = terrainColors[terrainType]; //---might be deactivated for BFS
    DrawRectangle(position.x, position.y, SIZE, SIZE, tileColor);
    DrawRectangleLines(position.x, position.y, SIZE, SIZE, BLACK);
}


//tile change color