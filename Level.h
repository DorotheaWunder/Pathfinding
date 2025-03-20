#pragma once
#include "tile.h"
#include "gamegrid.h"
#include <vector>

extern std::vector<std::pair<TerrainType, float>> terrainDistribution;

std::vector<Tile*> GetAllTiles(Grid& grid);
void ShuffleTiles(std::vector<Tile*>& tiles);
bool isValidDistance(const std::vector<Tile*>& anchors, Tile* candidate, int minDistance, int maxDistance);
std::vector<Tile*> SelectAnchorTiles(Grid& grid, int minDistance, int maxDistance);

TerrainType PickRandomTerrain(const std::vector<std::pair<TerrainType, float>>& percentage);
void AssignTerrain(std::vector<Tile*>& anchors, const std::vector<std::pair<TerrainType, float>>& percentage, Grid& grid);

void TerrainBFS(Grid* grid, Tile* startTile, TerrainType terrain, int spreadMinDistance, int spreadMaxDistance);