#pragma once
#include "Pokemon.h"
#include <vector>
#include <string>

using namespace std;

class Pokedex
{
public:
    Pokedex();
    ~Pokedex();

    vector<Pokemon*> getPokemons() const;
    Pokemon* getPokemon(string name) const;
    void AddPokemon(Pokemon* pokemon);

private:

    vector<Pokemon*> pokemons;

};