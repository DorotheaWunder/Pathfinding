# Pathfinding Project

A pathfinding simulation that moves an enemy through a generated tilemap with different types of terrain. 
It uses either the *BFS algorithm* or *Dijkstra's algorithm* to move the enemy towards the player-determined goal.

## Enemies
Enemies are generated randomly and have both a different size (which affects their speed) and a different type (which affects their movement behavior).
The movement rules for the different enemy types are the following:
- **Ground enemy** (red) - can not move on water or mountains
- **Aquatic enemy** (blue) - can move on water but not on mountains
- **Flying enemy** (black) - can move on any terrain

## Map
The map has different types of terrain that not only affect the enemy’s movement behavior but also their movement speed. Swampy terrain will slow the enemy down, while walking on ice will speed up the enemy.
Additionally, the terrain has different assigned movement costs, which are factored in when *Dijkstra's algorithm* is used.
