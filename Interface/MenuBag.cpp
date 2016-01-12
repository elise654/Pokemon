#include "MenuBag.h"
#include "../Pokemon/Fight.h"

MenuBag::MenuBag(Bag* theBag, Party* theParty, string origin, Pokemon* enemy, Trainer* trainer, RenderWindow& combatWin)
{
    font.loadFromFile("pkmnfl.ttf");
    bag = theBag;
	party = theParty;
    isItemSelected = false;
	isItemUsed = false;
	this->origin = origin;
	this->enemy = enemy;
	this->trainer = trainer;
	this->combatWin = &combatWin;
}

MenuBag::~MenuBag()
{

}

void MenuBag::SetInterface(RenderWindow* bagWindow)
{
    SetItems();
    Texture* textureBackGround = new Texture();
    textureBackGround->loadFromFile("Images/backGround_Bag.png");

    RectangleShape backGroundRectangle;
    backGroundRectangle.setSize(sf::Vector2f(500,500));
    backGroundRectangle.setTexture(textureBackGround);
    
    Texture* textureRectangle = new Texture();
    textureRectangle->loadFromFile("Images/rectangle_Bag.png");

	Texture* textureInfo = new Texture();
	textureInfo->loadFromFile("Images/rectangle_bag_info.png");
    
    
    RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300,300));
    rectangle.setPosition(200,0);
    rectangle.setTexture(textureRectangle);

	RectangleShape rectangleInfo;
    rectangleInfo.setSize(sf::Vector2f(500,300));
    rectangleInfo.setPosition(0,400);
    rectangleInfo.setTexture(textureInfo);

    Text textBag;
    textBag.setString("SAC");
    textBag.setFont(font);
    textBag.setColor(Color::Black);
    textBag.move(50,10);
    textBag.setCharacterSize(38);

    Texture textureBag;
    textureBag.loadFromFile("Images/Bag.PNG");
    Sprite spriteBag;
    spriteBag.setTexture(textureBag);
    spriteBag.setPosition(20,100);
    
    bagWindow->draw(backGroundRectangle);
    bagWindow->draw(rectangle);
	bagWindow->draw(rectangleInfo);
    bagWindow->draw(textBag);
    bagWindow->draw(spriteBag);

    bagWindow->draw(textPokeball);
    bagWindow->draw(textPotion);
    bagWindow->draw(textSuperPotion);
    bagWindow->draw(lines1);
    bagWindow->draw(lines2);
    bagWindow->draw(lines3);

	bagWindow->setMouseCursorVisible(false);

}

void MenuBag::SetItems()
{
    setItemsNumber(bag);
    //Pokeball
    textPokeball.setFont(font);
    textPokeball.setColor(Color::Black);
    textPokeball.setPosition(230,10);
    textPokeball.setCharacterSize(22);
    
    //potion
    textPotion.setFont(font);
    textPotion.setColor(Color::Black);
    textPotion.setPosition(230,45);
    textPotion.setCharacterSize(22);
    
    //super potion
    textSuperPotion.setFont(font);
    textSuperPotion.setColor(Color::Black);
    textSuperPotion.setPosition(230,80);
    textSuperPotion.setCharacterSize(22);

    lines1.setString("-----------------------------");
    lines1.setFont(font);
    lines1.setColor(Color::Black);
    lines1.setPosition(230,23);
    lines1.setCharacterSize(18);

    lines2.setString(lines1.getString());
    lines2.setFont(font);
    lines2.setColor(Color::Black);
    lines2.setPosition(230,58);
    lines2.setCharacterSize(18);

    lines3.setString(lines1.getString());
    lines3.setFont(font);
    lines3.setColor(Color::Black);
    lines3.setPosition(230,93);
    lines3.setCharacterSize(18);

    
}

void MenuBag::draw(RenderWindow& win)
{
    RenderWindow bagWindow(VideoMode(500, 500, 32), "Sac");
    bagWindow.setVerticalSyncEnabled(true);
    bagWindow.clear();
    SetInterface(&bagWindow);

    Texture texture;
    texture.loadFromFile("Images/cursor.png");
    cursor.setTexture(texture);
    	
    string item;

    captureImage = bagWindow.capture();
    captureTexture.loadFromImage(captureImage);
    captureSprite.setTexture(captureTexture);

    cursor.setPosition(210, 13);
	SetDescriptionItem(cursor,&bagWindow);

    bagWindow.draw(cursor);

    bagWindow.display(); 
    while (bagWindow.isOpen())
	{
		Event event;

		while (bagWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				    //bagWindow.close();
				    break;
                case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						bagWindow.close();
					}
                    if (event.key.code == sf::Keyboard::Up)
					{
						Sprite tempCursor;
						if(isItemSelected)
                        {
                            tempCursor = MoveSmallCursor("Up",cursor,smallCursor);
							smallCursor = tempCursor;
							bagWindow.clear();
							bagWindow.draw(captureSpriteMenu);
                        }
                        else
                        {
                            tempCursor = MoveCursor("Up", cursor);
							cursor = tempCursor;
							bagWindow.clear();
							bagWindow.draw(captureSprite);
                        }
						SetDescriptionItem(cursor,&bagWindow);
                        bagWindow.draw(tempCursor);
                        bagWindow.display();
					}
                    if (event.key.code == sf::Keyboard::Down)
					{
                        Sprite tempCursor;

						if(isItemSelected)
                        {
                            tempCursor = MoveSmallCursor("Down",cursor,smallCursor);
							smallCursor = tempCursor;
							bagWindow.clear();
							bagWindow.draw(captureSpriteMenu);
                        }
                        else
                        {
                            tempCursor = MoveCursor("Down",cursor);
							cursor = tempCursor;
							bagWindow.clear();
							bagWindow.draw(captureSprite);
                        }
							SetDescriptionItem(cursor,&bagWindow);
                            bagWindow.draw(tempCursor);
                            bagWindow.display();
						
					}
                    if(event.key.code == sf::Keyboard::Space)
                    {
						if(isItemUsed)
						{
							SelectPotionSmallCursor(&bagWindow, item);
							isItemUsed = false;
							isItemSelected = false;
						}
                        else if(isItemSelected)
                        {
                           bagWindow.clear();
                           if (SelectItemSmallCursor(&bagWindow) != "Retour")
						   {
							   if (item != "Pokeball")
							   {
								isItemUsed = true;
							   }
							   else
							   {
								   isItemSelected = false;
							   }
						   }
						   else
						   {
							   isItemSelected = false;
						   }
                        }
                        else
                        {
                            bagWindow.clear();
                            item = SelectItem(&bagWindow);
                            isItemSelected = true;
                        }
						SetDescriptionItem(cursor,&bagWindow);
						bagWindow.display();
                        
                    }
			}
		}
    }
}

void MenuBag::setItemsNumber(Bag* bag)
{
    pokeballCount = 0;
    potionCount = 0;
    superPotionCount = 0;

    for(int i = 0; i < bag->getItems().size(); i++)
    {
        if(bag->getItems()[i]->getHpRestore() == 0) 
        {
            pokeballCount++;
        }
        else if(bag->getItems()[i]->getHpRestore() == 20)
        {
            potionCount++;
        }
        else if(bag->getItems()[i]->getHpRestore() == 50)
        {
            superPotionCount++;
        }
    }
    textPokeball.setString("POKEBALL                         x   " + intToString(pokeballCount));
    textPotion.setString("POTION                             x   " + intToString(potionCount));
    textSuperPotion.setString("SUPER POTION                 x   " + intToString(superPotionCount));
}

string MenuBag::SelectItem(RenderWindow* window)
{
    int y = cursor.getPosition().y;
    int x = cursor.getPosition().x;
    string item;
    Texture* textureRectangle = new Texture();
    textureRectangle->loadFromFile("Images/rectangle_bag_select_item.png");
    RectangleShape rectangle;
    rectangle.setTexture(textureRectangle);
    rectangle.setSize(Vector2f(100,55));

    textureCursor.loadFromFile("Images/cursor_small.png");
    smallCursor.setTexture(textureCursor);

    Text textUse;
    textUse.setString("Utiliser");
    textUse.setCharacterSize(15);
    textUse.setColor(Color::Black);
    textUse.setFont(font);

    Text textDrop;
    textDrop.setString("Jeter");
    textDrop.setCharacterSize(15);
    textDrop.setColor(Color::Black);
    textDrop.setFont(font);

    Text textBack;
    textBack.setString("Retour");
    textBack.setCharacterSize(15);
    textBack.setColor(Color::Black);
    textBack.setFont(font);

    if(y == 13)
    {
        smallCursor.setPosition(115,18);
        textUse.setPosition(130,15);
        textDrop.setPosition(130,30);
        textBack.setPosition(130,45);
        rectangle.setPosition(115,15);
        item = "Pokeball";
    }
    else if(y == 48)
    {
        smallCursor.setPosition(115,53);
        textUse.setPosition(130,50);
        textDrop.setPosition(130,65);
        textBack.setPosition(130,80);
        rectangle.setPosition(115,50);
        item = "Potion";
    }
    else
    {
        smallCursor.setPosition(115,88);
        textUse.setPosition(130,85);
        textDrop.setPosition(130,100);
        textBack.setPosition(130,115);
        rectangle.setPosition(115,85);
        item = "Super potion";
    }
    SetInterface(window);

    window->draw(rectangle);
    window->draw(textUse);
    window->draw(textDrop);
    window->draw(textBack);
	captureImageMenu = window->capture();
    captureTextureMenu.loadFromImage(captureImageMenu);
    captureSpriteMenu.setTexture(captureTextureMenu);
    window->draw(smallCursor);

	return item;

}

string MenuBag::intToString(int number)
{
    std::ostringstream convert; 
    convert << number;      
    return convert.str();
}
Sprite MenuBag::MoveCursor(string direction, Sprite theCursor)
{
    int y = theCursor.getPosition().y;
    int x = theCursor.getPosition().x;

    if(direction == "Up")
    {
        if(y == 13)
        {
            theCursor.setPosition(x, 83);
        }
        else if(y == 48)
        {
            theCursor.setPosition(x, 13);
        }
        else //If position y == 83
        {
            theCursor.setPosition(x, 48);
        }
    }
    else
    {
        if(y == 13)
        {
            theCursor.setPosition(x, 48);
        }
        else if(y == 48)
        {
            theCursor.setPosition(x, 83);
        }
        else //If position y == 83
        {
            theCursor.setPosition(x, 13);
        }
    }

    return theCursor;
}


Sprite MenuBag::MoveSmallCursor(string direction, Sprite theCursor, Sprite smallCursor)
{
    int yCursor = theCursor.getPosition().y;
    int xCursor = theCursor.getPosition().x;
	int ySmallCursor = smallCursor.getPosition().y;
    int xSmallCursor = smallCursor.getPosition().x;

    if(direction == "Up")
    {
        if(yCursor == 13)
        {
			if(ySmallCursor == 18)
			{
				smallCursor.setPosition(xSmallCursor, 50);
			}
			else if(ySmallCursor == 35)
			{
				smallCursor.setPosition(xSmallCursor, 18);
			}
			else if(ySmallCursor == 50)
			{
				smallCursor.setPosition(xSmallCursor, 35);
			}
        }
        else if(yCursor == 48)
        {
			if(ySmallCursor == 53)
			{
				smallCursor.setPosition(xSmallCursor, 85);
			}
			else if(ySmallCursor == 70)
			{
				smallCursor.setPosition(xSmallCursor, 53);
			}
			else if(ySmallCursor == 85)
			{
				smallCursor.setPosition(xSmallCursor, 70);
			}
        }
        else //If position y == 83
        {
			if(ySmallCursor == 88)
			{
				smallCursor.setPosition(xSmallCursor, 120);
			}
			else if(ySmallCursor == 105)
			{
				smallCursor.setPosition(xSmallCursor, 88);
			}
			else if(ySmallCursor == 120)
			{
				smallCursor.setPosition(xSmallCursor, 105);
			}
        }
    }
    else
    {
        if(yCursor == 13)
        {
            if(ySmallCursor == 18)
			{
				smallCursor.setPosition(xSmallCursor, 35);
			}
			else if(ySmallCursor == 35)
			{
				smallCursor.setPosition(xSmallCursor, 50);
			}
			else if(ySmallCursor == 50)
			{
				smallCursor.setPosition(xSmallCursor, 18);
			}
        }
        else if(yCursor == 48)
        {
            if(ySmallCursor == 53)
			{
				smallCursor.setPosition(xSmallCursor, 70);
			}
			else if(ySmallCursor == 70)
			{
				smallCursor.setPosition(xSmallCursor, 85);
			}
			else if(ySmallCursor == 85)
			{
				smallCursor.setPosition(xSmallCursor, 53);
			}
        }
        else //If position y == 83
        {
            if(ySmallCursor == 88)
			{
				smallCursor.setPosition(xSmallCursor, 105);
			}
			else if(ySmallCursor == 105)
			{
				smallCursor.setPosition(xSmallCursor, 120);
			}
			else if(ySmallCursor == 120)
			{
				smallCursor.setPosition(xSmallCursor, 88);
			}
        }
    }

    return smallCursor;
}



string MenuBag::SelectItemSmallCursor(RenderWindow* window)
{
    int y = smallCursor.getPosition().y;
    int x = smallCursor.getPosition().x;
    string item;

    if (y == 50 || y == 85 || y == 120)
	{
		window->draw(captureSprite);
		window->draw(cursor);
		return "Retour";
	}
	else if (y == 18)
	{
		if (origin == "Menu")
		{
		Text textUsePokeball;
		textUsePokeball.setString("Vous ne pouvez pas utiliser de pokéball en ce moment.");
		textUsePokeball.setCharacterSize(20);
		textUsePokeball.setColor(Color::Black);
		textUsePokeball.setFont(font);
		textUsePokeball.setPosition(30, 375);
		window->draw(captureSprite);
		window->draw(cursor);
		window->draw(textUsePokeball);
		}
		else //À partir du combatMenu, utiliser une pokéball
		{
			int nbrItems = bag->getItems().size();
			int itPokeball = -1;
			for (int i = 0; i < nbrItems; i++)
			{
				if (bag->getItems().at(i)->getName() == "Pokeball")
				{
					itPokeball = i;
					break;
				}
			}
			if (itPokeball != -1)
			{
				SoftwareLogic::Fight fight;
				string message;
				message = fight.UseItem(enemy, bag->getItems().at(itPokeball), trainer);
				if (message != "Le pokmémon n'a pas été capturé.")
				{
					Text textUsePokeball;
					textUsePokeball.setString(message);
					textUsePokeball.setCharacterSize(20);
					textUsePokeball.setColor(Color::Black);
					textUsePokeball.setFont(font);
					textUsePokeball.setPosition(30, 375);

					window->clear();
					SetInterface(window);

					captureImage = window->capture();
					captureTexture.loadFromImage(captureImage);
					captureSprite.setTexture(captureTexture);

					window->draw(captureSprite);
					window->draw(cursor);
					window->draw(textUsePokeball);
					window->display();
					Wait();
					window->close();
					combatWin->close();
				}
				else
				{
				Text textUsePokeball;
				textUsePokeball.setString(message);
				textUsePokeball.setCharacterSize(20);
				textUsePokeball.setColor(Color::Black);
				textUsePokeball.setFont(font);
				textUsePokeball.setPosition(30, 375);

				window->clear();
				SetInterface(window);

				captureImage = window->capture();
				captureTexture.loadFromImage(captureImage);
				captureSprite.setTexture(captureTexture);

				window->draw(captureSprite);
				window->draw(cursor);
				window->draw(textUsePokeball);
				window->display();
				Wait();
				window->close();
				}
			}
			else
			{
				Text textPokeball;
				textPokeball.setString("Vous n'avez pas de pokéball.");
				textPokeball.setCharacterSize(20);
				textPokeball.setColor(Color::Black);
				textPokeball.setFont(font);
				textPokeball.setPosition(30, 375);
				window->draw(captureSprite);
				window->draw(cursor);
				window->draw(textPokeball);
			}
			
		}
		return "Test";
	}
	else if (y == 35)
	{
		if(pokeballCount == 0)
		{
			Text textPokeball;
			textPokeball.setString("Vous n'avez pas de pokéball.");
			textPokeball.setCharacterSize(20);
			textPokeball.setColor(Color::Black);
			textPokeball.setFont(font);
			textPokeball.setPosition(30, 375);
			window->draw(captureSprite);
			window->draw(cursor);
			window->draw(textPokeball);
		}
		else
		{

			//JETER POKEBALL 
			ThrowItem(window, "Pokeball");
		}
		return "Test";
	}
	else if (y == 53)
	{
		if(potionCount == 0)
		{
			Text textPokeball;
			textPokeball.setString("Vous n'avez pas de potion.");
			textPokeball.setCharacterSize(20);
			textPokeball.setColor(Color::Black);
			textPokeball.setFont(font);
			textPokeball.setPosition(30, 375);
			window->draw(captureSprite);
			window->draw(cursor);
			window->draw(textPokeball);
		}
		else
		{
		//UTILISER POTION
			usePotion(window);
		}
		return "Test";
	}
	else if (y == 70)
	{
		if(potionCount == 0)
		{
			Text textPokeball;
			textPokeball.setString("Vous n'avez pas de potion.");
			textPokeball.setCharacterSize(20);
			textPokeball.setColor(Color::Black);
			textPokeball.setFont(font);
			textPokeball.setPosition(30, 375);
			window->draw(captureSprite);
			window->draw(cursor);
			window->draw(textPokeball);
		}
		else
		{
			
			//JETER POTION
			ThrowItem(window, "Potion");
		}
		return "Test";
	}
	else if (y == 88)
	{
		if(superPotionCount == 0)
		{
			Text textPokeball;
			textPokeball.setString("Vous n'avez pas de super potion.");
			textPokeball.setCharacterSize(20);
			textPokeball.setColor(Color::Black);
			textPokeball.setFont(font);
			textPokeball.setPosition(30, 375);
			window->draw(captureSprite);
			window->draw(cursor);
			window->draw(textPokeball);
		}
		else
		{
			//UTILISER SUPERPOTION
			usePotion(window);
			
		}
		return "Test";
	}
	else if (y == 105)
	{
		if(superPotionCount == 0)
		{
			Text textPokeball;
			textPokeball.setString("Vous n'avez pas de super potion.");
			textPokeball.setCharacterSize(20);
			textPokeball.setColor(Color::Black);
			textPokeball.setFont(font);
			textPokeball.setPosition(30, 375);
			window->draw(captureSprite);
			window->draw(cursor);
			window->draw(textPokeball);
		}
		else
		{

			//JETER SUPERPOTION
			ThrowItem(window, "Super potion");
		}
		return "Test";
	}
	
   
}


void MenuBag::SetDescriptionItem(Sprite cursor, RenderWindow* window)
{
	int yCursor = cursor.getPosition().y;

	if (yCursor == 13)
	{
		Text textInfoPokeball;
		textInfoPokeball.setString("Un objet qui permet d'attraper les \npokémons sauvages.");
		textInfoPokeball.setCharacterSize(20);
		textInfoPokeball.setColor(Color::White);
		textInfoPokeball.setFont(font);
		textInfoPokeball.setPosition(115, 400);
		window->draw(textInfoPokeball);

		
		Texture* texturePokeball = new Texture();
		texturePokeball->loadFromFile("Images/Item_pokeball.png");
		RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(50,50));
		rectangle.setPosition(25,425);
		rectangle.setTexture(texturePokeball);
		window->draw(rectangle);

	}
	else if (yCursor == 48)
	{
		Text textInfoPotion;
		textInfoPotion.setString("Restaure les PV d'un pokémon de 20 points.");
		textInfoPotion.setCharacterSize(20);
		textInfoPotion.setColor(Color::White);
		textInfoPotion.setFont(font);
		textInfoPotion.setPosition(115, 400);
		window->draw(textInfoPotion);

		Texture* texturePotion = new Texture();
		texturePotion->loadFromFile("Images/Item_potion.png");
		RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(50,50));
		rectangle.setPosition(25,425);
		rectangle.setTexture(texturePotion);
		window->draw(rectangle);
	}
	else //yCursor == 83
	{
		Text textInfoSuperPotion;
		textInfoSuperPotion.setString("Restaure les PV d'un pokémon de 50 points.");
		textInfoSuperPotion.setCharacterSize(20);
		textInfoSuperPotion.setColor(Color::White);
		textInfoSuperPotion.setFont(font);
		textInfoSuperPotion.setPosition(115, 400);
		window->draw(textInfoSuperPotion);

		Texture* textureSuperPotion = new Texture();
		textureSuperPotion->loadFromFile("Images/Item_superPotion.png");
		RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(50,50));
		rectangle.setPosition(25,425);
		rectangle.setTexture(textureSuperPotion);
		window->draw(rectangle);
	}
}



void MenuBag::usePotion(RenderWindow* window)
{
	int y = cursor.getPosition().y;
    int x = cursor.getPosition().x;
	int nbrPokemon = party->getPokemons().size();
    
    Texture* textureRectangle = new Texture();
    textureRectangle->loadFromFile("Images/rectangle_bag_select_item.png");
    RectangleShape rectangle;
    rectangle.setTexture(textureRectangle);
    rectangle.setSize(Vector2f(100,100));

    textureCursor.loadFromFile("Images/cursor_small.png");
    smallCursorPotion.setTexture(textureCursor);

   int positionText = 0;
    
    if(y == 48) //POTION
    {
        smallCursorPotion.setPosition(120,115);
        rectangle.setPosition(115,110);
		positionText = 115;
    }
    else //SUPER POTION
    {
        smallCursorPotion.setPosition(120,163);
        rectangle.setPosition(115,158);
		positionText = 165;
    }

	
	SetInterface(window);

	window->draw(captureSpriteMenu);
	window->draw(rectangle);
    window->draw(smallCursorPotion);

	
	for (int i = 0; i < nbrPokemon; i++)
	{
		Text textPokemon;
		textPokemon.setString(party->getPokemons().at(i)->getName());
		textPokemon.setCharacterSize(15);
		textPokemon.setColor(Color::Black);
		textPokemon.setFont(font);
		textPokemon.setPosition(130, positionText);
		window->draw(textPokemon);
		positionText = positionText + 5;
	}


}




void MenuBag::SelectPotionSmallCursor(RenderWindow* bagWindow, string item)
{
	int y = smallCursorPotion.getPosition().y;
    int x = smallCursorPotion.getPosition().x;
	int nbrPokemon = party->getPokemons().size();
	int nbrItems = bag->getItems().size();
	int itPotion = 0;

	for (int i = 0; i < nbrItems; i++)
	{
		if (bag->getItems().at(i)->getName() == item)
		{
			itPotion = i;
			break;
		}
	}

	if (y == 115 && nbrPokemon >= 1)
	{
		//USE POSTION
		bag->UsePotion(party->getPokemons().at(0), bag->getItems().at(itPotion));
	}
	else if (y == 120 && nbrPokemon >= 2)
	{
		//USE POSTION
		bag->UsePotion(party->getPokemons().at(1), bag->getItems().at(itPotion));
	}
	else if (y == 125 && nbrPokemon >= 3)
	{
		//USE POSTION
		bag->UsePotion(party->getPokemons().at(2), bag->getItems().at(itPotion));
	}
	else if (y == 130 && nbrPokemon >= 4)
	{
		//USE POSTION
		bag->UsePotion(party->getPokemons().at(3), bag->getItems().at(itPotion));
	}
	else if (y == 135 && nbrPokemon >= 5)
	{
		//USE POSTION
		bag->UsePotion(party->getPokemons().at(4), bag->getItems().at(itPotion));
	}
	else if (y == 163 && nbrPokemon >= 1)
	{
		bag->UsePotion(party->getPokemons().at(0), bag->getItems().at(itPotion));
	}
	else if (y == 168 && nbrPokemon >= 2)
	{
		bag->UsePotion(party->getPokemons().at(1), bag->getItems().at(itPotion));
	}
	else if (y == 173 && nbrPokemon >= 3)
	{
		bag->UsePotion(party->getPokemons().at(2), bag->getItems().at(itPotion));
	}
	else if (y == 178 && nbrPokemon >= 4)
	{
		bag->UsePotion(party->getPokemons().at(3), bag->getItems().at(itPotion));
	}
	else if (y == 183 && nbrPokemon >= 5)
	{
		bag->UsePotion(party->getPokemons().at(4), bag->getItems().at(itPotion));
	}

	bagWindow->clear();
    SetInterface(bagWindow);

    captureImage = bagWindow->capture();
    captureTexture.loadFromImage(captureImage);
    captureSprite.setTexture(captureTexture);
	bagWindow->draw(captureSprite);
	bagWindow->draw(textPokeball);
    bagWindow->draw(textPotion);
    bagWindow->draw(textSuperPotion);
	bagWindow->draw(cursor);
	
	Text textUsePotion;
	textUsePotion.setString("Vous avez utilisé votre " + item + ".");
	textUsePotion.setCharacterSize(15);
	textUsePotion.setColor(Color::Black);
	textUsePotion.setFont(font);
	textUsePotion.setPosition(30, 375);
	bagWindow->draw(textUsePotion);
}

void MenuBag::ThrowItem(RenderWindow* bagWindow, string item)
{
	int nbrItems = bag->getItems().size();
	int itItem = 0;

	for (int i = 0; i < nbrItems; i++)
	{
		if (bag->getItems().at(i)->getName() == item)
		{
			itItem = i;
			break;
		}
	}

	bag->RemoveItem(bag->getItems().at(itItem));

	bagWindow->clear();
    SetInterface(bagWindow);

    captureImage = bagWindow->capture();
    captureTexture.loadFromImage(captureImage);
    captureSprite.setTexture(captureTexture);

	Text textThrowItem;
	textThrowItem.setString("Vous avez jeter cet item.");
	textThrowItem.setCharacterSize(20);
	textThrowItem.setColor(Color::Black);
	textThrowItem.setFont(font);
	textThrowItem.setPosition(30, 375);

	bagWindow->draw(captureSprite);
	bagWindow->draw(cursor);
	bagWindow->draw(textThrowItem);
}

void MenuBag::Wait()
{
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();
    while(time < 2)
    {
        time = clock.getElapsedTime().asSeconds();
    }
}