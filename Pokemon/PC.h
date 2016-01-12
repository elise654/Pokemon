#pragma once 
#include "Pokemon.h"
#include <vector>

using namespace std;

class PC
{
public:
    PC();
    ~PC();

    vector<Pokemon*> getPokemons() const;
    void AddPokemon(Pokemon* pokemon);
    //void TakePokemonToParty(Pokemon* pokemon);
    void RemovePokemon(Pokemon* pokemon);
    //void MovePokemon(Pokemon pokemon, int position);

private:
    
    vector<Pokemon*> pokemons;
};