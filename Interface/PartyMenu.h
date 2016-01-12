#pragma once

#include "../Pokemon/Party.h"
#include "SFML/Graphics.hpp"
#include <sstream>
#include <vector>

using namespace sf;

class PartyMenu
{
public:
    PartyMenu(Party* party);
    ~PartyMenu();
    void Initialize(RenderWindow* window);
    void Draw();

private:
    Party* party;
    Pokemon* pokemonSelected;
    Pokemon* pokemonToChange;

    Image captureImage;
    Texture captureTexture;
    Sprite capture;

    Sprite cursor;
    Sprite smallCursor;
    Texture textureSmallCursor;
    Texture textureCursor;

    Font font;

    bool isPokemonSelected;
    bool isOrderChanging;
    bool changeUnavailable;
    int partySize;

    void SetRectangles(RenderWindow* window);
    void SetPokemons(RenderWindow* window);
    string IntToString(int number);
    Text InitializeText(String text, int characterSize, Color color, int x, int y);
    void SelectPokemon(RenderWindow* window);
    bool SelectAction(RenderWindow* window);
    void SetPokemonNames(RenderWindow* window);
    void ChangeOrder(RenderWindow* window);

    void MoveCursor(string direction);
    void MoveSmallCursor(string direction);
    void MoveCursorWhileOrderChanging(string direction);



};