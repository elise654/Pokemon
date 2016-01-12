#include "PC.h"

PC::PC()
{

}

PC::~PC()
{
    this->pokemons.clear();
}

vector<Pokemon*> PC::getPokemons() const
{
    return this->pokemons;
}

void PC::AddPokemon(Pokemon* pokemon)
{
    this->pokemons.push_back(pokemon);
}

//void PC::TakePokemonToParty(Pokemon* pokemon)
//{

//}

void PC::RemovePokemon(Pokemon* pokemon)
{
    bool removed = false;
    vector<Pokemon*> tempPokemons;

    for(int i = 0; i < pokemons.size(); i++)
    {
        if(this->pokemons[i] == pokemon && removed == false)
        {
            removed = true;
        }
        else
        {
            tempPokemons.push_back(this->pokemons[i]);
        }
    }
    this->pokemons.clear();
    for(int i = 0; i < tempPokemons.size(); i++)
    {
        this->pokemons.push_back(tempPokemons[i]);
    }
}