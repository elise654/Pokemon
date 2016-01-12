#pragma once
#include "../Pokemon/Bag.h"
#include "../Pokemon/Party.h"
#include "../Pokemon/Trainer.h"
#include "SFML/Graphics.hpp"
#include <sstream>

using namespace sf;

class MenuBag
{
public:
    MenuBag(Bag* bag, Party* theParty, string origin, Pokemon* enemy, Trainer* trainer, RenderWindow& combatWin);
    ~MenuBag();
    
    void setItemsNumber(Bag* bag);
    
    void draw(RenderWindow& win);

private:

    Font font;

    Text textPokeball;
    Text textPotion;
    Text textSuperPotion;

    Text lines1;
    Text lines2;
    Text lines3;

    Sprite cursor;
    Sprite smallCursor;
	Sprite smallCursorPotion;
	Texture textureCursor;
    Sprite captureSprite;
    Image captureImage;
    Texture captureTexture;
	Sprite captureSpriteMenu;
    Image captureImageMenu;
    Texture captureTextureMenu;
	Sprite captureSpriteMenuItem;
	Image captureImageMenuItem;
    Texture captureTextureMenuItem;

	RenderWindow* combatWin;

    Bag* bag;
	Party* party;
	string origin;
	Trainer* trainer;
	Pokemon* enemy;

    int pokeballCount;
    int potionCount;
    int superPotionCount;

    bool isItemSelected;
	bool isItemUsed;

    string intToString(int number);
    void SetInterface(RenderWindow* bagWindow);
    void SetItems();
    Sprite MoveCursor(string direction, Sprite cursor);  
    string SelectItem(RenderWindow* window);
	Sprite MoveSmallCursor(string direction, Sprite theCursor, Sprite smallCursor);
	string SelectItemSmallCursor(RenderWindow* window);
	void SetDescriptionItem(Sprite cursor, RenderWindow* window);
	void usePotion(RenderWindow* window);
	void SelectPotionSmallCursor(RenderWindow* bagWindow, string item);
	void ThrowItem(RenderWindow* bagWindow, string item);
	void Wait();

};