#pragma once
#include "GameGrid.h"
#include "Enemy.h"
#include "Pathfinding.h"
#include "raylib.h"

void MouseClick(Grid& grid, Tile*& goalTile);
void KeyPress(Grid& grid, Tile*& startTile, Tile*& goalTile, Enemy& enemy);