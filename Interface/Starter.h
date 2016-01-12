#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "../Pokemon/Trainer.h"


using namespace std;
using namespace sf;

class Starter
{
public:
    Starter(Trainer* trainer);
    ~Starter();
	void draw(); 
    

private:
	void SetInterface(RenderWindow& window);
	string MoveCursor(string direction); 
	Sprite cursor;
	Texture texture;
	Texture* textureBackGround;
	RectangleShape backGroundRectangle;
	Trainer* trainer;
};