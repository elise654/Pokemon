#pragma once 
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;
using namespace sf;

class Tile : public Sprite
{
public:
    Tile(string letter, float positionX, float positionY);
    ~Tile();

    bool isValid();
    bool getPokeCenterDoor() const;
    bool getPokeMartDoor() const;
    string getName() const;

    void setInvalid();
    void setPokeCenterDoor();
    void setPokeMartDoor();

private:
    string name;
    bool valid;
    bool isPokeCenterDoor;
    bool isPokeMartDoor;
    sf::Texture texture;
};