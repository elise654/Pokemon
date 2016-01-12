#include "Bag.h"

Bag::Bag()
{
    this->money = 0;
}

Bag::~Bag()
{
    for(vector<Item*>::const_iterator it = this->items.begin(); it != this->items.end(); it++)
	{
		delete *it;
	}
}

void Bag::AddItem(Item* item)
{
    this->items.push_back(item);
}
 
void Bag::RemoveItem(Item* item)
{
	bool isFound = false;
	vector<Item*>::iterator it;

	for(vector<Item*>::const_iterator it = this->items.begin(); it != this->items.end() && isFound == false; it++)
	{
		if((*it)->getName() == item->getName())
		{
			this->items.erase(it);
			isFound = true;
			break;
		}
	}


}

vector<Item*> Bag::getItems() const
{
    return this->items;
}

void Bag::AddMoney(int cash)
{
    this->money += cash;
}

void Bag::RemoveMoney(int cash)
{
    this->money -= cash;
}

int Bag::getMoney() const
{
    return this->money;
}

string Bag::UsePotion(Pokemon* target, Item* usedItem)
{
	int newHP = target->getCurrentHealth() + usedItem->getHpRestore();
	if(newHP >= target->getFullHealth())
	{
		newHP = target->getFullHealth();
	}
	target->setCurrentHealth(newHP);

	this->RemoveItem(usedItem);
	return "La potion a bien été utilisée";
}