#include "SaveGame.h"
#include <sstream>


using namespace std;
using namespace DataDeposit;

SaveGame::SaveGame(string name, int positionX, int positionY, vector<Pokemon*> pokemon, vector<Item*> item, PC* pc, Pokedex* pokedex, int money)
{
	this->name = name;
	this->positionX = positionX;
	this->positionY = positionY;
	this->pokemon = pokemon;
	this->item = item;
	this->pc = pc;
	this->pokedex = pokedex;
	this->money = money;
}

SaveGame::~SaveGame() 
{
	delete pc;
	delete pokedex;
}

void SaveGame::WriteXML()
{
	TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "no");
    TiXmlDocument* doc = new TiXmlDocument;
    doc->LinkEndChild(declaration);

	saveGame = new TiXmlElement("SaveGame");

	TiXmlElement* name = new TiXmlElement("Name");
	TiXmlText* characterName = new TiXmlText(this->name.c_str());
	name->LinkEndChild(characterName);
	saveGame->LinkEndChild(name);

	TiXmlElement* position = new TiXmlElement("Position");
	TiXmlElement* positionX = new TiXmlElement("X");
	TiXmlText* positionXText = new TiXmlText(IntToString(this->positionX).c_str());
	positionX->LinkEndChild(positionXText);
	TiXmlElement* positionY = new TiXmlElement("Y");
	TiXmlText* positionYText = new TiXmlText(IntToString(this->positionY).c_str());
	positionY->LinkEndChild(positionYText);
	position->LinkEndChild(positionX);
	position->LinkEndChild(positionY);
	saveGame->LinkEndChild(position);

	WritePokemon();
	WriteItem();
	WritePC();
	WritePokedex();

	doc->LinkEndChild(saveGame);
	doc->SaveFile("SaveGame.xml");
}

void SaveGame::WritePokemon()
{
	TiXmlElement* pokemonList = new TiXmlElement("PokemonList");
	for(vector<Pokemon*>::iterator it = this->pokemon.begin(); it != this->pokemon.end(); ++it) 
	{
		TiXmlElement* pokemonElement = new TiXmlElement("Pokemon");
		TiXmlText* pokemonName = new TiXmlText((*it)->getName().c_str());
		TiXmlText* pokemonCurrentHP = new TiXmlText(IntToString((*it)->getCurrentHealth()).c_str());
		TiXmlText* pokemonFullHP = new TiXmlText(IntToString((*it)->getFullHealth()).c_str());
		TiXmlText* pokemonCurrentExperience = new TiXmlText(IntToString((*it)->getCurrentExperience()).c_str());
		TiXmlText* pokemonLevelExperience = new TiXmlText(IntToString((*it)->getExperienceToLevelUp()).c_str());
		TiXmlText* pokemonLevel = new TiXmlText(IntToString((*it)->getLevel()).c_str());
		TiXmlElement* pokemonNameTag = new TiXmlElement("Name");
		pokemonNameTag->LinkEndChild(pokemonName);
		TiXmlElement* pokemonHealthTag = new TiXmlElement("CurrentHealth");
		pokemonHealthTag->LinkEndChild(pokemonCurrentHP);
		TiXmlElement* pokemonFullHealthTag = new TiXmlElement("FullHealth");
		pokemonFullHealthTag->LinkEndChild(pokemonFullHP);
		TiXmlElement* pokemonExperienceTag = new TiXmlElement("CurrentExperience");
		pokemonExperienceTag->LinkEndChild(pokemonCurrentExperience);
		TiXmlElement* pokemonExperienceLevelTag = new TiXmlElement("ExperienceLevel");
		pokemonExperienceLevelTag->LinkEndChild(pokemonLevelExperience);
		TiXmlElement* pokemonLevelTag = new TiXmlElement("Level");
		pokemonLevelTag->LinkEndChild(pokemonLevel);
		

		pokemonElement->LinkEndChild(pokemonNameTag);
		pokemonElement->LinkEndChild(pokemonHealthTag);
		pokemonElement->LinkEndChild(pokemonFullHealthTag);
		pokemonElement->LinkEndChild(pokemonExperienceTag);
		pokemonElement->LinkEndChild(pokemonExperienceLevelTag);
		pokemonElement->LinkEndChild(pokemonLevelTag);
		pokemonList->LinkEndChild(pokemonElement);
	}
	saveGame->LinkEndChild(pokemonList);
}

void SaveGame::WriteItem()
{
	TiXmlElement* itemList = new TiXmlElement("ItemList");
	TiXmlElement* moneyElement = new TiXmlElement("Money");
	for(vector<Item*>::iterator it = this->item.begin(); it != this->item.end(); ++it) 
	{
		TiXmlElement* itemElement = new TiXmlElement("Item");
		TiXmlText* itemText = new TiXmlText((*it)->getName().c_str());
		itemElement->LinkEndChild(itemText);
		itemList->LinkEndChild(itemElement);
	}
	TiXmlText* moneyText = new TiXmlText(IntToString(this->money).c_str());
	moneyElement->LinkEndChild(moneyText);
	saveGame->LinkEndChild(moneyElement);
	saveGame->LinkEndChild(itemList);
}

void SaveGame::WritePC()
{
	TiXmlElement* pcList = new TiXmlElement("PCList");
	vector<Pokemon*> pcPokemon = pc->getPokemons();
	for(vector<Pokemon*>::iterator it = pcPokemon.begin(); it != pcPokemon.end(); ++it) 
	{
		TiXmlText* pcText = new TiXmlText((*it)->getName().c_str());
		TiXmlElement* pcElement = new TiXmlElement("PCPokemon");
		pcElement->LinkEndChild(pcText);
		pcList->LinkEndChild(pcElement);
	}
	saveGame->LinkEndChild(pcList);
}

void SaveGame::WritePokedex()
{
	TiXmlElement* pokedexList = new TiXmlElement("PokedexList");
	vector<Pokemon*> pokedexPokemon = pokedex->getPokemons();
	for(vector<Pokemon*>::iterator it = pokedexPokemon.begin(); it != pokedexPokemon.end(); ++it) 
	{
		TiXmlElement* pokedexElement = new TiXmlElement("PokedexPokemon");
		TiXmlText* pokedexText = new TiXmlText((*it)->getName().c_str());
		pokedexElement->LinkEndChild(pokedexText);
		pokedexList->LinkEndChild(pokedexElement);
	}
	saveGame->LinkEndChild(pokedexList);
}

string SaveGame::IntToString(int intToConvert)
{
  ostringstream os;
  os << intToConvert;
  return os.str();
}
