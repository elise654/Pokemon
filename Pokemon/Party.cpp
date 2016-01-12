#include "Party.h"


Party::Party()
{
    this->nbPokemons = 0;
}
Party::~Party()
{

    this->pokemons.clear();
}

vector<Pokemon*> Party::getPokemons() const
{
    return this->pokemons;
}

bool Party::AddPokemon(Pokemon* pokemon)
{
    if(this->nbPokemons == 6)
    {
        return false;
    }
    this->pokemons.push_back(pokemon);
    this->nbPokemons++;
    return true;
}

bool Party::RemovePokemon(Pokemon* pokemon)
{
    if(this->nbPokemons == 1)
    {
        return false;
    }
    bool removed = false;
    vector<Pokemon*> tempPokemons;

    for(int i = 0; i < this->pokemons.size(); i++)
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
    if(this->pokemons.size() == (this->nbPokemons - 1))
    {
        this->nbPokemons--;
        return true;
    }
    return false;
}

bool Party::ChangeOrder(Pokemon* pokemon1, Pokemon* pokemon2)
{
    int pokemon1Position = -1;
    int pokemon2Position = -1;
    if(pokemon1 == NULL || pokemon2 == NULL)
    {
        return false;
    }
    vector<Pokemon*> tempPokemons = this->pokemons;
    this->pokemons.clear();

    for(int i = 0; i < tempPokemons.size(); i++)
    {
        if(pokemon1 == tempPokemons[i] && pokemon1Position == -1)
        {
            pokemon1Position = i;
        }
        if(pokemon2 == tempPokemons[i] && pokemon2Position == -1)
        {
            pokemon2Position = i;
        }
    }

    tempPokemons[pokemon1Position] = pokemon2;
    tempPokemons[pokemon2Position] = pokemon1;

    for(int i = 0; i < tempPokemons.size(); i++)
    {
        this->pokemons.push_back(tempPokemons[i]);
    }
    
    return true;
}