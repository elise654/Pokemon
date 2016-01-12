#pragma once

#ifndef LOADGAME_H
#define LOADGAME_H

#include <vector>
#include "pugixml.hpp"
#include "../Pokemon/Pokemon.h"
#include "../Pokemon/Item.h"

using namespace std;

namespace DataDeposit
{
	class LoadGame
	{
		public:
			LoadGame();
			~LoadGame();
			void ReadElements();
			string getName() const;
			int getPositionX() const;
			int getPositionY() const;
			vector<Pokemon*> getPokemon() const;
			vector<Item*> getItem() const;
			vector<Pokemon*> getPCPokemon() const;
			vector<Pokemon*> getPokedexPokemon() const;
			int getMoney() const;

			
		private:
			string name;
			int positionX;
			int positionY;
			vector<Pokemon*> pokemon;
			vector<Item*> item;
			vector<Pokemon*> pcPokemon;
			vector<Pokemon*> pokedexPokemon;
			int ConvertStringToInt(string stringToConvert);
			int money;
			pugi::xml_node parametres;
			void ReadPokemon();
			void ReadItem();
			void ReadPC();
			void ReadPokedex();
			
			
			
	};
}


#endif