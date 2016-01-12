#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Tile.h"

using namespace std;

class Map
{
public:
    Map();
    ~Map();

    void GenerateMap(string name);

    vector<Tile*> getTiles();

    bool IsTileValid(int x, int y);
    bool IsTileMart(int x, int y);
    bool IsTileCenter(int x, int y);
    bool IsTileBush(int x, int y);

private:
    vector<Tile*> tiles;
    string name;

    int x;
    bool buildingPositionsfilled;
    bool buildingDrawed;

    vector<int> positionsXDoorCenter;
    vector<int> positionsYDoorCenter;

    vector<int> positionsXDoorMart;
    vector<int> positionsYDoorMart;

    bool CheckBuildings(string letter, int value, vector<int> positions, int i, int j);
    vector<int> fillBuildingPositionsTaken(int i, string letter);
	int iterBuildingTiles;
};