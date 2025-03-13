# pragma once
# include "tile.h"
# include "gamegrid.h"
# include <queue>

bool IsWalkable(Tile* tile);
bool WasVisited(Tile* tile);
bool IsValid(Tile* tile);
void MarkVisited(Tile* tile);
void AddToFrontier(std::queue<Tile*>& frontier, Tile* tile);
void MeasureDistance(Tile* tile, Tile* parent);
void ReconstructPath(Tile* startTile, Tile* goalTile);
std::vector<Tile*> GetNeighbors(Tile* tile, Grid& grid);
std::vector<Tile*> BacktrackPath(Tile* startPos, Tile* goalPos);

void BFS(Grid& grid, Tile* startTile, Tile* goalTile);