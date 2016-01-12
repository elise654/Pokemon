#include "Type.h"

using namespace std;
using namespace SoftwareLogic;

Type::Type()
{
}
Type::~Type()
{
}
Type::Type(string typeName)
{
	this->name = typeName;
}
void Type::setWeakness(string weaknessTypeName1, string weaknessTypeName2)
{
	this->weakness1 = weaknessTypeName1;
	this->weakness2 = weaknessTypeName2;
}
void Type::setWeakness(string weaknessTypeName)
{
	this->weakness1 = weaknessTypeName;
	this->weakness2 = "NULL";
}
void Type::setStrength(string strengthTypeName1, string strengthTypeName2)
{
	this->strength1 = strengthTypeName1;
	this->strength2 = strengthTypeName2;
}
void Type::setStrength(string strengthTypeName)
{
	this->strength1 = strengthTypeName;
	this->strength2 = "NULL";
}
string Type::getWeakness1() const
{
	return this->weakness1;
}
string Type::getWeakness2() const
{
	return this->weakness2;
}
string Type::getStrength1() const
{
	return this->strength1;
}
string Type::getStrength2() const
{
	return this->strength2;
}
string Type::getTypeName() const
{
	return this->name;
}