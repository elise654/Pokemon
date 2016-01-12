#pragma once 
#include <vector>
#include "Bag.h"
#include "Pokedex.h"
#include "Party.h"
#include "PC.h"

using namespace std;

class Trainer
{
public:

    Trainer();
    ~Trainer();

    void CapturePokemon(Pokemon* pokemon);
    void setPokemonToParty(Pokemon* pokemon);
    void DeletePokemonFromParty(Pokemon* pokemon);
    Party* getParty() const;

    void AddPokemonToPokedex(Pokemon* pokemon);
    vector<Pokemon*> getPokemonsFromPokedex() const;
    
    void SellItem(Item* item);
    void BuyItem(Item* item);
    Bag* getBag() const;
    
    void setPokemonToPC(Pokemon* pokemon);
    void DeletePokemonFromPC(Pokemon* pokemon);
    vector<Pokemon*> getPokemonsFromPC() const;
	PC* getPC() const;
	Pokedex* getPokedex() const;

private:
    Bag* trainerBag;
    Pokedex* trainerPokedex;
    Party* trainerParty;
    PC* trainerPC;
};