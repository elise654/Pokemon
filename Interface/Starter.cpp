#include "Starter.h"
#include "../DataDeposit/PokemonFinder.h"

Starter::Starter(Trainer* trainer)
{
	this->trainer = trainer;
}

Starter::~Starter()
{
}

void Starter::SetInterface(RenderWindow& window)
{
	this->textureBackGround = new Texture();
    this->textureBackGround->loadFromFile("Images/Menu_Starter.png");

    
    this->backGroundRectangle.setSize(sf::Vector2f(500,300));
    this->backGroundRectangle.setTexture(this->textureBackGround);

	this->texture.loadFromFile("Images/Starter_cursor.png");

	this->cursor.setTexture(texture);
	this->cursor.setPosition(20, 240);

	window.draw(this->backGroundRectangle);
	window.draw(this->cursor);
}

void Starter::draw()
{
	RenderWindow starterWindow(VideoMode(500, 300, 32), "TP3- Pokemon");
    starterWindow.setVerticalSyncEnabled(true);
    starterWindow.clear();
    SetInterface(starterWindow);
	starterWindow.display();
	string choicePokemon = "Squirtle";
    
    while (starterWindow.isOpen())
	{
		Event event;

		while (starterWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				      starterWindow.close();
				    break;
                case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						starterWindow.close();
					}
                    if (event.key.code == sf::Keyboard::Left)
					{
						choicePokemon = MoveCursor("Left");
						starterWindow.draw(backGroundRectangle);
						starterWindow.draw(cursor);
						starterWindow.display();
					}
                    if (event.key.code == sf::Keyboard::Right)
					{
                        choicePokemon = MoveCursor("Right");
						starterWindow.draw(backGroundRectangle);
						starterWindow.draw(cursor);
						starterWindow.display();
					}
                    if(event.key.code == sf::Keyboard::Space)
                    {
						//ADD POKEMON AND BEGIN GAME
						DataDeposit::PokemonFinder* starterFinder = new DataDeposit::PokemonFinder();
						starterFinder->ReadPokemonAvailable();
						vector<Pokemon*> starterList = starterFinder->getStarterPokemon();
						Pokemon* starterPokemon;
						for(vector<Pokemon*>::iterator it = starterList.begin(); it != starterList.end(); it++)
						{
							if((*it)->getName() == choicePokemon)
							{
								starterPokemon = *it;
								break;
							}
							
						}
						trainer->getParty()->AddPokemon(starterPokemon);
                        starterWindow.close();
                    }
			}
		}
    }
}


string Starter::MoveCursor(string direction)
{
	int x = this->cursor.getPosition().x;

	if (direction == "Right")
	{
		if (x == 20) //Squirtle
		{
			this->cursor.setPosition(160, 240);
			return "Bulbasaur";
		}
		else if (x == 160) //Bulbasaur
		{
			this->cursor.setPosition(300, 240);
			return "Charmander";
		}
		else //Charmander
		{
			this->cursor.setPosition(20, 240);
			return "Squirtle";
		}
	}
	else
	{
		if (x == 20) //Squirtle
		{
			this->cursor.setPosition(300, 240);
			return "Charmander";	
		}
		else if (x == 160) //Bulbasaur
		{
			this->cursor.setPosition(20, 240);
			return "Squirtle";
		}
		else //Charmander
		{
			this->cursor.setPosition(160, 240);
			return "Bulbasaur";
		}
	}
	
}