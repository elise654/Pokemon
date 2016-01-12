#pragma once

#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <string>
#include <vector>
#include "tinyxml.h"
#include "tinystr.h"
#include "../Pokemon/Pokemon.h"
#include "../Pokemon/Item.h"
#include "../Pokemon/PC.h"
#include "../Pokemon/Pokedex.h"

using namespace std;

namespace DataDeposit
{
	class SaveGame
	{
		public:
			SaveGame(string name, int positionX, int positionY, vector<Pokemon*> pokemon, vector<Item*> item, PC* pc, Pokedex* pokedex, int money);
			~SaveGame();
			void WriteXML();
			string IntToString(int intToConvert);
			
		private:
			string name;
			int positionX;
			int positionY;
			vector<Pokemon*> pokemon;
			vector<Item*> item;
			PC* pc;
			Pokedex* pokedex;
			int money;
			void WritePokemon();
			void WriteItem();
			void WritePC();
			void WritePokedex();
			TiXmlElement* saveGame;

			
			
	};
}


#endif