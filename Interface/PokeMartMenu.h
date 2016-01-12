#pragma once 
#include <string>
#include "SFML/Graphics.hpp"
#include "../Pokemon/Trainer.h"
#include "../Pokemon/PokeBall.h"
#include "../Pokemon/Potion.h"
#include <sstream>

using namespace sf;

class PokeMartMenu
{
public:
    PokeMartMenu(Trainer* trainer);
    ~PokeMartMenu();

    void Draw();

private:
    Trainer* trainer;

    Image imageCapture;
    Texture textureCapture;
    Sprite capture;

    Font font;
    Texture textureCursor;
    Sprite cursor;
    Text textPokeball;
    Text textPotion;
    Text textSuperPotion;

    Text textTrainerPokeball;
    Text textTrainerPotion;
    Text textTrainerSuperPotion;

    Text textMoney;

    int pokeballNumber;
    int potionNumber;
    int superPotionNumber;
    
    int pokeballTrainerNumber;
    int potionTrainerNumber;
    int superPotionTrainerNumber;

    void SetInterface(RenderWindow* window);
    void MoveCursor(RenderWindow* window, string direction);
    void BuyItem(RenderWindow* window);
    void SellItem(RenderWindow* window);
    void SelectOption(RenderWindow* window);
    void Wait();

    string IntToString(int number);
    Text InitializeText(String text, int characterSize, Color color, int x, int y);
};