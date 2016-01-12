#include "PartyMenu.h"

PartyMenu::PartyMenu(Party* theParty)
{
    party = theParty;
    changeUnavailable = false;
    isOrderChanging = false;
    isPokemonSelected = false;

    pokemonSelected = NULL;
    pokemonToChange = NULL;
    
    textureCursor.loadFromFile("Images/cursor.png");
    cursor.setTexture(textureCursor);
    cursor.setPosition(5,110);

    textureSmallCursor.loadFromFile("Images/cursor_small.png");
    smallCursor.setTexture(textureSmallCursor);
    smallCursor.setPosition(5,110);

    partySize = party->getPokemons().size();

    font.loadFromFile("pkmnfl.ttf");
}

PartyMenu::~PartyMenu()
{

}

void PartyMenu::Initialize(RenderWindow* window)
{
    window->clear();
    SetRectangles(window);
    SetPokemons(window);

    captureImage = window->capture();
    captureTexture.loadFromImage(captureImage);
    capture.setTexture(captureTexture);

    window->draw(cursor);

    window->display();
}

void PartyMenu::Draw()
{
    RenderWindow partyWindow(VideoMode(500, 400, 32), "Pokemon");
    partyWindow.setVerticalSyncEnabled(true);

    Initialize(&partyWindow);

   while (partyWindow.isOpen())
	{
		Event event;
        
		while (partyWindow.pollEvent(event))
		{
            switch (event.type)
			{
				case sf::Event::Closed:
				    partyWindow.close();
				    break;
                case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						partyWindow.close();
					}
                    else if (event.key.code == sf::Keyboard::Up)
					{
                        if(isOrderChanging)
                        {
                            MoveCursorWhileOrderChanging("Up");
                            partyWindow.clear();
                            partyWindow.draw(capture);
                            partyWindow.draw(smallCursor);
                            partyWindow.display();
                        }
						else if(isPokemonSelected)
                        {
                            MoveSmallCursor("Up");
                            partyWindow.clear();
                            partyWindow.draw(capture);
                            partyWindow.draw(smallCursor);
                            partyWindow.display();
                        }
                        else
                        {
                            MoveCursor("Up");
                            partyWindow.clear();
                            partyWindow.draw(capture);
                            partyWindow.draw(cursor);
                            partyWindow.display();
                        }
					}
                    else if (event.key.code == sf::Keyboard::Down)
					{
                        if(isOrderChanging)
                        {
                            MoveCursorWhileOrderChanging("Down");
                            partyWindow.clear();
                            partyWindow.draw(capture);
                            partyWindow.draw(smallCursor);
                            partyWindow.display();
                        }
						else if(isPokemonSelected)
                        {
                            partyWindow.clear();
                            MoveSmallCursor("Down");
                            partyWindow.draw(capture);
                            partyWindow.draw(smallCursor);
                            partyWindow.display();
                        }
                        else
                        {
                            MoveCursor("Down");
                            partyWindow.clear();
                            partyWindow.draw(capture);
                            partyWindow.draw(cursor);
                            partyWindow.display();
                        }
					}
                    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
					{
						if(!isPokemonSelected)
                        {
                            MoveCursor("Right");
                            partyWindow.clear();
                            partyWindow.draw(capture);
                            partyWindow.draw(cursor);
                            partyWindow.display();
                        }
					}
                    else if (event.key.code == sf::Keyboard::Space)
					{
                        if(isOrderChanging)
                        {
                            partyWindow.clear();
                            ChangeOrder(&partyWindow);
                            partyWindow.draw(capture);
                            partyWindow.draw(cursor);
                            partyWindow.display();
                        }
                        if(isPokemonSelected)
                        {
                            partyWindow.clear();
                            bool actionSelected =  SelectAction(&partyWindow);
                            partyWindow.draw(capture);
                            if(actionSelected)
                                partyWindow.draw(smallCursor);                            
                            else
                                partyWindow.draw(cursor);
                            partyWindow.display();
                        }
                        else
                        {
                            partyWindow.clear();
                            SelectPokemon(&partyWindow);
                            partyWindow.draw(capture);
                            partyWindow.draw(smallCursor);
                            partyWindow.display();
                        }
                    }
            }
        }
    }

}

void PartyMenu::SetRectangles(RenderWindow* window)
{
    Texture textureBackGround;
    textureBackGround.loadFromFile("Images/backGround_Bag.png");

    Texture textureRectangleMainPokmeon;
    textureRectangleMainPokmeon.loadFromFile("Images/Rectangle_party_mainPokemon.png");

    Texture textureRectangleSecondaryPokemon;
    textureRectangleSecondaryPokemon.loadFromFile("Images/Rectangle_party_secondaryPokemon.png");

    Texture textureRectangleLeave;
    textureRectangleLeave.loadFromFile("Images/party_Leave.png");

    Sprite backGround;
    backGround.setTexture(textureBackGround);
    
    Sprite rectangleMainPokemon;
    rectangleMainPokemon.setTexture(textureRectangleMainPokmeon);
    rectangleMainPokemon.setPosition(10, 100);

    Sprite rectangleSecondaryPokemon1;
    rectangleSecondaryPokemon1.setTexture(textureRectangleSecondaryPokemon);
    rectangleSecondaryPokemon1.setPosition(250, 50);

    Sprite rectangleSecondaryPokemon2;
    rectangleSecondaryPokemon2.setTexture(textureRectangleSecondaryPokemon);
    rectangleSecondaryPokemon2.setPosition(250, 110);

    Sprite rectangleSecondaryPokemon3;
    rectangleSecondaryPokemon3.setTexture(textureRectangleSecondaryPokemon);
    rectangleSecondaryPokemon3.setPosition(250, 170);

    Sprite rectangleSecondaryPokemon4;
    rectangleSecondaryPokemon4.setTexture(textureRectangleSecondaryPokemon);
    rectangleSecondaryPokemon4.setPosition(250, 230);

    Sprite rectangleSecondaryPokemon5;
    rectangleSecondaryPokemon5.setTexture(textureRectangleSecondaryPokemon);
    rectangleSecondaryPokemon5.setPosition(250, 290);

    Sprite rectangleLeave;
    rectangleLeave.setTexture(textureRectangleLeave);
    rectangleLeave.setPosition(390, 350);

    window->draw(backGround);
    window->draw(rectangleMainPokemon);
    window->draw(rectangleSecondaryPokemon1); 
    window->draw(rectangleSecondaryPokemon2);
    window->draw(rectangleSecondaryPokemon3);
    window->draw(rectangleSecondaryPokemon4);
    window->draw(rectangleSecondaryPokemon5);
    window->draw(rectangleLeave);
}

void PartyMenu::SetPokemons(RenderWindow* window)
{
    Texture textureMainPokemon;
    textureMainPokemon.loadFromFile("Images/"+ party->getPokemons()[0]->getName() + "_mini.png");

    Sprite mainPokemon;
    mainPokemon.setTexture(textureMainPokemon);
    mainPokemon.setPosition(15, 105);

    Texture textureSecondaryPokemon1;
    Texture textureSecondaryPokemon2;
    Texture textureSecondaryPokemon3;
    Texture textureSecondaryPokemon4;
    Texture textureSecondaryPokemon5;

    Sprite secondaryPokemon1;
    Sprite secondaryPokemon2;
    Sprite secondaryPokemon3;
    Sprite secondaryPokemon4;
    Sprite secondaryPokemon5;

    Text textNameMainPokemon = InitializeText(party->getPokemons()[0]->getName(),30,Color::White,60,110);
    Text textNameSecondaryPokemon1;
    Text textNameSecondaryPokemon2;
    Text textNameSecondaryPokemon3;
    Text textNameSecondaryPokemon4;
    Text textNameSecondaryPokemon5;

    Text textLevelMainPokemon = InitializeText("N." + IntToString(party->getPokemons()[0]->getLevel()),30,Color::White,60,140);
    Text textLevelSecondaryPokemon1;
    Text textLevelSecondaryPokemon2;
    Text textLevelSecondaryPokemon3;
    Text textLevelSecondaryPokemon4;
    Text textLevelSecondaryPokemon5;
    
    Text textHpMainPokemon = InitializeText("HP : " + IntToString(party->getPokemons()[0]->getCurrentHealth()) + "/" + IntToString(party->getPokemons()[0]->getFullHealth()),30,Color::White,60,200);
    Text textHpSecondaryPokemon1;
    Text textHpSecondaryPokemon2;
    Text textHpSecondaryPokemon3;
    Text textHpSecondaryPokemon4;
    Text textHpSecondaryPokemon5;

    

    if(partySize >= 2)
    {
        
        string sdf = party->getPokemons()[1]->getName();
        textureSecondaryPokemon1.loadFromFile("Images/"+ party->getPokemons()[1]->getName() + "_mini.png");
        secondaryPokemon1.setTexture(textureSecondaryPokemon1);
        secondaryPokemon1.setPosition(255, 55);
        textNameSecondaryPokemon1 = InitializeText(party->getPokemons()[1]->getName(),18,Color::White,300,50);
        textLevelSecondaryPokemon1 = InitializeText("N." + IntToString(party->getPokemons()[1]->getLevel()),18,Color::White,300,70);
        textHpSecondaryPokemon1 = InitializeText("HP : " + IntToString(party->getPokemons()[1]->getCurrentHealth()) + "/" + IntToString(party->getPokemons()[1]->getFullHealth()),18,Color::White,400,70);

    }
    if(partySize >= 3)
    {
        textureSecondaryPokemon2.loadFromFile("Images/"+ party->getPokemons()[2]->getName() + "_mini.png");
        secondaryPokemon2.setTexture(textureSecondaryPokemon2);
        secondaryPokemon2.setPosition(255, 115);
        textNameSecondaryPokemon2 = InitializeText(party->getPokemons()[2]->getName(),18,Color::White,300,110);
        textLevelSecondaryPokemon2 = InitializeText("N." + IntToString(party->getPokemons()[2]->getLevel()),18,Color::White,300,130);
        textHpSecondaryPokemon2 = InitializeText("HP : " + IntToString(party->getPokemons()[2]->getCurrentHealth()) + "/" + IntToString(party->getPokemons()[2]->getFullHealth()),18,Color::White,400,130);
    }
    if(partySize >= 4)
    {
        textureSecondaryPokemon3.loadFromFile("Images/"+ party->getPokemons()[3]->getName() + "_mini.png");
        secondaryPokemon3.setTexture(textureSecondaryPokemon3);
        secondaryPokemon3.setPosition(255, 175);
        textNameSecondaryPokemon3 = InitializeText(party->getPokemons()[3]->getName(),18,Color::White,300,170);
        textLevelSecondaryPokemon3 = InitializeText("N." + IntToString(party->getPokemons()[3]->getLevel()),18,Color::White,300,190);
        textHpSecondaryPokemon3 = InitializeText("HP : " + IntToString(party->getPokemons()[3]->getCurrentHealth()) + "/" + IntToString(party->getPokemons()[3]->getFullHealth()),18,Color::White,400,190);
    }
    if(partySize >= 5)
    {
        textureSecondaryPokemon4.loadFromFile("Images/"+ party->getPokemons()[4]->getName() + "_mini.png");
        secondaryPokemon4.setTexture(textureSecondaryPokemon4);
        secondaryPokemon4.setPosition(255, 235);
        textNameSecondaryPokemon4 = InitializeText(party->getPokemons()[4]->getName(),18,Color::White,300,230);
        textLevelSecondaryPokemon4 = InitializeText("N." + IntToString(party->getPokemons()[4]->getLevel()),18,Color::White,300,250);
        textHpSecondaryPokemon4 = InitializeText("HP : " + IntToString(party->getPokemons()[4]->getCurrentHealth()) + "/" + IntToString(party->getPokemons()[4]->getFullHealth()),18,Color::White,400,250);
    }
    if(partySize == 6)
    {

        textureSecondaryPokemon5.loadFromFile("Images/"+ party->getPokemons()[5]->getName() + "_mini.png");
        secondaryPokemon5.setTexture(textureSecondaryPokemon5);
        secondaryPokemon5.setPosition(255, 295);
        textNameSecondaryPokemon5 = InitializeText(party->getPokemons()[5]->getName(),18,Color::White,300,290);
        textLevelSecondaryPokemon5 = InitializeText("N" + IntToString(party->getPokemons()[5]->getLevel()),18,Color::White,300,310);
        textHpSecondaryPokemon5 = InitializeText("HP : " + IntToString(party->getPokemons()[5]->getCurrentHealth()) + "/" + IntToString(party->getPokemons()[5]->getFullHealth()),18,Color::White,400,310);
    }

    window->draw(mainPokemon);
    window->draw(secondaryPokemon1);
    window->draw(secondaryPokemon2);
    window->draw(secondaryPokemon3);
    window->draw(secondaryPokemon4);
    window->draw(secondaryPokemon5);

    window->draw(textHpMainPokemon);
    window->draw(textHpSecondaryPokemon1);
    window->draw(textHpSecondaryPokemon2);
    window->draw(textHpSecondaryPokemon3);
    window->draw(textHpSecondaryPokemon4);
    window->draw(textHpSecondaryPokemon5);

    window->draw(textNameMainPokemon);
    window->draw(textNameSecondaryPokemon1);
    window->draw(textNameSecondaryPokemon2);
    window->draw(textNameSecondaryPokemon3);
    window->draw(textNameSecondaryPokemon4);
    window->draw(textNameSecondaryPokemon5);

    window->draw(textLevelMainPokemon);
    window->draw(textLevelSecondaryPokemon1);
    window->draw(textLevelSecondaryPokemon2);
    window->draw(textLevelSecondaryPokemon3);
    window->draw(textLevelSecondaryPokemon4);
    window->draw(textLevelSecondaryPokemon5);
}


void PartyMenu::MoveCursor(string direction)
{
    int y = cursor.getPosition().y;
    int x = cursor.getPosition().x;
    
    int mainYPosition = 110;
    int mainXPosition = 5;
    
    int SecondaryXPosition = 245; 
    int firstYPosition = 60;
    int secondYPosition = 120;
    int thirdYPosition = 180;
    int fourthYPosition = 240;
    int fifthYPosition = 300;

    int leaveXPosition = 380;
    int leaveYPosition = 360;

    if(x == SecondaryXPosition || x == leaveXPosition)
    {
        if(direction == "Up")
        {
            if(y == firstYPosition)
            {
                cursor.setPosition(leaveXPosition, leaveYPosition);
            }
            else if(y == secondYPosition)
            {
                cursor.setPosition(x, firstYPosition);
            }
            else if(y == thirdYPosition)
            {
                cursor.setPosition(x, secondYPosition);
            }
            else if(y == fourthYPosition)
            {
                cursor.setPosition(x, thirdYPosition);
            }
            else if (y == fifthYPosition)
            {
                cursor.setPosition(x, fourthYPosition);
            }
            else //if y = leaveYPosition
            {
                cursor.setPosition(SecondaryXPosition, fifthYPosition);
            }
        }
        else if(direction == "Down")
        {
            if(y == firstYPosition)
            {
                cursor.setPosition(x, secondYPosition);
            }
            else if(y == secondYPosition)
            {
                cursor.setPosition(x, thirdYPosition);
            }
            else if(y == thirdYPosition)
            {
                cursor.setPosition(x, fourthYPosition);
            }
            else if(y == fourthYPosition)
            {
                cursor.setPosition(x, fifthYPosition);
            }
            else if (y == fifthYPosition)
            {
                cursor.setPosition(leaveXPosition, leaveYPosition);
            }
            else // if y = leaveYPosition
            {
                cursor.setPosition(SecondaryXPosition, firstYPosition);
            }
        }
    }
    if(direction == "Right")// if direction = right or left
    {
        if(x == 5)
        {
            cursor.setPosition(SecondaryXPosition, firstYPosition);
        }
        else
        {
            cursor.setPosition(mainXPosition, mainYPosition);
        }
    }
}

void PartyMenu::MoveSmallCursor(string direction)
{
    int y = smallCursor.getPosition().y;
    int x = smallCursor.getPosition().x;

    int mainYPosition1 = 58;
    int mainYPosition2 = 78;
    int mainXPosition = 0;

    int SecondaryXPosition = 140; 
    int firstYPosition1 = 68;
    int secondYPosition1 = 88;
    int firstYPosition2 = 128;
    int secondYPosition2 = 148;
    int firstYPosition3 = 188;
    int secondYPosition3 = 208;
    int firstYPosition4 = 248;
    int secondYPosition4 = 268;
    int firstYPosition5 = 308;
    int secondYPosition5 = 328;

    switch (y)
    {
        //First choice
        case 58:
            smallCursor.setPosition(mainXPosition, mainYPosition2);
            break;
        case 68:
            smallCursor.setPosition(SecondaryXPosition, secondYPosition1);
            break;
        case 128:
            smallCursor.setPosition(SecondaryXPosition, secondYPosition2);
            break;
        case 188:
            smallCursor.setPosition(SecondaryXPosition, secondYPosition3);
            break;
        case 248:
            smallCursor.setPosition(SecondaryXPosition, secondYPosition4);
            break;
        case 308:
            smallCursor.setPosition(SecondaryXPosition, secondYPosition5);
            break;
        //Second choice
        case 78:
            smallCursor.setPosition(mainXPosition, mainYPosition1);
            break;
        case 88:
            smallCursor.setPosition(SecondaryXPosition, firstYPosition1);
            break;
        case 148:
            smallCursor.setPosition(SecondaryXPosition, firstYPosition2);
            break;
        case 208:
            smallCursor.setPosition(SecondaryXPosition, firstYPosition3);
            break;
        case 268:
            smallCursor.setPosition(SecondaryXPosition, firstYPosition4);
            break;
        case 328:
            smallCursor.setPosition(SecondaryXPosition, firstYPosition5);
            break;
    }

}

void PartyMenu::MoveCursorWhileOrderChanging(string direction)
{
    int y = smallCursor.getPosition().y;
    int x = smallCursor.getPosition().x;

    if(direction == "Up")
    {
        switch (y)
        {
            case 108:
                smallCursor.setPosition(x, 208);
                break;
            case 128:
                smallCursor.setPosition(x, 108);
                break;
            case 148:
                smallCursor.setPosition(x, 128);
                break;
            case 168:
                smallCursor.setPosition(x, 148);
                break;
            case 188:
                smallCursor.setPosition(x, 168);
                break;
            case 208:
                smallCursor.setPosition(x, 188);
                break;
        }
    }
    else
    {
        switch (y)
        {
            case 108:
                smallCursor.setPosition(x, 128);
                break;
            case 128:
                smallCursor.setPosition(x, 148);
                break;
            case 148:
                smallCursor.setPosition(x, 168);
                break;
            case 168:
                smallCursor.setPosition(x, 188);
                break;
            case 188:
                smallCursor.setPosition(x, 208);
                break;
            case 208:
                smallCursor.setPosition(x, 208);
                break;
        }
    }
}

void PartyMenu::SelectPokemon(RenderWindow*  window)
{
	bool isPokemon = true;
    int y = cursor.getPosition().y;
    int x = cursor.getPosition().x;

    int mainYPosition = 110;    
    int mainXPosition = 5;
    
    int SecondaryXPosition = 245; 
    int firstYPosition = 60;
    int secondYPosition = 120;
    int thirdYPosition = 180;
    int fourthYPosition = 240;
    int fifthYPosition = 300;
    int leaveYPosition = 360;

    Texture* textureRectangle = new Texture();
    textureRectangle->loadFromFile("Images/rectangle_bag_select_item.png");
    RectangleShape rectangle;
    rectangle.setTexture(textureRectangle);
    rectangle.setSize(Vector2f(100,55));

    Text textUse;
    textUse.setString("Changer l'ordre");
    textUse.setCharacterSize(15);
    textUse.setColor(Color::White);
    textUse.setFont(font);

    Text textBack;
    textBack.setString("Retour");
    textBack.setCharacterSize(15);
    textBack.setColor(Color::White);
    textBack.setFont(font);

    if(y == mainYPosition)
    {
        isPokemonSelected = true;
        pokemonSelected = party->getPokemons()[0];
        smallCursor.setPosition(mainXPosition - 5,mainYPosition - 52);
        textUse.setPosition(mainXPosition + 5,mainYPosition - 55);
        textBack.setPosition(mainXPosition + 5,mainYPosition - 35);
        rectangle.setPosition(mainXPosition,mainYPosition - 60);
    }
    else if(y == firstYPosition)
    {
        if(party->getPokemons().size() >= 2)
        {
            isPokemonSelected = true;
            pokemonSelected = party->getPokemons()[1];
            smallCursor.setPosition(SecondaryXPosition - 105,firstYPosition + 8);
            textUse.setPosition(SecondaryXPosition - 95,firstYPosition + 5);
            textBack.setPosition(SecondaryXPosition - 95,firstYPosition + 25);
            rectangle.setPosition(SecondaryXPosition - 100,firstYPosition);
        }
		else
		{
			isPokemon = false;
		}
    }
    else if(y == secondYPosition)
    {
        if(party->getPokemons().size() >= 3)
        {
            isPokemonSelected = true;
            pokemonSelected = party->getPokemons()[2];
            smallCursor.setPosition(SecondaryXPosition - 105,secondYPosition + 8);
            textUse.setPosition(SecondaryXPosition - 95,secondYPosition + 5);
            textBack.setPosition(SecondaryXPosition - 95,secondYPosition + 25);
            rectangle.setPosition(SecondaryXPosition - 100,secondYPosition);
        }
		else
		{
			isPokemon = false;
		}
    }
    else if(y == thirdYPosition)
    {
        if(party->getPokemons().size() >= 4)
        {
            isPokemonSelected = true;
            pokemonSelected = party->getPokemons()[3];
            smallCursor.setPosition(SecondaryXPosition - 105,thirdYPosition + 8);
            textUse.setPosition(SecondaryXPosition - 95,thirdYPosition + 5);
            textBack.setPosition(SecondaryXPosition - 95,thirdYPosition + 25);
            rectangle.setPosition(SecondaryXPosition - 100,thirdYPosition);
        }
		else
		{
			isPokemon = false;
		}
    }
    else if(y == fourthYPosition)
    {
        if(party->getPokemons().size() >= 5)
        {
            isPokemonSelected = true;
            pokemonSelected = party->getPokemons()[4];
            smallCursor.setPosition(SecondaryXPosition - 105,fourthYPosition + 8);
            textUse.setPosition(SecondaryXPosition - 95,fourthYPosition + 5);
            textBack.setPosition(SecondaryXPosition - 95,fourthYPosition + 25);
            rectangle.setPosition(SecondaryXPosition - 100,fourthYPosition);
        }
		else
		{
			isPokemon = false;
		}
    }
    else if (y == fifthYPosition)
    {
        if(party->getPokemons().size() == 6)
        {
            isPokemonSelected = true;
            pokemonSelected = party->getPokemons()[5];
            smallCursor.setPosition(SecondaryXPosition - 105,fifthYPosition + 8);
            textUse.setPosition(SecondaryXPosition - 95,fifthYPosition + 5);
            textBack.setPosition(SecondaryXPosition - 95,fifthYPosition + 25);
            rectangle.setPosition(SecondaryXPosition - 100,fifthYPosition);
        }
		else
		{
			isPokemon = false;
		}
    }
    else // if y = leaveYPosition
    {
        window->close();
    }

	SetRectangles(window);
	SetPokemons(window);

	if (isPokemon == true)
	{
		window->draw(rectangle);
		window->draw(textUse);
		window->draw(textBack);
	}

    captureImage = window->capture();
    captureTexture.loadFromImage(captureImage);
    capture.setTexture(captureTexture);
}

bool PartyMenu::SelectAction(RenderWindow* window)
{
    int y = smallCursor.getPosition().y;
    int x = smallCursor.getPosition().x;

    int mainYPosition1 = 58;
    int mainYPosition2 = 78;
    int mainXPosition = 0;

    int SecondaryXPosition = 140; 
    int firstYPosition1 = 68;
    int secondYPosition1 = 88;
    int firstYPosition2 = 128;
    int secondYPosition2 = 148;
    int firstYPosition3 = 188;
    int secondYPosition3 = 208;
    int firstYPosition4 = 248;
    int secondYPosition4 = 268;
    int firstYPosition5 = 308;
    int secondYPosition5 = 328;


   
    // First choice
    if(y == 58 || y == 68 || y == 128 || y == 188 || y == 248 || y == 308)
    {
        SetPokemonNames(window);
        return true;
    }

    // Second choice
    if(y == 78 || y == 88 || y == 148 || y == 208 || y == 268 || y == 328)
    {
        Initialize(window);
        isPokemonSelected = false;
        return false;
    }
}

void PartyMenu::SetPokemonNames(RenderWindow* window)
{
    Texture* textureRectangle = new Texture();
    textureRectangle->loadFromFile("Images/rectangle_bag_select_item.png");
    RectangleShape rectangle;
    rectangle.setTexture(textureRectangle);
    rectangle.setSize(Vector2f(100,150));
    rectangle.setPosition(200,100);
    
    Text texPokemonName1 = InitializeText(party->getPokemons()[0]->getName(),18,Color::White,205,105); 
    Text texPokemonName2;
    Text texPokemonName3;
    Text texPokemonName4;
    Text texPokemonName5;
    Text texPokemonName6;

    if(partySize >= 2)
    {
        texPokemonName2 = InitializeText(party->getPokemons()[1]->getName(),18,Color::White,205,125);
    }
    if(partySize >= 3)
    {
        texPokemonName3 = InitializeText(party->getPokemons()[2]->getName(),18,Color::White,205,145); 
    }
    if(partySize >= 4)
    {
        texPokemonName4 = InitializeText(party->getPokemons()[3]->getName(),18,Color::White,205,165); 
    }
    if(partySize >= 5)
    {
        texPokemonName5 = InitializeText(party->getPokemons()[4]->getName(),18,Color::White,205,185); 
    }
    if(partySize == 6)
    {
        texPokemonName6 = InitializeText(party->getPokemons()[5]->getName(),18,Color::White,205,205);
    }   
    SetRectangles(window);
    SetPokemons(window);

    window->draw(rectangle);
    window->draw(texPokemonName1);
    window->draw(texPokemonName2);
    window->draw(texPokemonName3);
    window->draw(texPokemonName4);
    window->draw(texPokemonName5);
    window->draw(texPokemonName6);

    captureImage = window->capture();
    captureTexture.loadFromImage(captureImage);
    capture.setTexture(captureTexture);

    smallCursor.setPosition(200,108);
    isOrderChanging = true;
}

void PartyMenu::ChangeOrder(RenderWindow* window)
{
    int y = smallCursor.getPosition().y;
    int x = smallCursor.getPosition().x; 

    switch (y)
    {
            case 108:
                pokemonToChange = party->getPokemons()[0];
                break;
            case 128:
                if(partySize >= 2)
                {
                    pokemonToChange = party->getPokemons()[1];
                }
                break;
            case 148:
                if(partySize >= 3)
                {
                    pokemonToChange = party->getPokemons()[2];
                }
                break;
            case 168:
                if(partySize >= 4)
                {
                    pokemonToChange = party->getPokemons()[3];
                }
                break;
            case 188:
                if(partySize >= 5)
                {
                    pokemonToChange = party->getPokemons()[4];
                }
                break;
            case 208:
                if(partySize == 6)
                {
                    pokemonToChange = party->getPokemons()[5];
                }
                break;
    }
    if(pokemonSelected != NULL && pokemonToChange != NULL)
    {
        party->ChangeOrder(pokemonSelected,pokemonToChange);
    }
        Initialize(window);
        isOrderChanging = false;
        isPokemonSelected = false;
        pokemonToChange = NULL;
    
}

Text PartyMenu::InitializeText(String text, int characterSize, Color color, int x, int y)
{
    Text textTemp;
    textTemp.setString(text);
    textTemp.setCharacterSize(characterSize);
    textTemp.setColor(color);
    textTemp.setPosition(x, y);
    textTemp.setFont(font);

    return textTemp;
}

string PartyMenu::IntToString(int number)
{
    stringstream convert;
    convert << number;
    return convert.str();
}
