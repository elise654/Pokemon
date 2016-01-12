#include <iostream>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "../DataDeposit/SaveGame.h"
#include "../DataDeposit/LoadGame.h"
#include "../DataDeposit/PokemonFinder.h"
#include "CombatMenu.h"
#include "../Pokemon/Trainer.h"
#include <vld.h>


#define LARGEUR 500
#define HAUTEUR 600

//namespace SFML
using namespace sf;

//La fenêtre principale
RenderWindow mainWin(VideoMode(LARGEUR, HAUTEUR, 32), "TP3- Pokemon");


int main()
{
	//Synchonisation coordonnée à l'écran!
	mainWin.setVerticalSyncEnabled(true);


	

	Menu mainMenu;
	mainMenu.draw(mainWin);
	
		

	while (mainWin.isOpen())
	{
		Event event;
	

		while (mainWin.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					mainWin.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Down)
					{
						mainMenu.MoveCursor("Down", mainWin);
					}
					else if (event.key.code == sf::Keyboard::Up)
					{
						mainMenu.MoveCursor("Up", mainWin);
					}
					else if (event.key.code == sf::Keyboard::Space)
					{
						mainMenu.SelectItem(mainWin);
					}
					break;


			}
		}

	}

	

	return EXIT_SUCCESS;
}
