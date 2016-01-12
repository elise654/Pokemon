#include "Tile.h"

Tile::Tile(string letter, float positionX, float positionY)
{
    this->valid = true;
    this->name = letter;
    this->isPokeCenterDoor = false;
    this->isPokeMartDoor = false;
    if(letter == "h")
        this->texture.loadFromFile("Images/House.png");
    else if(letter == "c")
        this->texture.loadFromFile("Images/PokeCenter.png");
    else if(letter == "s")
        this->texture.loadFromFile("Images/Tile_Sand.png");
    else if(letter == "g")
        this->texture.loadFromFile("Images/Tile_Grass.png");
    else if(letter == "p")
        this->texture.loadFromFile("Images/Tile_Path.png");
    else if(letter == "m")
        this->texture.loadFromFile("Images/PokeMart.png");
    else if(letter == "b")
        this->texture.loadFromFile("Images/Tile_Bush.png");

    this->setTexture(texture);
    this->setPosition(positionX, positionY);


}
Tile::~Tile()
{

}

bool Tile::isValid()
{
    return this->valid;
}

bool Tile::getPokeCenterDoor() const
{
    return this->isPokeCenterDoor;
}

bool Tile::getPokeMartDoor() const
{
    return this->isPokeMartDoor;
}

string Tile::getName() const
{
    return this->name;
}

void Tile::setInvalid()
{
    this->valid = false;
}

void Tile::setPokeCenterDoor()
{
    this->isPokeCenterDoor = true;
}
void Tile::setPokeMartDoor()
{
    this->isPokeMartDoor = true;
}