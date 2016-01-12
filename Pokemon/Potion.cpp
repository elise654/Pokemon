#include "Potion.h"

Potion::Potion(string theName, int theValue, int hp)
{
    name = theName;
    value = theValue;
    hpRestore = hp;
}
Potion::~Potion()
{

}
void Potion::setName(string theName)
{
    name  = theName;
}
void Potion::setHpRestore(int hp)
{
    hpRestore = hp;
}
string Potion::getName()
{
    return name;
}
int Potion::getHpRestore()
{
    return hpRestore;
}
int Potion::getValue()
{
	return value;
}