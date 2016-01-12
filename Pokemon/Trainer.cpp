#include "Trainer.h"


Trainer::Trainer()
{
    this->trainerBag = new Bag();
    this->trainerParty = new Party();
    this->trainerPokedex = new Pokedex();
    this->trainerPC = new PC();
}
Trainer::~Trainer()
{
    delete trainerBag;
    delete trainerParty;
    delete trainerPC;
    delete trainerPokedex;
}

void Trainer::CapturePokemon(Pokemon* pokemon)
{
    if(!(this->trainerParty->AddPokemon(pokemon)))
    {
        this->trainerPC->AddPokemon(pokemon);
    }
}

void Trainer::DeletePokemonFromParty(Pokemon* pokemon)
{
    this->trainerParty->RemovePokemon(pokemon);
}

void Trainer::setPokemonToParty(Pokemon* pokemon)
{
    this->trainerPC->RemovePokemon(pokemon);
    this->trainerParty->AddPokemon(pokemon);
}

Party* Trainer::getParty() const
{
    return this->trainerParty;
}

void Trainer::AddPokemonToPokedex(Pokemon* pokemon)
{
    this->trainerPokedex->AddPokemon(pokemon);
}

vector<Pokemon*> Trainer::getPokemonsFromPokedex() const
{
    return this->trainerPokedex->getPokemons();
	
}

void Trainer::BuyItem(Item* item)
{
    this->trainerBag->AddItem(item);
    this->trainerBag->RemoveMoney(item->getValue());
}
void Trainer::SellItem(Item* item)
{
    this->trainerBag->RemoveItem(item);
    this->trainerBag->AddMoney(item->getValue());
}

Bag* Trainer::getBag() const
{
   return this->trainerBag;
}

void Trainer::setPokemonToPC(Pokemon* pokemon)
{
    this->trainerParty->RemovePokemon(pokemon);
    this->trainerPC->AddPokemon(pokemon);
}
void Trainer::DeletePokemonFromPC(Pokemon* pokemon)
{
    this->trainerPC->RemovePokemon(pokemon);
}

vector<Pokemon*> Trainer::getPokemonsFromPC() const
{
	return this->trainerPC->getPokemons();
}

PC* Trainer::getPC() const
{
	return this->trainerPC;
}

Pokedex* Trainer::getPokedex() const
{
	return this->trainerPokedex;
}