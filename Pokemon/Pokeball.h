#pragma once
#include "Item.h"

class Pokeball: public Item
{

public:
    Pokeball(string name, int value, int chance);
    ~Pokeball();
    void setName(string theName);
    void setChance(float theChance);
    void setHpRestore(int hp);

    float getChance();
    string getName();
    int getValue();
    int getHpRestore();
    
private:
    float chance;

};