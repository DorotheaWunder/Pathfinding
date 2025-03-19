# pragma once
# include "tile.h"
# include "raylib.h"
#include <vector>

class Grid
{
public:
    Grid(int width, int height);
    Grid(int screenWidth, int screenHeight, int tileSize);
    int width, height;
    void InitializeGrid();
    void DrawGrid();
    void ResetTiles();
    void ResizeGrid(int screenWidth, int screenHeight);
    void SetTileSize(int size);

    Tile* GetTilePos(int row, int col);

private:
    std::vector<std::vector<Tile>> grid;
    int tileSize;
};