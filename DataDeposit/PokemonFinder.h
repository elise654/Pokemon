#pragma once

#ifndef POKEMONFINDER_H
#define POKEMONFINDER_H

#include <vector>
#include "pugixml.hpp"
#include "../Pokemon/Pokemon.h"

using namespace std;

namespace DataDeposit
{
	class PokemonFinder
	{
		public:
			PokemonFinder();
			~PokemonFinder();
			void ReadPokemonAvailable();
			vector<Pokemon*> getWildPokemon() const;
			vector<Pokemon*> getStarterPokemon() const;
			
		private:
			vector<Pokemon*> pokemonStarterAvailable;
			vector<Pokemon*> pokemonWildAvailable;
			int ConvertStringToInt(string stringToConvert);
			void ReadPokemonList(string kind);
			pugi::xml_node pokemonListNode;
			
			
	};
}


#endif