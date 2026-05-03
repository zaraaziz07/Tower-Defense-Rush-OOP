#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;

const int rows = 24;
const int cols = 43;
const int wayPointsCount = 8;
int grid[rows][cols] = { 0 };
const int TileSize = 32;
const int MaxEnemiesPerWave = 15;
const int totalWaves = 5;
class Enemy;

class WayPoint {
public:
    float x;
    float y;
};



class Wave {
public:
    Enemy* enemies[MaxEnemiesPerWave];
    int enemyCount;   //How many enemies will come in the current wave
    float spawnInterval;   //Seconds between each spawn
    int currentSpawn;      //Which enemy to spawn next
    float spawnTimer;      //Time since last spawn
    Wave() : enemyCount(0), spawnInterval(2.0f),
    currentSpawn(0), spawnTimer(0)
    {
        for (int i = 0; i < MaxEnemiesPerWave; i++)
            enemies[i] = nullptr;
    }
    ~Wave()
    {
        for (int i = 0; i < MaxEnemiesPerWave; i++)
        {
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }
};

extern Wave waves[totalWaves];


