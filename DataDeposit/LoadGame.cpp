#include "LoadGame.h"
#include "../Pokemon/Potion.h"
#include "../Pokemon/Pokeball.h"
#include "PokemonFinder.h"

using namespace std;
using namespace DataDeposit;

LoadGame::LoadGame()
{

}

LoadGame::~LoadGame()
{

}

void LoadGame::ReadElements()
{
	//Déclaration d'un conteneur XML potentiel
	pugi::xml_document mediaXML;
	//Chargement du contenu XML
	pugi::xml_parse_result result = mediaXML.load_file("../Interface/SaveGame.xml");
	//On cherche un node de premier niveau, enfant du contenu
	parametres = mediaXML.child("SaveGame");

	name = parametres.child_value("Name");
	pugi::xml_node positionNode = parametres.child("Position");
	positionX = ConvertStringToInt(positionNode.child_value("X"));
	positionY = ConvertStringToInt(positionNode.child_value("Y"));

	//Appel des autre méthodes nécessaire à la lecture du fichier
	ReadPokemon();
	ReadItem();
	ReadPC();
	ReadPokedex();
}

void LoadGame::ReadPokemon()
{
	pugi::xml_node pokemonListNode = parametres.child("PokemonList");
	for (pugi::xml_node pokemonList = pokemonListNode.child("Pokemon"); pokemonList!= nullptr; pokemonList= pokemonList.next_sibling("Pokemon"))
	{
		Pokemon* pokemonElement = new Pokemon();
		pokemonElement->setName(pokemonList.child_value("Name"));
		pokemonElement->setCurrentHealth(ConvertStringToInt(pokemonList.child_value("CurrentHealth")));
		pokemonElement->setFullHealth(ConvertStringToInt(pokemonList.child_value("FullHealth")));
		pokemonElement->setExperienceToLevelUp(ConvertStringToInt(pokemonList.child_value("ExperienceLevel")));
		pokemonElement->setCurrentExperience(ConvertStringToInt(pokemonList.child_value("CurrentExperience")));
		pokemonElement->setLevel(ConvertStringToInt(pokemonList.child_value("Level")));
		if(pokemonElement->getCurrentHealth() > 0)
		{
			pokemonElement->setDead(false);
		}
		//WILD
		DataDeposit::PokemonFinder* pokemonFinder = new DataDeposit::PokemonFinder();
		pokemonFinder->ReadPokemonAvailable();
		vector<Pokemon*> wildList = pokemonFinder->getWildPokemon();
		for(vector<Pokemon*>::iterator it = wildList.begin(); it != wildList.end(); it++)
		{
			if((*it)->getName() == pokemonElement->getName())
			{
				//SET
				pokemonElement->setAttack((*it)->getAttack());
				pokemonElement->setDefense((*it)->getDef());
				pokemonElement->setSpeed((*it)->getSpeed());
				pokemonElement->setListMove((*it)->getMoves());
			}
		}
		//STARTER
		vector<Pokemon*> starterList = pokemonFinder->getStarterPokemon();
		delete pokemonFinder;
		for(vector<Pokemon*>::iterator it = starterList.begin(); it != starterList.end(); it++)
		{
			if((*it)->getName() == pokemonElement->getName())
			{
				//SET
				pokemonElement->setAttack((*it)->getAttack());
				pokemonElement->setDefense((*it)->getDef());
				pokemonElement->setSpeed((*it)->getSpeed());
				pokemonElement->setListMove((*it)->getMoves());
			}
		}

		pokemon.push_back(pokemonElement);
	}
}


void LoadGame::ReadItem()
{
	pugi::xml_node itemList = parametres.child("ItemList");
	for (pugi::xml_node pcPokemonXML = itemList.child("Item"); pcPokemonXML!= nullptr; pcPokemonXML = pcPokemonXML.next_sibling("Item"))
	{
		string itemXML = pcPokemonXML.first_child().value();
		if(itemXML == "Potion")
		{
			Potion* potionElement = new Potion("Potion", 300, 20);
			item.push_back(potionElement);
		}
		else if (itemXML == "Super Potion")
		{
			Pokeball* pokeballElement = new Pokeball("Super Potion", 600, 50);
			item.push_back(pokeballElement);
		}
		else if (itemXML == "Pokeball")
		{
			Pokeball* pokeballElement = new Pokeball("Pokeball", 200, 0);
			item.push_back(pokeballElement);
		}
	}
	money = ConvertStringToInt(parametres.child_value("Money"));
}

void LoadGame::ReadPC()
{
	pugi::xml_node pcList = parametres.child("PCList");
	for (pugi::xml_node pcPokemonXML = pcList.child("PCPokemon"); pcPokemonXML!= nullptr; pcPokemonXML = pcPokemonXML.next_sibling("PCPokemon"))
	{
		Pokemon* pokemonElement = new Pokemon();
		pokemonElement->setName(pcPokemonXML.first_child().value());
		

		pcPokemon.push_back(pokemonElement);
	}
}

void LoadGame::ReadPokedex()
{
	pugi::xml_node pokedexList = parametres.child("PokedexList");
	for (pugi::xml_node pokedexPokemonXML = pokedexList.child("PokedexPokemon"); pokedexPokemonXML!= nullptr; pokedexPokemonXML = pokedexPokemonXML.next_sibling("PokedexPokemon"))
	{
		Pokemon* pokemonElement = new Pokemon();
		pokemonElement->setName(pokedexPokemonXML.first_child().value());

		pokedexPokemon.push_back(pokemonElement);
	}
}

string LoadGame::getName() const
{
	return this->name;
}

int LoadGame::getPositionX() const
{
	return this->positionX;
}

int LoadGame::getPositionY() const
{
	return this->positionY;
}

vector<Pokemon*> LoadGame::getPokemon() const
{
	return this->pokemon;
}

vector<Item*> LoadGame::getItem() const
{
	return this->item;
}

int LoadGame::getMoney() const
{
	return this->money;
}

vector<Pokemon*> LoadGame::getPCPokemon() const
{
	return this->pcPokemon;
}

vector<Pokemon*> LoadGame::getPokedexPokemon() const
{
	return this->pokedexPokemon;
}

int LoadGame::ConvertStringToInt(string stringToConvert)
{
	int value = atoi(stringToConvert.c_str());
	return value;
}
