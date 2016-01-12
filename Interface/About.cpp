#include "About.h"

About::About()
{
}

About::~About()
{
}

void About::Show(sf::RenderWindow& window)
{
	RenderWindow windowAbout(sf::VideoMode(800, 800), "À propos");


	sf::Font font;
	font.loadFromFile("pkmnfl.ttf");


	sf::Text textTitle;
	textTitle.setFont(font);
	textTitle.setString("À propos");
	textTitle.setCharacterSize(70);
	textTitle.setColor(sf::Color::Red);
	textTitle.setPosition(280, 50);

	sf::Text text1;
	text1.setFont(font);
	text1.setString("Réalisé par Élise Carbonneau-Leclerc");
	text1.setCharacterSize(45);
	text1.setColor(sf::Color::Red);
	text1.setPosition(50, 200);

	sf::Text text2;
	text2.setFont(font);
	text2.setString("Pierre Marion et Pierre-Antoine Morin");
	text2.setCharacterSize(45);
	text2.setColor(sf::Color::Red);
	text2.setPosition(50, 250);

	sf::Text text3;
	text3.setFont(font);
	text3.setString("Programmation d'application hiver 2014");
	text3.setCharacterSize(45);
	text3.setColor(sf::Color::Red);
	text3.setPosition(50, 300);


	windowAbout.setVerticalSyncEnabled(true);

	while (windowAbout.isOpen())
	{
		Event event;

		while (windowAbout.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				windowAbout.close();
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						windowAbout.close();
					}
				
				
				break;
			}
		}

		windowAbout.clear(Color::White);
		windowAbout.draw(textTitle);
		windowAbout.draw(text1);
		windowAbout.draw(text2);
		windowAbout.draw(text3);
		windowAbout.display();

	}


	
}




