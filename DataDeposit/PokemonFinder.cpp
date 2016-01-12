#include "PokemonFinder.h"
#include "../Pokemon/Type.h"


using namespace std;
using namespace DataDeposit;


PokemonFinder::PokemonFinder()
{
}

PokemonFinder::~PokemonFinder()
{
	pokemonStarterAvailable.clear();
	pokemonWildAvailable.clear();
}

void PokemonFinder::ReadPokemonAvailable()
{
	
	//Déclaration d'un conteneur XML potentiel
	pugi::xml_document mediaXML;
	//Chargement du contenu XML
	pugi::xml_parse_result result = mediaXML.load_file("../Interface/listPokemon.xml");
	//On cherche un node de premier niveau, enfant du contenu
	pokemonListNode = mediaXML.child("ListPokemon");


	ReadPokemonList("StarterPokemon");
	ReadPokemonList("WildPokemon");

}

void PokemonFinder::ReadPokemonList(string kind)
{
	//Set les types
	SoftwareLogic::Type fire("Fire");
	fire.setStrength("Grass","Steel");
	fire.setWeakness("Water");
	SoftwareLogic::Type water("Water");
	water.setStrength("Fire");
	water.setWeakness("Grass","Electric");
	SoftwareLogic::Type grass("Grass");
	grass.setStrength("Water");
	grass.setWeakness("Fire","Flying");
	SoftwareLogic::Type electric("Electric");
	electric.setStrength("Water","Flying");
	electric.setWeakness("NULL");
	SoftwareLogic::Type flying("Flying");
	flying.setStrength("Grass","Fighting");
	flying.setWeakness("Electric");
	SoftwareLogic::Type normal("Normal");
	normal.setStrength("NULL");
	normal.setWeakness("Fighting");
	SoftwareLogic::Type steel("Steel");
	steel.setStrength("NULL");
	steel.setWeakness("Fire","Water");
	SoftwareLogic::Type fighting("Fighting");
	fighting.setStrength("Normal","Dark");
	fighting.setWeakness("Flying");
	SoftwareLogic::Type	dark("Dark");
	dark.setStrength("NULL");
	dark.setWeakness("Fighting");

	for (pugi::xml_node pokemonList = pokemonListNode.child(kind.c_str()); pokemonList!= nullptr; pokemonList= pokemonList.next_sibling(kind.c_str()))
	{
		Pokemon* pokemonElement = new Pokemon();
		string name = pokemonList.child_value("Name");
		name.erase(name.find_last_not_of("\n\t\t\t")+1);
		name = name.substr(4);
		pokemonElement->setName(name);
		pokemonElement->setLevel(ConvertStringToInt(pokemonList.child_value("Level")));
		pokemonElement->setFullHealth(ConvertStringToInt(pokemonList.child_value("MaxHP")));
		pokemonElement->setCurrentHealth(ConvertStringToInt(pokemonList.child_value("MaxHP")));
		pokemonElement->setAttack(ConvertStringToInt(pokemonList.child_value("Attack")));
		pokemonElement->setDefense(ConvertStringToInt(pokemonList.child_value("Defense")));
		pokemonElement->setSpeed(ConvertStringToInt(pokemonList.child_value("Speed")));
		int expToLevelUp = (4*pow((ConvertStringToInt(pokemonList.child_value("Level"))),3))/5;
		pokemonElement->setExperienceToLevelUp(expToLevelUp);
		pokemonElement->setCurrentExperience(0);
		pokemonElement->setDead(false);
		
		string type = pokemonList.child_value("Type");
		type.erase(type.find_last_not_of("\n\t\t\t")+1);
		type = type.substr(4);

		if(type == fire.getTypeName())
		{
			pokemonElement->setType(fire);
		}
		else if(type == water.getTypeName())
		{
			pokemonElement->setType(water);
		}
		else if(type == electric.getTypeName())
		{
			pokemonElement->setType(electric);
		}
		else if(type == grass.getTypeName())
		{
			pokemonElement->setType(grass);
		}
		else if(type == normal.getTypeName())
		{
			pokemonElement->setType(normal);
		}
		else if(type == flying.getTypeName())
		{
			pokemonElement->setType(flying);
		}

		vector<Move*> movePokemon;
		for (pugi::xml_node moveList = pokemonList.child("Move"); moveList!= nullptr; moveList= moveList.next_sibling("Move"))
		{
			string typeName = moveList.child_value("MoveType");
			typeName.erase(typeName.find_last_not_of("\n\t\t\t")+1);
			typeName = typeName.substr(5);
			
			SoftwareLogic::Type type;
			if(typeName == fire.getTypeName())
			{
				type = fire;
			}
			else if(typeName == water.getTypeName())
			{
				type = water;
			}
			else if(typeName == electric.getTypeName())
			{
				type = electric;
			}
			else if(typeName == grass.getTypeName())
			{
				type = grass;
			}
			else if(typeName == normal.getTypeName())
			{
				type = normal;
			}
			else if(typeName == flying.getTypeName())
			{
				type = flying;
			}
			else if(typeName == dark.getTypeName())
			{
				type = dark;
			}
			else if(typeName == steel.getTypeName())
			{
				type = steel;
			}
			else if(typeName == fighting.getTypeName())
			{
				type = fighting;
			}

			string moveName = moveList.child_value("MoveName");
			moveName.erase(moveName.find_last_not_of("\n\t\t\t")+1);
			moveName = moveName.substr(5);
			Move* moveElement = new Move(moveName, type, ConvertStringToInt(moveList.child_value("MovePower")));
			movePokemon.push_back(moveElement);
		}
		pokemonElement->setListMove(movePokemon);

		if (kind == "WildPokemon")
		{
			pokemonWildAvailable.push_back(pokemonElement);
		}
		else
		{
			pokemonStarterAvailable.push_back(pokemonElement);
		}
	}
}

vector<Pokemon*> PokemonFinder::getWildPokemon() const
{
	return this->pokemonWildAvailable;
}

vector<Pokemon*> PokemonFinder::getStarterPokemon() const
{
	return this->pokemonStarterAvailable;
}

int PokemonFinder::ConvertStringToInt(string stringToConvert)
{
	int value = atoi(stringToConvert.c_str());
	return value;
}
