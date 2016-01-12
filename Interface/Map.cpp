#include "Map.h"

Map::Map()
{
    name = "";
    buildingPositionsfilled = false;
    buildingDrawed = false;
    iterBuildingTiles = 0;
}

Map::~Map()
{
    tiles.clear();
}

void Map::GenerateMap(string theName)
{
    int iterY = 0;

    vector<int> positionYTaken;

    string line;
    string letter;

    ifstream file;
    file.open("Pallet_Town.txt");
    while(getline(file,line))
    {
        for(int i = 0; i < line.size(); i++)
        {
            x = i;
            letter = line.substr(i,1);
            if(!buildingPositionsfilled)
            {
                positionYTaken = fillBuildingPositionsTaken(iterY,letter);
            }      

            

            if(!(CheckBuildings(letter, iterY, positionYTaken, i, iterY)))
            {
                Tile* tile = new Tile(letter,20*i,iterY*18);
                if(letter == "h" || letter == "c" || letter == "m" ) // first tile of a building
                {
                    tile->setInvalid();
                    buildingDrawed = true;
                }
                tiles.push_back(tile);

                for(int j = 0; j < positionsXDoorCenter.size(); j++)
                {
                    if(i == positionsXDoorCenter[j] && iterY == positionsYDoorCenter[j])
                    {
                        tile->setPokeCenterDoor();
                    }
                }

                for(int j = 0; j < positionsXDoorMart.size(); j++)
                {
                    if(i == positionsXDoorMart[j] && iterY == positionsYDoorMart[j])
                    {
                        tile->setPokeMartDoor();
                    }
                }
            }
        }
        iterY++;
    }
}

bool Map::CheckBuildings(string letter, int value, vector<int> positions, int i, int j)
{
    int iter = 0;
    vector<int>::iterator it;
    it = find(positions.begin(), positions.end(), value);

    if(it != positions.end() && (letter == "h" || letter == "c" || letter == "m" ))
    {
        if(buildingDrawed)
        {
            Tile* tile = new Tile("t",20*i,j*18);
            tile->setColor(Color::Transparent);
            tile->setInvalid();
            tiles.push_back(tile);
            iterBuildingTiles++;
            if(iterBuildingTiles == 15)
            {
                buildingDrawed = false;
                buildingPositionsfilled = false;
                iterBuildingTiles = 0;
            }
            return true;
        }
        else
        {
            buildingDrawed = true;
            return false;
        }
    }
    return false;
}

vector<int> Map::fillBuildingPositionsTaken(int y, string letter)
{
    vector<int> positions;
    if(letter == "c" || letter == "h" || letter == "m")
    {
        positions.push_back(y);
        positions.push_back(y+1);
        positions.push_back(y+2);
        positions.push_back(y+3);
        buildingPositionsfilled = true;
        if(letter == "c")
        {
            positionsXDoorCenter.push_back(x+1);
            positionsXDoorCenter.push_back(x+2);
            positionsYDoorCenter.push_back(y+4);
            positionsYDoorCenter.push_back(y+4);
        }
        else if (letter == "m")
        {
            positionsXDoorMart.push_back(x+1);
            positionsXDoorMart.push_back(x+2);
            positionsYDoorMart.push_back(y+4);
            positionsYDoorMart.push_back(y+4);
        }        
    }
    
    return positions;
}

vector<Tile*> Map::getTiles()
{
    return tiles;
}

bool Map::IsTileCenter(int x, int y)
{
	if (x < 0 || y < 0 || x > 790)
	{
		return false;
	}

    x = x/20;
    y = y/18;

    int position = ((40 * y) + (x));
    
	if (position < 1760)
	{
		if(tiles[position]->getPokeCenterDoor())
		{
			return true;   
		}
	}
    return false;
}   

bool Map::IsTileMart(int x, int y)
{
	if (x < 0 || y < 0 || x > 790)
	{
		return false;
	}

    x = x/20;
    y = y/18;

    int position = ((40 * y) + (x));
    
	if (position < 1760)
	{
		if(tiles[position]->getPokeMartDoor())
		{
			return true;   
		}
	}
    return false;
}   

bool Map::IsTileValid(int x, int y)
{
	if (x < 0 || y < 0 || x > 790)
	{
		return false;
	}

    x = x/20;
    y = y/18;

    int position = ((40 * y) + (x));
    
	if (position < 1760)
	{
		if(tiles[position]->isValid())
		{
			return true;   
		}
	}
    return false;
}

bool Map::IsTileBush(int x, int y)
{
    if (x < 0 || y < 0 || x > 790)
	{
		return false;
	}

    x = x/20;
    y = y/18;

    int position = ((40 * y) + (x));

    if (position < 1760)
	{
		if(tiles[position]->getName() == "b")
		{
			return true;   
		}
	}
    return false;
}