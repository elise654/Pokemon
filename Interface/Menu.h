#include "SFML/Graphics.hpp"
#include <list>
#include "../Pokemon/Trainer.h"

using namespace std;
using namespace sf;


class Menu
{
public:
    Menu();
    ~Menu();
    
    void draw(RenderWindow& win);
	void MoveCursor(string direction, RenderWindow& window); 
	void SelectItem(RenderWindow& window);

private:
	bool wildEncounter(Trainer* trainer);
    void SetInterface(RenderWindow& window);
	Sprite cursor;
	Texture texture;
	Sprite sprite;
	Texture image;
	void loadMap(int x, int y);
	Trainer* trainer ;

	
	
};
