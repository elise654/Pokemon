#include "PokeMartMenu.h"

#define POKEBALL_PRICE 200
#define POTION_PRICE 300
#define SUPER_POTION_PRICE 600 

#define RIGHT_X_POSITION 210
#define LEFT_X_POSITION 10

#define FIRST_Y_POSITION 55
#define SECOND_Y_POSITION 85
#define THIRD_Y_POSITION 115
#define LEAVE_Y_POSITION 230

#define FONT_PATH "pkmnfl.ttf"

PokeMartMenu::PokeMartMenu(Trainer* trainer)
{
    this->font.loadFromFile(FONT_PATH);
    this->trainer = trainer;
    this->textureCursor.loadFromFile("Images/cursor_small.png");
    this->cursor.setTexture(textureCursor);
}

PokeMartMenu::~PokeMartMenu()
{

}

void PokeMartMenu::Draw()
{
    RenderWindow pokeMartWindow(VideoMode(400, 280, 32), "PokeMart");
    pokeMartWindow.setVerticalSyncEnabled(true);

    this->SetInterface(&pokeMartWindow);

    this->imageCapture = pokeMartWindow.capture();
    this->textureCapture.loadFromImage(this->imageCapture);
    this->capture.setTexture(this->textureCapture);

    this->cursor.setPosition(10, 55);
    pokeMartWindow.draw(cursor);

    pokeMartWindow.display();


    while (pokeMartWindow.isOpen())
    {
        Event event;
        
		while (pokeMartWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				    //combatWindow.close();
				    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        pokeMartWindow.clear();
                        this->MoveCursor(&pokeMartWindow,"Up");
                        pokeMartWindow.draw(capture);
                        pokeMartWindow.draw(cursor);
                        pokeMartWindow.display();
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        pokeMartWindow.clear();
                        this->MoveCursor(&pokeMartWindow,"Down");
                        pokeMartWindow.draw(capture);
                        pokeMartWindow.draw(cursor);
                        pokeMartWindow.display();
                    }
                    else if(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
                    {
                        pokeMartWindow.clear();
                        this->MoveCursor(&pokeMartWindow,"Right");
                        pokeMartWindow.draw(capture);
                        pokeMartWindow.draw(cursor);
                        pokeMartWindow.display();
                    }
                    else if(event.key.code == sf::Keyboard::Space)
                    {
                        pokeMartWindow.clear();
                        this->SelectOption(&pokeMartWindow);
                        pokeMartWindow.draw(capture);
                        pokeMartWindow.draw(cursor);
                        pokeMartWindow.display();
                    }
            }
        }
    }
}

void PokeMartMenu::SetInterface(RenderWindow* window)
{
    Texture textureBackGround;
    textureBackGround.loadFromFile("Images/backGround_Bag.png");
    Sprite spriteBackGround;
    spriteBackGround.setTexture(textureBackGround);

    Texture textureLeave;
    textureLeave.loadFromFile("Images/party_Leave.png");
    Sprite spriteLeave;
    spriteLeave.setTexture(textureLeave);
    spriteLeave.setPosition(220, 220);

    Texture* textureRectangle = new Texture();
    textureRectangle->loadFromFile("Images/rectangle_bag_select_item.png");

    RectangleShape firsrtRectangle;
    firsrtRectangle.setTexture(textureRectangle);
    firsrtRectangle.setPosition(10,10);
    firsrtRectangle.setSize(Vector2f(180, 200));

    RectangleShape secondRectangle;
    secondRectangle.setTexture(textureRectangle);
    secondRectangle.setPosition(200,10);
    secondRectangle.setSize(Vector2f(180, 200));

    Text textBuy = InitializeText("Acheter",30,Color::White,20,10);
    textPokeball = InitializeText("Pokeball (" + IntToString(POKEBALL_PRICE) + " $)",18,Color::White,20,50);
    textPotion = InitializeText("Potion (" + IntToString(POTION_PRICE) + " $)",18,Color::White,20,80);
    textSuperPotion = InitializeText("Super Potion (" + IntToString(SUPER_POTION_PRICE) + " $)",18,Color::White,20,110);

    Text textSell = InitializeText("Vendre",30,Color::White,220,10);
    textTrainerPokeball = InitializeText("Pokeball (" + IntToString(POKEBALL_PRICE/2) + " $)",18,Color::White,220,50);
    textTrainerPotion = InitializeText("Potion (" + IntToString(POTION_PRICE/2) + " $)",18,Color::White,220,80);
    textTrainerSuperPotion = InitializeText("Super Potion (" + IntToString(SUPER_POTION_PRICE/2) + " $)",18,Color::White,220, 110);

    textMoney = InitializeText(IntToString(trainer->getBag()->getMoney()) + " $",18,Color::White,10,225);

    window->draw(spriteBackGround);
    window->draw(spriteLeave);
    window->draw(firsrtRectangle);
    window->draw(secondRectangle);
    window->draw(textBuy);
    window->draw(textPokeball);
    window->draw(textPotion);
    window->draw(textSuperPotion);
    window->draw(textSell);
    window->draw(textTrainerPokeball);
    window->draw(textTrainerPotion);
    window->draw(textTrainerSuperPotion);
    window->draw(textMoney);
}

void PokeMartMenu ::MoveCursor(RenderWindow* window, string direction)
{
    int y = cursor.getPosition().y;
    int x = cursor.getPosition().x;

        if(direction == "Up")
        {
            if(y == FIRST_Y_POSITION)
            {
                if(x == LEFT_X_POSITION)
                {
                    cursor.setPosition(x, THIRD_Y_POSITION);
                }
                else
                {
                    cursor.setPosition(x, LEAVE_Y_POSITION);
                }
            }
            else if(y == SECOND_Y_POSITION)
            {
                cursor.setPosition(x, FIRST_Y_POSITION);
            }
            else if(y == THIRD_Y_POSITION)
            {
                cursor.setPosition(x, SECOND_Y_POSITION);
            }
            else if(y == LEAVE_Y_POSITION)
            {
                cursor.setPosition(x, THIRD_Y_POSITION);
            }
        }
        else if(direction == "Down")
        {
            if(y == FIRST_Y_POSITION)
            {
                cursor.setPosition(x, SECOND_Y_POSITION);
            }
            else if(y == SECOND_Y_POSITION)
            {
                cursor.setPosition(x, THIRD_Y_POSITION);
            }
            else if(y == THIRD_Y_POSITION)
            {
                if(x == LEFT_X_POSITION)
                {
                    cursor.setPosition(x, FIRST_Y_POSITION);
                }
                else
                {
                    cursor.setPosition(x, LEAVE_Y_POSITION);
                }
                
            }
            else if(y == LEAVE_Y_POSITION)
            {
                cursor.setPosition(x, FIRST_Y_POSITION);
            }
        }
        else if(direction == "Right")
        {
            if(y != LEAVE_Y_POSITION)
            {
                if(x == RIGHT_X_POSITION)
                {
                    cursor.setPosition(LEFT_X_POSITION, y);
                }
                else if(x == LEFT_X_POSITION)
                {
                    cursor.setPosition(RIGHT_X_POSITION, y);
                }
            }
        }

}

void PokeMartMenu::SelectOption(RenderWindow* window)
{
    int x = cursor.getPosition().x;

    if(x == LEFT_X_POSITION)
    {
        this->BuyItem(window);
    }
    else
    {
        if(cursor.getPosition().y == LEAVE_Y_POSITION)
        {
            window->close();
        }
        else
        {
            this->SellItem(window);
        }
        
    }
}

void PokeMartMenu::BuyItem(RenderWindow* window)
{
    int y = cursor.getPosition().y;
    int x = cursor.getPosition().x;

    if(y == FIRST_Y_POSITION)
    {
        if(this->trainer->getBag()->getMoney() >= POKEBALL_PRICE)
        {
            this->trainer->BuyItem(new Pokeball("Pokeball",POKEBALL_PRICE,23));
            this->textMoney.setString(IntToString(this->trainer->getBag()->getMoney()) + " $");

            this->SetInterface(window);

            this->imageCapture = window->capture();
            this->textureCapture.loadFromImage(this->imageCapture);
            this->capture.setTexture(this->textureCapture);
            
            window->draw(this->capture);
            window->display();
        }
        else
        {
            Text textNotEnoughMoney = InitializeText("Vous n'avez pas assez d'argent.",22,Color::Black,60,170);
            window->draw(this->capture);
            window->draw(textNotEnoughMoney);
            window->display();
            this->Wait();
        }
    }
    else if(y == SECOND_Y_POSITION)
    {
        if(this->trainer->getBag()->getMoney() >= POTION_PRICE)
        {
            this->trainer->BuyItem(new Potion("Potion",POTION_PRICE,23));
            this->textMoney.setString(this->IntToString(this->trainer->getBag()->getMoney()) + " $");

            this->SetInterface(window);

            this->imageCapture = window->capture();
            this->textureCapture.loadFromImage(this->imageCapture);
            this->capture.setTexture(this->textureCapture);
            
            window->draw(this->capture);
            window->display();
        }
        else
        {
            Text textNotEnoughMoney = this->InitializeText("Vous n'avez pas assez d'argent.",22,Color::Black,60,170);
            window->draw(this->capture);
            window->draw(textNotEnoughMoney);
            window->display();
            this->Wait();
        }
    }
    else if(y == THIRD_Y_POSITION)
    {
        if(this->trainer->getBag()->getMoney() >= SUPER_POTION_PRICE)
        {
            this->trainer->BuyItem(new Potion("Super Potion",SUPER_POTION_PRICE,23));
            this->textMoney.setString(this->IntToString(this->trainer->getBag()->getMoney()) + " $");

            this->SetInterface(window);

            this->imageCapture = window->capture();
            this->textureCapture.loadFromImage(this->imageCapture);
            this->capture.setTexture(this->textureCapture);
            
            window->draw(this->capture);
            window->display();
        }
        else
        {
            Text textNotEnoughMoney = InitializeText("Vous n'avez pas assez d'argent.",22,Color::Black,60,170);
            window->draw(this->capture);
            window->draw(textNotEnoughMoney);
            window->display();
            this->Wait();
        }
    }
}

void PokeMartMenu::SellItem(RenderWindow* window)
{
    int y = cursor.getPosition().y;


    int pokeballCount = 0;
    int potionCount = 0;
    int superPotionCount = 0;


    for(int i = 0; i < this->trainer->getBag()->getItems().size(); i++)
        {
            if(this->trainer->getBag()->getItems()[i]->getName() == "Pokeball")
            {
                pokeballCount++;
            }
            else if(this->trainer->getBag()->getItems()[i]->getName() == "Potion")
            {
                potionCount++;
            }
            else if(this->trainer->getBag()->getItems()[i]->getName() == "Super Potion")
            {
                superPotionCount++;
            }
        }
    if(y == FIRST_Y_POSITION)
    {
        
        if(pokeballCount > 0)
        {
            this->trainer->SellItem(new Pokeball("Pokeball",POKEBALL_PRICE / 2,23));
            this->textMoney.setString(this->IntToString(this->trainer->getBag()->getMoney()) + " $");

            this->SetInterface(window);

            this->imageCapture = window->capture();
            this->textureCapture.loadFromImage(this->imageCapture);
            this->capture.setTexture(this->textureCapture);
            
            window->draw(this->capture);
            window->display();
        }
        else
        {
            Text textNotEnoughMoney = InitializeText("Vous n'avez pas de Pokeball.",22,Color::Black,60,170);
            window->draw(this->capture);
            window->draw(textNotEnoughMoney);
            window->display();
            this->Wait();
        }
    }
    else if(y == SECOND_Y_POSITION)
    {
        if(potionCount > 0)
        {
            this->trainer->SellItem(new Potion("Potion",POTION_PRICE / 2,23));
            this->textMoney.setString(IntToString(trainer->getBag()->getMoney()) + " $");

            this->SetInterface(window);

            this->imageCapture = window->capture();
            this->textureCapture.loadFromImage(this->imageCapture);
            this->capture.setTexture(this->textureCapture);
            
            window->draw(this->capture);
            window->display();
        }
        else
        {
            Text textNotEnoughMoney = this->InitializeText("Vous n'avez pas de potion.",22,Color::Black,60,170);
            window->draw(this->capture);
            window->draw(textNotEnoughMoney);
            window->display();
            this->Wait();
        }
    }
    else if(y == THIRD_Y_POSITION)
    {
        if(superPotionCount > 0)
        {
            this->trainer->SellItem(new Potion("Potion",SUPER_POTION_PRICE / 2,23));
            this->textMoney.setString(this->IntToString(this->trainer->getBag()->getMoney()) + " $");

            this->SetInterface(window);

            this->imageCapture = window->capture();
            this->textureCapture.loadFromImage(this->imageCapture);
            this->capture.setTexture(this->textureCapture);
            
            window->draw(this->capture);
            window->display();
        }
        else
        {
            Text textNotEnoughMoney = this->InitializeText("Vous n'avez pas de super potion.",22,Color::Black,60,170);
            window->draw(this->capture);
            window->draw(textNotEnoughMoney);
            window->display();
            this->Wait();
        }
    }
}

void PokeMartMenu::Wait()
{
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();
    while(time < 2)
    {
        time = clock.getElapsedTime().asSeconds();
    }
}

string PokeMartMenu::IntToString(int number)
{
    stringstream convert;
    convert << number;
    return convert.str();
}

Text PokeMartMenu::InitializeText(String text, int characterSize, Color color, int x, int y)
{
    Text textTemp;
    textTemp.setString(text);
    textTemp.setCharacterSize(characterSize);
    textTemp.setColor(color);
    textTemp.setPosition(x, y);
    textTemp.setFont(font);

    return textTemp;
}