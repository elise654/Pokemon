#include "Pokeball.h"

Pokeball::Pokeball(string theName, int theValue, int theChance)
{
    name = theName;
    chance = theChance;
    value = theValue;
}

Pokeball::~Pokeball()
{

}

void Pokeball::setName(string theName)
{
    name = theName;
}
void Pokeball::setChance(float theChance)
{
	chance = theChance;
}


string Pokeball::getName()
{
    return name;
}
float Pokeball::getChance()
{
    return chance;
}
int Pokeball::getValue()
{
	return value;
}
int Pokeball::getHpRestore()
{
    return 0;
}
void Pokeball::setHpRestore(int hp)
{
    this->value = hp;
}