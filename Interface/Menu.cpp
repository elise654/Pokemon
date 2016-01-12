#include "Menu.h"
#include "About.h"
#include "Map.h"
#include "Player.h"
#include "../Pokemon/Trainer.h"
#include "MenuOption.h"
#include "CombatMenu.h"
#include "../Pokemon/Potion.h"
#include <SFML/Audio.hpp>
#include "Starter.h"
#include "../Pokemon/Party.h"
#include "../DataDeposit/PokemonFinder.h"
#include "../DataDeposit/LoadGame.h"
#include "PokeMartMenu.h"

Menu::Menu()
{
}

Menu::~Menu()
{

}

void Menu::draw(RenderWindow& window)
{
	SetInterface(window);
	window.display();
}


void Menu::MoveCursor(string direction, RenderWindow& window)
{
	int y = cursor.getPosition().y;

	if (direction == "Up")
	{
		if (y == 260)
		{
			cursor.setPosition(65, 455);
		}
		else if (y == 345)
		{
			cursor.setPosition(65, 260);
		}
		else if (y == 455)
		{
			cursor.setPosition(65, 345);
		}
	}
	else
	{
		if (y == 260)
		{
			cursor.setPosition(65, 345);
		}
		else if (y == 345)
		{
			cursor.setPosition(65, 455);
		}
		else if (y == 455)
		{
			cursor.setPosition(65, 260);
		}
	}
	window.clear();
	window.draw(sprite);
	window.draw(cursor);
	window.display();
}

void Menu::SelectItem(RenderWindow& window)
{
	int y = cursor.getPosition().y;

	if (y == 260)
	{
		//CONTINUE
		DataDeposit::LoadGame load;
		load.ReadElements();
		trainer = new Trainer();
		vector<Pokemon*> loadPokemon = load.getPokemon();
		for(vector<Pokemon*>::iterator it = loadPokemon.begin(); it != loadPokemon.end(); it++)
		{
			trainer->setPokemonToParty((*it));
		}

		vector<Item*> loadItem = load.getItem();
		for(vector<Item*>::iterator it = loadItem.begin(); it != loadItem.end(); it++)
		{
			trainer->getBag()->AddItem((*it));
		}
		trainer->getBag()->AddMoney(load.getMoney());
		loadMap(load.getPositionX(), load.getPositionY());
	}
	else if (y == 345)
	{
		//NEW GAME
		trainer = new Trainer();

		window.close();
		Starter starterMenu(trainer);
		starterMenu.draw();
		trainer->getBag()->AddMoney(500);
		loadMap(0,0);
		
	}
	else if (y == 455)
	{
		//ABOUT
		About aboutWin;
		aboutWin.Show(window);
	}

}

void Menu::SetInterface(RenderWindow& window)
{
	image.loadFromFile("Images/MenuAccueil.png");
	sprite.setTexture(image);

	texture.loadFromFile("Images/Menu_cursor.png");

	cursor.setTexture(texture);
	cursor.setPosition(65, 260);

	window.draw(sprite);
	window.draw(cursor);	
}


void Heal(RenderWindow* window, Trainer* trainer, Sprite sprite, Interface::Player* player)
{
    for(int i = 0; i< trainer->getParty()->getPokemons().size(); i++)
    {
        if(trainer->getParty()->getPokemons()[i] != NULL)
        {
            trainer->getParty()->getPokemons()[i]->setCurrentHealth(trainer->getParty()->getPokemons()[i]->getFullHealth());
            trainer->getParty()->getPokemons()[i]->setDead(false);
        }
    }
    Font font;
    font.loadFromFile("pkmnfl.ttf");
    
    Text textPokemonHealed;
    textPokemonHealed.setString("Vos Pokemon ont tous été guérit!");
    textPokemonHealed.setCharacterSize(40);
    textPokemonHealed.setColor(Color::Red);
    textPokemonHealed.setPosition(150,200);
    textPokemonHealed.setFont(font);
    window->draw(sprite);
    window->draw(textPokemonHealed);
    window->display();
    Clock clock;
    clock.restart();
    float time = clock.getElapsedTime().asSeconds();
    while(time < 2)
    {
        time = clock.getElapsedTime().asSeconds();
    }
    player->setX(60);
    player->setY(324);
}


void Menu::loadMap(int x, int y)
{
	RenderWindow mainWin(VideoMode(800, 800, 32), "TP3- Pokemon");
	
	sf::SoundBuffer buffer;
	buffer.loadFromFile("ThemeSong.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setLoop(true);
	

	sf::Clock clock;
	
	Interface::Player player(clock);
	player.initialize(x,y);
	player.loadContent();

	Map map;
        
    map.GenerateMap("ASF");

    for(int i = 0; i< map.getTiles().size(); i++)
    {
        mainWin.draw(*map.getTiles()[i]);
    }
    sf::Image mapImage = mainWin.capture();
    sf::Texture texture;
    texture.loadFromImage(mapImage);
    sf::Sprite sprite;
    sprite.setTexture(texture);
	sound.play();
	mainWin.draw(sprite);

	float framerate = 1 / (clock.getElapsedTime().asMilliseconds() * 0.001);

	player.update(mainWin, "no direction", framerate, map);
	player.draw(mainWin);

	

	while (mainWin.isOpen())
	{
		Event event;
		mainWin.draw(sprite);
        

        Potion* item1 = new Potion("pokeball",100,0.75);

        Bag* bag = new Bag();
        bag->AddItem(item1);

		float framerate = 1 / (clock.getElapsedTime().asMilliseconds() * 0.001);

		player.update(mainWin, "no direction", framerate, map);
		player.draw(mainWin);
		mainWin.display();

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
						player.update(mainWin, "Down", framerate, map);

                        if(map.IsTileBush(player.getX(), player.getY()))
                        {
                            if(wildEncounter(trainer))
                            {
                                Heal(&mainWin,trainer,sprite,&player);
                            }
                        }
						
					}
					else if (event.key.code == sf::Keyboard::Up)
					{
						player.update(mainWin, "Up", framerate, map);

						if(map.IsTileBush(player.getX(), player.getY()))
                        {
                            if(wildEncounter(trainer))
                            {
                                Heal(&mainWin,trainer,sprite,&player);
                            }

                        }
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						player.update(mainWin, "Right", framerate, map);

						if(map.IsTileBush(player.getX(), player.getY()))
                        {
                            if(wildEncounter(trainer))
                            {
                                Heal(&mainWin,trainer,sprite,&player);
                            }
                        }
					}
					else if (event.key.code == sf::Keyboard::Left)
					{
						player.update(mainWin, "Left", framerate, map);

						if(map.IsTileBush(player.getX(), player.getY()))
                        {
                            if(wildEncounter(trainer))
                            {
                                Heal(&mainWin,trainer,sprite,&player);
                            }
                        }
					}
					else if (event.key.code == sf::Keyboard::N)
					{
						MenuOption* menuOption = new MenuOption(sound, trainer, player);
						menuOption->draw(mainWin);
					}
                    else if (event.key.code == sf::Keyboard::Space)
                    {                        
                        if(map.IsTileCenter(player.getX(),player.getY()))
                        {
                            Heal(&mainWin,trainer,sprite,&player);
                        }
                        else if(map.IsTileMart(player.getX(),player.getY()))
                        {
                            PokeMartMenu pokemartMenu(trainer);
                            pokemartMenu.Draw();
                        }
                    }
					break;
			}
		}
	
	}
}
bool Menu::wildEncounter(Trainer* trainer)
{
	int randomEncounter = rand() %100 + 1;

    bool allDead = false;

	if(randomEncounter <= 35)
	{
		srand ( time(NULL) );
		int pokemonRandomizer = rand() %100 +1;
		DataDeposit::PokemonFinder* wildFinder = new DataDeposit::PokemonFinder();
		wildFinder->ReadPokemonAvailable();
		vector<Pokemon*> wildList = wildFinder->getWildPokemon();
		Pokemon* enemy;
		bool isFound = false;
		for(vector<Pokemon*>::iterator it = wildList.begin(); it != wildList.end() && isFound == false; it++)
		{
			if(pokemonRandomizer <= 20)
			{
				if((*it)->getName() == "Pikachu")
				{
					enemy = *it;
					isFound == true;
				}
			}
			else if(pokemonRandomizer > 60)
			{
				if((*it)->getName() == "Pidgey")
				{
					enemy = *it;
					isFound == true;
				}
			}
			else
			{
				if((*it)->getName() == "Rattata")
				{
					enemy = *it;
					isFound == true;
				}
			}
		}
		CombatMenu wildBattle(trainer, enemy);
		wildBattle.draw();
        allDead = true;
        for(int i = 0; i < trainer->getParty()->getPokemons().size(); i++)
        {
            if(!(trainer->getParty()->getPokemons()[i]->isDead()))
            {
                allDead = false;
            }
        }
	}

	return allDead;
}




