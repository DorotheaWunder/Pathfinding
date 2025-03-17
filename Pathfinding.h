# pragma once
# include "tile.h"
# include "gamegrid.h"
# include <queue>

struct CompareTileCost;
bool IsWalkable(Tile* tile);
bool WasVisited(Tile* tile);
bool IsValid(Tile* tile);
void MarkVisited(Tile* tile);
void AddToFrontier(std::queue<Tile*>& frontier, Tile* tile);
void InitPriorityQueue(std::priority_queue<Tile*, std::vector<Tile*>, CompareTileCost>& frontier, Tile* startTile);
void InitDijkstraTiles(Grid& grid, Tile* startTile);
void MeasureDistance(Tile* tile, Tile* parent);
void ReconstructPath(Tile* startTile, Tile* goalTile);
float CalculateMovementCosts(Tile* currentTile, Tile* nextTile);
struct CompareTileCost;
std::vector<Tile*> GetNeighbors(Tile* tile, Grid& grid);
void CompareNeighborCost(Tile* current, Tile* neighbor, std::priority_queue<Tile*, std::vector<Tile*>, CompareTileCost>& frontier);
std::vector<Tile*> BacktrackPath(Tile* startPos, Tile* goalPos);


void BFS(Grid& grid, Tile* startTile, Tile* goalTile);
void Dijkstra(Grid& grid, Tile* startTile, Tile* goalTile);