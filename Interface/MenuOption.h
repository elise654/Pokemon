#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "../Pokemon/Trainer.h"


using namespace std;
using namespace sf;

class MenuOption
{
public:
    MenuOption(Sound &sound, Trainer* trainer, Interface::Player &player);
    ~MenuOption();
    
    void draw(RenderWindow& win);

private:
	Font font;

    void SetInterface(RenderWindow &bagWindow);
	Texture textureBackGround;
	Sprite smallCursor;
	Sprite MoveCursor(string direction, Sprite cursor); 
	Texture texture;
	Sprite captureSprite;
	Image captureImage;
    Texture captureTexture;
	string SelectItem();
	Sound *music;
	Trainer* trainer;
	Interface::Player* player;
};