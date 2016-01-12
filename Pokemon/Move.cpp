#include "Move.h"

Move::Move(string theName,SoftwareLogic::Type theType, int basePower)
{
    this->name = theName;
    this->type = theType;
	this->basePower = basePower;
}
Move::Move()
{
}
Move::~Move()
{
}

string Move::getName() const
{
    return this->name;
}

SoftwareLogic::Type Move::getType() const
{
    return this->type;
}

int Move::getBasePower() const
{
    return this->basePower;
}