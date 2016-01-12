#include "MenuOption.h"
#include "MenuBag.h"
#include "../Pokemon/Bag.h"
#include "PartyMenu.h"
#include "../Pokemon/Potion.h"
#include "../DataDeposit/SaveGame.h"



MenuOption::MenuOption(Sound &sound, Trainer* trainer, Interface::Player &player)
{
    font.loadFromFile("pkmnfl.ttf");
	this->music = &sound;
	this->trainer = trainer;
	this->player = &player;
}

MenuOption::~MenuOption()
{

}

void MenuOption::SetInterface(RenderWindow& optionWindow)
{
    textureBackGround.loadFromFile("Images/MenuOption.png");

    RectangleShape backGroundRectangle;
    backGroundRectangle.setSize(sf::Vector2f(160,255));
    backGroundRectangle.setTexture(&textureBackGround);


    Text textSave;
    textSave.setString("Sauvegarder");
    textSave.setFont(font);
    textSave.setColor(Color::Black);
    textSave.setPosition(23,12);
    textSave.setCharacterSize(22);

	Text textBag;
    textBag.setString("Sac");
    textBag.setFont(font);
    textBag.setColor(Color::Black);
    textBag.setPosition(23,42);
    textBag.setCharacterSize(22);

	Text textParty;
    textParty.setString("Pokémon");
    textParty.setFont(font);
    textParty.setColor(Color::Black);
    textParty.setPosition(23,72);
    textParty.setCharacterSize(22);

	Text textOption;
    textOption.setString("Son on/off");
    textOption.setFont(font);
    textOption.setColor(Color::Black);
    textOption.setPosition(23,102);
    textOption.setCharacterSize(22);

	Text textBack;
    textBack.setString("Retour");
    textBack.setFont(font);
    textBack.setColor(Color::Black);
    textBack.setPosition(23,132);
    textBack.setCharacterSize(22);

	
	
    texture.loadFromFile("Images/cursor_small.png");
    smallCursor.setTexture(texture);
	smallCursor.setPosition(15, 21);
	
    
    optionWindow.draw(backGroundRectangle);
    optionWindow.draw(textSave);
	optionWindow.draw(textBack);
	optionWindow.draw(textOption);
	optionWindow.draw(textBag);
	optionWindow.draw(textParty);

	captureImage = optionWindow.capture();
    captureTexture.loadFromImage(captureImage);
    captureSprite.setTexture(captureTexture);

	optionWindow.draw(smallCursor);

}



void MenuOption::draw(RenderWindow& win)
{
	RenderWindow optionWindow(VideoMode(160, 255, 32), "Option");
    optionWindow.setVerticalSyncEnabled(true);
	optionWindow.setMouseCursorVisible(false);
	SetInterface(optionWindow);

	
    optionWindow.display();   
    
    while (optionWindow.isOpen())
	{
		Event event;

		while (optionWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				    //optionWindow.close();
				    break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						optionWindow.close();
					}
                    if (event.key.code == sf::Keyboard::Up)
					{
						
                            Sprite tempCursor = MoveCursor("Up", smallCursor);
                            optionWindow.clear();
                            optionWindow.draw(captureSprite);
                            optionWindow.draw(tempCursor);
							smallCursor = tempCursor;
                            optionWindow.display();
                        
					}
                    if (event.key.code == sf::Keyboard::Down)
					{
                        Sprite tempCursor;

                       
                            tempCursor = MoveCursor("Down",smallCursor);
                        
                            optionWindow.clear();
                            optionWindow.draw(captureSprite);
                            optionWindow.draw(tempCursor);
							smallCursor = tempCursor;
                            optionWindow.display();
						
					}
                    if(event.key.code == sf::Keyboard::Space)
                    {
                            string result = SelectItem();
							if (result == "Retour")
							{
								optionWindow.close();
							}
							else if (result == "Sauvegarder")
							{
								string name = "test";
								DataDeposit::SaveGame save(name, player->getX(), player->getY(), trainer->getParty()->getPokemons(), trainer->getBag()->getItems(), trainer->getPC(), trainer->getPokedex(), trainer->getBag()->getMoney());
								save.WriteXML();
								optionWindow.close();
							}
							else if (result == "Sac")
							{
								MenuBag menuBag(trainer->getBag(), trainer->getParty(), "Menu", NULL, trainer, win);
								menuBag.draw(win);
							}
							else if (result == "Pokemon")
							{
								PartyMenu* partyMenu = new PartyMenu(trainer->getParty());
								partyMenu->Draw();
							}
							else //option
							{
								if (music->getStatus() == Sound::Status::Playing)
								{
									music->stop();
								}
								else if (music->getStatus() == Sound::Status::Stopped)
								{
									music->play();
								}
							}
                            
                        
                        
                    }
			}
		}

         
    }
    
}


Sprite MenuOption::MoveCursor(string direction, Sprite theCursor)
{
    int y = theCursor.getPosition().y;
    int x = theCursor.getPosition().x;

    if(direction == "Up")
    {
        if(y == 21)
        {
            theCursor.setPosition(x, 141);
        }
        else if(y == 51)
        {
            theCursor.setPosition(x, 21);
        }
		else if(y == 81)
		{
			theCursor.setPosition(x,51);
		}
		else if(y == 111)
		{
			theCursor.setPosition(x,81);
		}
        else //If position y == 141
        {
            theCursor.setPosition(x, 111);
        }
    }
    else
    {
        if(y == 21)
        {
            theCursor.setPosition(x, 51);
        }
        else if(y == 51)
        {
            theCursor.setPosition(x, 81);
        }
		else if(y == 81)
        {
            theCursor.setPosition(x, 111);
        }
		else if(y == 111)
        {
            theCursor.setPosition(x, 141);
        }
        else //If position y == 141
        {
            theCursor.setPosition(x, 21);
        }
    }
    return theCursor;
}


string MenuOption::SelectItem()
{
    int y = smallCursor.getPosition().y;
    int x = smallCursor.getPosition().x;
   

    if(y == 21)
    {
        return "Sauvegarder";
    }
    else if(y == 51)
    {
        return "Sac";
    }
    else if(y == 81)
    {
        return "Pokemon";
    }
	else if(y == 111)
    {
        return "Option";
    }
	else //if(y == 141)
    {
        return "Retour";
    }
	
   
}



