#pragma once
#include "Item.h"

class Potion : public Item
{
public:
    Potion(string name, int value, int hpRestore);
    ~Potion();
    void setName(string theName);
    void setHpRestore(int hp);
    string getName();
    int getHpRestore();
    int getValue();
    
private:
    int hpRestore;
};