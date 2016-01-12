#include "Pokemon.h"


Pokemon::Pokemon(string theName,int atk,int health,int theSpeed, int exp, int theLevel, int def,  SoftwareLogic::Type type)
{
    this->name = theName;
    this->attack = atk;
    this->fullHealth = health;
    this->currentHealth = fullHealth;
	this->defense = def;
    this->speed = theSpeed;
    this->currentExperience = 0;
    this->experienceToLevelUp = exp;
    this->level = theLevel;
	this->type =  type;
}
Pokemon::Pokemon()
{

}

Pokemon::~Pokemon()
{

}

bool Pokemon::operator==( const Pokemon &_pokemon ) const
{
    if(!(this->name == _pokemon.name))
    {
        return false;
    }
    if(!(this->level == _pokemon.level))
    {
        return false;
    }
    if(!(this->currentExperience == _pokemon.currentExperience))
    {
        return false;
    }
	return true;
}

const Pokemon &Pokemon::operator=( const Pokemon &_pokemon)
{
    this->attack = _pokemon.attack;
    this->currentHealth = _pokemon.currentHealth;
    this->fullHealth = _pokemon.fullHealth;
    this->defense = _pokemon.defense;
    this->speed = _pokemon.speed;
    this->level = _pokemon.level;
    this->currentExperience = _pokemon.currentExperience;
    this->experienceToLevelUp = _pokemon.experienceToLevelUp;
    this->dead = _pokemon.dead;
    this->name = _pokemon.name;
	return *this;
}

//Getters
int Pokemon::getAttack()  const
{
    return this->attack;
}
int Pokemon::getCurrentHealth()  const
{
    return this->currentHealth;
}
int Pokemon::getFullHealth()  const
{
    return this->fullHealth;
}
int Pokemon::getDef()  const
{
    return this->defense;
}
int Pokemon::getSpeed() const
{
    return this->speed;
}
bool Pokemon::isDead() const 
{
    return this->dead;
}
int Pokemon::getCurrentExperience() const 
{
    return this->currentExperience;
}
int Pokemon::getExperienceToLevelUp() const
{
    return this->experienceToLevelUp;
}
int Pokemon::getLevel()  const
{
    return this->level;
}

string Pokemon::getName()  const
{
    return this->name;
}
SoftwareLogic::Type Pokemon::getType() const
{
	return this->type;
}

vector<Move*> Pokemon::getMoves()  const
{
    return this->moves;
}


//Setters
void Pokemon::setAttack(int theattack)
{
    this->attack = theattack;
}
void Pokemon::setCurrentHealth(int health)
{
    this->currentHealth = health;
}
void Pokemon::setFullHealth(int health)
{
    this->fullHealth = health;
}
void Pokemon::setDefense(int def)
{
    this->defense = def;
}
void Pokemon::setSpeed(int theSpeed)
{
    this->speed = theSpeed;
}
void Pokemon::setDead(bool isdead)
{
    this->dead = isdead;
}
void Pokemon::setCurrentExperience(int xp)
{
    this->currentExperience = xp;
}
void Pokemon::setExperienceToLevelUp(int xp)
{
    this->experienceToLevelUp = xp;
}
void Pokemon::setLevel(int lvl)
{
    this->level = lvl;
}
void Pokemon::setName(string theName)
{
    this->name  = theName;
}
void Pokemon::AddMove(Move* move)
{
    moves.push_back(move);
}

void Pokemon::setType(SoftwareLogic::Type theType)
{
    this->type = theType;
}
void Pokemon::setListMove(vector<Move*> themoves)
{
    this->moves = themoves;
}