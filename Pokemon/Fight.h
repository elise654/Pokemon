#pragma once
#ifndef FIGHT_H
#define FIGHT_H
#include "Pokemon.h"
#include "Item.h"
#include "Trainer.h"

using namespace std;

namespace SoftwareLogic
{
	class Fight
	{
		public:
				Fight();
				~Fight();
				Fight(Pokemon* trainerPoke, Pokemon* foePoke);
				void Attack(Pokemon* attacker, Pokemon* defender, Move* attack);
				string UseItem(Pokemon* target, Item* usedItem, Trainer* trainer);
				string setNewExp(Pokemon* pokemon, Pokemon* enemy);
		private:
				Pokemon* trainerPoke;
				Pokemon* foePoke;
				string UsePokeball(Pokemon* target, Item* usedItem, Trainer* trainer);
				int DamageFormula(Pokemon* attacker, Pokemon* defender, Move* attack);
				string LevelUp(Pokemon* pokemon);
	};


}

#endif