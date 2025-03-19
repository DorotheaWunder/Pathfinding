#pragma once
# include "enemy.h"
# include "gamegrid.h"
# include <vector>
# include <queue>

class  SpawnManager
{
public:
    SpawnManager(Grid& grid, int maxEnemies = 10, float spawnInterval = 2.0f);

    std::vector<Enemy*>& GetEnemies() { return activeEnemies; }
    void SpawnEnemy();
    void DespawnEnemy(Enemy* enemy);
    void UpdateEnemy();
    void SetMaxEnemies(int count) {maxEnemies = count;}
    void SetSpawnInterval(float interval) {spawnInterval = interval;}

private:
    Grid& grid;
    std::vector<Tile*> spawnTiles;
    std::vector<Tile*> goalTiles;
    std::vector<Enemy*> activeEnemies;
    int maxEnemies;
    float spawnInterval;
    float spawnCountdown;

    void FindSpawnTiles();
    Tile* GetRandomSpawn();
    void FindGoalTiles();
    Tile* GetClosestGoal(Tile* startTile);
};