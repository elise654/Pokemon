#pragma once
#include "Pokemon.h"
#include <vector>
#include <string>

using namespace std;


class Party
{
public:
    Party();
    ~Party();

    vector<Pokemon*> getPokemons() const;

    bool AddPokemon(Pokemon* pokemon);
    bool RemovePokemon(Pokemon* pokemon);
    bool ChangeOrder(Pokemon* pokemon1, Pokemon* pokemon2);


private:
    vector<Pokemon*> pokemons;
    int nbPokemons;


};