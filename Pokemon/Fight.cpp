#include "Fight.h"
#include <sstream>
#include <ctime>
using namespace std;
using namespace SoftwareLogic;

Fight::Fight()
{
}
Fight::~Fight()
{
}
Fight::Fight(Pokemon* trainerPoke, Pokemon* foePoke)
{
	this->trainerPoke = trainerPoke;
	this->foePoke = trainerPoke;
}
int Fight::DamageFormula(Pokemon* attacker, Pokemon* defender, Move* attack)
{
	/* Damage = ((L * 2 + 10)/250 * (A / D) * B + 2) * M
	L - Level of the attacking Pokémon.
	A - Attack of the attacking Pokémon.
	D - Defense of the defending Pokémon.
	B - The base damage of the attack.
	M - Any damage modifiers. M is calculated as follows:
	
	Modifier = STAB * T * (rand is between [0.85, 1.00])
	STAB - Same-type attack bonus. Value is 1.5 if the Pokémon gets STAB, 1 otherwise.
	T - Type effectiveness. Value can be 0, 0.5, 1 or 2.
	Rand - Random number between 0.85 and 1.00. 
	*/

	float damage = 0;
	float L = attacker->getLevel();
	float A = attacker->getAttack();
	float D = defender->getDef();
	float B = attack->getBasePower();
	float M;
	
	float STAB = 1;
	if(attacker->getType().getTypeName() == attack->getType().getTypeName())
	{
		STAB = 1.5;
	}

	float T = 1;
	if(defender->getType().getWeakness1() == attack->getType().getTypeName() || defender->getType().getWeakness2() == attack->getType().getTypeName())
	{
		T = 2;
	}
	else if(defender->getType().getStrength1() == attack->getType().getTypeName() || defender->getType().getStrength2() == attack->getType().getTypeName())
	{
		T = 0.5;
	}
	srand(time(NULL));
	float Rand = rand() %16 + 85;
	
	M = STAB * T * (Rand / 100);

	damage = abs((((((L * 2 ) + 10)/250) * (A / D) * B )+ 2) * M);

	return damage;
}
void Fight::Attack(Pokemon* attacker, Pokemon* defender, Move* attack)
{
	int damage = DamageFormula(attacker, defender, attack);
	int currentHP;
	if(defender->getCurrentHealth() - damage <= 0)
	{
		currentHP = 0;
		defender->setDead(true);
	}
	else
	{
		currentHP = defender->getCurrentHealth() - damage;
	}

	defender->setCurrentHealth(currentHP);
}
string Fight::UseItem(Pokemon* target, Item* usedItem, Trainer* trainer)
{
	string message;
	if(usedItem->getName() == "Pokeball")
	{
		message = UsePokeball(target, usedItem, trainer);
	}
	else
	{
		message = trainer->getBag()->UsePotion(target, usedItem);
	}
	return message;
}

string Fight::UsePokeball(Pokemon* target, Item* usedItem, Trainer* trainer)
{
	trainer->getBag()->RemoveItem(usedItem);
	bool isCaught = false;
	float Rand = rand() %100 + 1;
	float catchRate;
	catchRate = (3 * target->getFullHealth());
	catchRate -= (2 * target->getCurrentHealth());
	catchRate = catchRate / (3 * target->getFullHealth());
	if(Rand <= (catchRate * 100))
	{
		isCaught = true;
	}

	if(isCaught)
	{
		trainer->getParty()->AddPokemon(target);
		return "Le " + target->getName() + " sauvage à été capturé!";
	}
	return "Le pokmémon n'a pas été capturé.";

}
string Fight::setNewExp(Pokemon* pokemon, Pokemon* enemy)
{
	int currentExp = pokemon->getCurrentExperience();
	int addedExp = abs((65 * enemy->getLevel())/7); //65 est, dans le vrai jeu, une valeur spécifique de base à chaque pokemon (ex: bulbasaur vaut 64 exp, charmander 62, etc.)
	stringstream message; 
	message	<< "Votre " + pokemon->getName() << " a gagne " <<endl << endl << addedExp << " points d'experience." << endl << endl;
	if(currentExp + addedExp >= pokemon->getExperienceToLevelUp())
	{
		currentExp = currentExp + addedExp - pokemon->getExperienceToLevelUp();
		message << LevelUp(pokemon);
	}
	else
	{
		currentExp += addedExp;
	}
	pokemon->setCurrentExperience(currentExp);
	return message.str();
}
string Fight::LevelUp(Pokemon* pokemon)
{
	pokemon->setLevel(pokemon->getLevel() + 1);
	pokemon->setFullHealth(pokemon->getFullHealth() + 4);
	pokemon->setDefense(pokemon->getDef() + 2);
	pokemon->setAttack(pokemon->getAttack() + 2);
	pokemon->setSpeed(pokemon->getSpeed() + 2);
	pokemon->setExperienceToLevelUp((4*pow((pokemon->getLevel()),3))/5);
	string message = "Votre " + pokemon->getName() + " a monte d'un niveau!";
	return message;
}