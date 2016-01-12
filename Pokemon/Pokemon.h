#pragma once
#include <string>
#include "Move.h"
#include <vector>
#include "Type.h"

using namespace std;

class Pokemon
{
public:
    Pokemon(string name,int atk,int health,int speed, int exp, int level, int def,  SoftwareLogic::Type type);
    Pokemon();
    ~Pokemon();

	 //Get
     int getAttack() const;
     int getCurrentHealth() const;
     int getFullHealth() const;
	 int getDef() const;
	 int getSpeed() const;
	 bool isDead() const;
	 int getCurrentExperience() const;
	 int getExperienceToLevelUp() const;
	 int getLevel() const;
	 SoftwareLogic::Type getType() const;
     string getName() const;

    vector<Move*> getMoves() const; 
    //Set
    void setAttack(int theAttack);
    void setCurrentHealth(int health);
    void setFullHealth(int health);
    void setDefense(int def);
    void setSpeed(int theSpeed);
    void setDead(bool isDead);
    void setCurrentExperience(int xp);
    void setExperienceToLevelUp(int xp);
    void setLevel(int lvl);
    void setName(string theName);
    void setType(SoftwareLogic::Type theType);
    void setListMove(vector<Move*> moves);
    void AddMove(Move* move);

    bool operator==(const Pokemon &_pokemon) const;
    const Pokemon &operator=(const Pokemon &_pokemon);

private:
    vector<Move*> moves;
    int attack;
    int currentHealth;
    int fullHealth;
    int defense;
    int speed;
    int level;
    int currentExperience;
    int experienceToLevelUp;
    bool dead;
    string name;
    SoftwareLogic::Type type;
    
};