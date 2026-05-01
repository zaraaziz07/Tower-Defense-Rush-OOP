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


struct WayPoint {
    float x;
    float y;
};

