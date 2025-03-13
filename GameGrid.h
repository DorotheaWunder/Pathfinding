# pragma once
# include "tile.h"
# include "raylib.h"
#include <vector>

class Grid
{
public:
    Grid(int width, int height);
    int width, height;
    void InitializeGrid();
    void DrawGrid();

    Tile* GetTilePos(int row, int col);

private:
    std::vector<std::vector<Tile>> grid;
};