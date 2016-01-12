#include "Pokedex.h"

Pokedex::Pokedex()
{

}
Pokedex::~Pokedex()
{
    this->pokemons.clear();
}

vector<Pokemon*> Pokedex::getPokemons() const
{
    return this->pokemons;
}

Pokemon* Pokedex::getPokemon(string name) const
{
    for(int i = 0; i < this->pokemons.size() ; i++)
    {
        if(this->pokemons[i]->getName() == name)
        {
            return this->pokemons[i];
        }
    }
    return NULL;
}

void Pokedex::AddPokemon(Pokemon* pokemon)
{
    this->pokemons.push_back(pokemon);
}