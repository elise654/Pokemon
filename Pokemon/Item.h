#pragma once
#include <string>

using namespace std;

class Item
{
public:
    Item();
    ~Item();
    virtual void setName(string theName) = 0;
    virtual void setHpRestore(int hp) = 0;
    virtual string getName() = 0;
    virtual int getHpRestore() = 0;
    virtual int getValue() = 0;
    
protected:
    string name;
    int value;


};