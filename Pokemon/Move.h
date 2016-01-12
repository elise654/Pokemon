#pragma once
#include "Type.h"
#include <string>

using namespace std;

class Move
{
public:
    Move(string name, SoftwareLogic::Type type, int basePower);
    Move();
	~Move();

    string getName() const;
    SoftwareLogic::Type getType() const;
    int getBasePower() const;

private:
    string name;
    SoftwareLogic::Type type;
	int basePower;
};