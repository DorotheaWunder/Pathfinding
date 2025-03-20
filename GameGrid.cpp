# include "GameGrid.h"
# include "tile.h"
# include "raylib.h"
#include <vector>

Grid::Grid(int width, int height)
    : width(width), height(height), tileSize(Tile::SIZE)
{
    InitializeGrid();
}

Grid::Grid(int screenWidth, int screenHeight, int tileSize)
    : tileSize(tileSize)
{
    width = screenWidth / tileSize;
    height = screenHeight / tileSize;
    InitializeGrid();
}

void Grid::InitializeGrid()
{
    grid.resize(height);
    for (int row = 0; row < height; row++)
    {
        grid[row].resize(width);
        for (int col = 0; col < width; col++)
        {
            grid[row][col] = Tile(row, col, GRASS);
        }
    }
}

void Grid::ResizeGrid(int screenWidth, int screenHeight)
{
    width = screenWidth / tileSize;
    height = screenHeight/ tileSize;

    grid.resize(height);
    {
        for (int row = 0; row < height; row++)
        {
            grid.resize(width);
            for (int col = 0; col < width; col++)
            {
                if (row >= grid.size() || col >= grid[row].size())
                {
                    grid[row] [col] = Tile(row, col, GRASS);
                }
            }
        }
    }
}

void Grid::SetTileSize(int size)
{
    tileSize = size;
    Tile::SIZE = size;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            grid[row][col].position = TileGridPosition(row, col);
        }
    }
}

void Grid::DrawGrid()
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            grid[row][col].Draw();
        }
    }
}

void Grid::ResetTiles()
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            Tile& tile = grid[row][col];
            tile.wasVisited = false;
            tile.vectorDirection = nullptr;
            tile.distanceFromGoal = -1;
            tile.tileColor = terrainColorVal[tile.terrainType];
        }
    }
}



Tile* Grid::GetTilePos(int row, int col)
{
    if (row >= 0 && row < height && col >= 0 && col < width) {
        return &grid[row][col];
    }
    return nullptr;
}