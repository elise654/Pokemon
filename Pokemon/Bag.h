#pragma once
#include "Item.h"
#include <vector>
#include "Pokemon.h"

using namespace std;

class Bag
{
public:
    Bag();
    ~Bag();

    vector<Item*> getItems() const;

    void AddItem(Item* item);
    void RemoveItem(Item* item);
    void AddMoney(int cash);
    void RemoveMoney(int cash);
    int getMoney() const;
	string UsePotion(Pokemon* target, Item* usedItem);


private:
    vector<Item*> items;
    int money;

};