# include "GameGrid.h"
# include "tile.h"
# include "raylib.h"
#include <vector>

Grid::Grid(int width, int height)
    : width(width), height(height)
{
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


Tile* Grid::GetTilePos(int row, int col)
{
    if (row >= 0 && row < height && col >= 0 && col < width) {
        return &grid[row][col];
    }
    return nullptr;
}