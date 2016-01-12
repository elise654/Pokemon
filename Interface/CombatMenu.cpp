#include "CombatMenu.h"
#include "../Pokemon/Fight.h"

CombatMenu::CombatMenu(Trainer* trainer, Pokemon* enemy)
{
    font.loadFromFile("pkmnfl.ttf");
    trainerPokemons = trainer->getParty();
    enemyPokemon = enemy;
    moveText1.setString("");
    moveText2.setString("");
    moveText3.setString("");
    moveText4.setString("");
    this->trainer = trainer;
    fight = new SoftwareLogic::Fight(trainerPokemons->getPokemons().at(0), enemyPokemon);
    
    isActionSelected = false;
}

CombatMenu::~CombatMenu()
{
	//delete trainer;
    trainerPokemons->getPokemons().clear();
    //delete enemyPokemon;
    delete fight;
    moveSelected = NULL;
    enemyMove = NULL;
    enemyPokemon = NULL;
}

void CombatMenu::draw()
{
    RenderWindow combatWindow(VideoMode(500, 500, 32), "Fight");
    combatWindow.setVerticalSyncEnabled(true);

    Texture textureCursor;
    textureCursor.loadFromFile("Images/cursor.png");
    cursor.setTexture(textureCursor);
    cursor.setPosition(35, 420);
    cursorColor = cursor.getColor();

    SetRectangles(&combatWindow);
    SetChoices(&combatWindow);
    SetPokemon(&combatWindow);

    imageCapture = combatWindow.capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    combatWindow.draw(cursor);
	combatWindow.setMouseCursorVisible(false);

    combatWindow.display();
    while (combatWindow.isOpen())
	{
		Event event;
        
		while (combatWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				    //combatWindow.close();
				    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                    {
                        MoveCursor(true);
                        combatWindow.clear();
                        combatWindow.draw(capture);
                        combatWindow.draw(cursor);
                        combatWindow.display();
                    }
                    if(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
                    {
                        MoveCursor(false);
                        combatWindow.clear();
                        combatWindow.draw(capture);
                        combatWindow.draw(cursor);
                        combatWindow.display();
                    }
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        if(isActionSelected)
                        {
                            combatWindow.clear();
                            Attack(&combatWindow);
							
                            combatWindow.draw(capture);
                            combatWindow.draw(cursor);
                            combatWindow.display();
                            isActionSelected = false;
                        }
                        else
                        {
                            combatWindow.clear();
                            SelectOption(&combatWindow);
                            combatWindow.draw(capture);
                            combatWindow.draw(cursor);
                            combatWindow.display();
                        }
                    }
			}
		}
    }
}

void CombatMenu::SetRectangles(RenderWindow* window)
{
    RectangleShape rectangle;
    rectangle.setPosition(25,400);
    rectangle.setSize(sf::Vector2f(450,100));
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineColor(Color::Black);
    rectangle.setOutlineThickness(5);

    RectangleShape rectangleTrainerPokemon;
    rectangleTrainerPokemon.setSize(sf::Vector2f(200,100));
    rectangleTrainerPokemon.setPosition(280,250);
    rectangleTrainerPokemon.setOutlineColor(Color::Black);
    rectangleTrainerPokemon.setOutlineThickness(5);

    RectangleShape rectangleEnemyPokemon;
    rectangleEnemyPokemon.setSize(sf::Vector2f(200,100));
    rectangleEnemyPokemon.setPosition(20,20);
    rectangleEnemyPokemon.setOutlineColor(Color::Black);
    rectangleEnemyPokemon.setOutlineThickness(5);

    Texture textureBackGround;
    textureBackGround.loadFromFile("Images/GreyBackGround.png");
    Sprite spriteBackGround;
    spriteBackGround.setTexture(textureBackGround);
    
    window->draw(spriteBackGround);
    window->draw(rectangle);
    window->draw(rectangleTrainerPokemon);
    window->draw(rectangleEnemyPokemon);
}

void CombatMenu::SetChoices(RenderWindow* window)
{
    
    fightText.setString("Attaque");
    fightText.setFont(font);
    fightText.setColor(Color::Black);
    fightText.setCharacterSize(30);
    fightText.setPosition(50,410);

    pokemonText.setString("Pokemon");
    pokemonText.setColor(Color::Black);
    pokemonText.setFont(font);
    pokemonText.setCharacterSize(30);
    pokemonText.setPosition(50,460);

    leaveText.setString("Fuite");
    leaveText.setColor(Color::Black);
    leaveText.setFont(font);
    leaveText.setCharacterSize(30);
    leaveText.setPosition(340,460);

    bagText.setString("Sac");
    bagText.setFont(font);
    bagText.setColor(Color::Black);
    bagText.setCharacterSize(30);
    bagText.setPosition(340,410);

    window->draw(fightText);
    window->draw(bagText);
    window->draw(leaveText);
    window->draw(pokemonText);
}

void CombatMenu::ShowMoves(RenderWindow* window)
{
    int size = trainerPokemons->getPokemons()[0]->getMoves().size();

    pokemonText.setColor(Color::Transparent);
    bagText.setColor(Color::Transparent);
    leaveText.setColor(Color::Transparent);
    fightText.setColor(Color::Transparent);

    moveText1.setString(trainerPokemons->getPokemons()[0]->getMoves()[0]->getName());
    moveText1.setCharacterSize(30);
    moveText1.setColor(Color::Black);
    moveText1.setPosition(50,410);
    moveText1.setFont(font);

    if(size >= 2)
    {
        moveText2.setString(trainerPokemons->getPokemons()[0]->getMoves()[1]->getName());
        moveText2.setCharacterSize(30);
        moveText2.setColor(Color::Black);
        moveText2.setPosition(340,410);
        moveText2.setFont(font);
    }
    if(size >= 3)
    {
        moveText3.setString(trainerPokemons->getPokemons()[0]->getMoves()[2]->getName());
        moveText3.setCharacterSize(30);
        moveText3.setColor(Color::Black);
        moveText3.setPosition(50,460);
        moveText3.setFont(font);
    }
    if(size >= 4)
    {
        moveText4.setString(trainerPokemons->getPokemons()[0]->getMoves()[3]->getName());
        moveText4.setCharacterSize(30);
        moveText4.setColor(Color::Black);
        moveText4.setPosition(340,460);
        moveText4.setFont(font);
    }
    SetRectangles(window);
    SetPokemon(window);
    window->draw(moveText1);
    window->draw(moveText2);
    window->draw(moveText3);
    window->draw(moveText4);
	window->setMouseCursorVisible(false);
    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);
    isActionSelected = true;
}

void CombatMenu::SetPokemon(RenderWindow* window)
{
    //Trainer's pokemon
    Texture textureTrainerPokemon;
    textureTrainerPokemon.loadFromFile("Images/"+ trainerPokemons->getPokemons()[0]->getName() + "_back.png");

    Sprite spriteTrainerPokemon;
    spriteTrainerPokemon.setTexture(textureTrainerPokemon);
    spriteTrainerPokemon.setPosition(50,250);
   
    textAllyName.setString(trainerPokemons->getPokemons()[0]->getName());
    textAllyName.setColor(Color::Black);
    textAllyName.setCharacterSize(18);
    textAllyName.setFont(font);
    textAllyName.setPosition(290,260);

    textAllyHP.setString("Health :     " + IntToString(trainerPokemons->getPokemons()[0]->getCurrentHealth()) + "/" + IntToString(trainerPokemons->getPokemons()[0]->getFullHealth()));
    textAllyHP.setPosition(290, 280);
    textAllyHP.setColor(Color::Black);
    textAllyHP.setFont(font);
    textAllyHP.setCharacterSize(18);

    textAllyLevel.setString("N." + IntToString(trainerPokemons->getPokemons()[0]->getLevel()));
    textAllyLevel.setPosition(425, 260);
    textAllyLevel.setColor(Color::Black);
    textAllyLevel.setFont(font);
    textAllyLevel.setCharacterSize(18);

    textAllyExp.setString("Exp :     " + IntToString(trainerPokemons->getPokemons()[0]->getCurrentExperience()) + "/" + IntToString(trainerPokemons->getPokemons()[0]->getExperienceToLevelUp()));
    textAllyExp.setPosition(290, 300);
    textAllyExp.setColor(Color::Black);
    textAllyExp.setFont(font);
    textAllyExp.setCharacterSize(18);

    //Enemy pokemon
    Texture textureEnemyPokemon;
    textureEnemyPokemon.loadFromFile("Images/"+ enemyPokemon->getName() + "_front.png");

    Sprite spriteEnemyPokemon;
    spriteEnemyPokemon.setTexture(textureEnemyPokemon);
    spriteEnemyPokemon.setPosition(300,50);

    textEnemyName.setString(enemyPokemon->getName());
    textEnemyName.setCharacterSize(18);
    textEnemyName.setColor(Color::Black);
    textEnemyName.setFont(font);
    textEnemyName.setPosition(30,30);

    textEnemyHP.setString("Health :     " + IntToString(enemyPokemon->getCurrentHealth()) + "/" + IntToString(enemyPokemon->getFullHealth()));
    textEnemyHP.setPosition(30, 65);
    textEnemyHP.setColor(Color::Black);
    textEnemyHP.setFont(font);
    textEnemyHP.setCharacterSize(18);

    textEnemyLevel.setString("N." + IntToString(enemyPokemon->getLevel()));
    textEnemyLevel.setPosition(100, 30);
    textEnemyLevel.setFont(font);
    textEnemyLevel.setColor(Color::Black);
    textEnemyLevel.setCharacterSize(18);

    window->draw(spriteTrainerPokemon);
    window->draw(textAllyName);
    window->draw(textAllyHP);
    window->draw(textAllyLevel);
    window->draw(textAllyExp);
    window->draw(spriteEnemyPokemon);
    window->draw(textEnemyName);
    window->draw(textEnemyHP);
    window->draw(textEnemyLevel);
}

void CombatMenu::MoveCursor(bool isVertical)
{
    if(isVertical)
    {
        if(cursor.getPosition().y == 420)
        {
            cursor.setPosition(cursor.getPosition().x, 470);
        }
        else //If position y == 470
        {
            cursor.setPosition(cursor.getPosition().x, 420);
        }
    }
    else
    {
        if(cursor.getPosition().x == 35)
        {
            cursor.setPosition(325, cursor.getPosition().y);
        }
        else //If position x == 325 
        {
            cursor.setPosition(35, cursor.getPosition().y);
        }
    }
}

void CombatMenu::SelectOption(RenderWindow* window)
{
    int x = cursor.getPosition().x;
    int y = cursor.getPosition().y;

    if(x == 35)
    {
        if(y == 420)
        {
            ShowMoves(window);
        }
        else//If position y == 470
        {
            PartyMenu partyMenu(trainer->getParty());
            partyMenu.Draw();
            SetRectangles(window);
            SetPokemon(window);
            SetChoices(window);

            imageCapture = window->capture();
            textureCapture.loadFromImage(imageCapture);
            capture.setTexture(textureCapture);
            isActionSelected = false;
        }
    }
    else //If position x == 325 
    {
        if(y == 420)
        {
            MenuBag menubag(trainer->getBag(),trainer->getParty(),"CombatMenu", enemyPokemon, trainer, *window);
            menubag.draw(*window);
            isActionSelected = false;
        }
        else//If position y == 470
        {
            SetLeave(window);
        }        
    }
}

void CombatMenu::SetLeave(RenderWindow* window)
{
    
    textLeave.setString("Vous prenez la fuite.");
    textLeave.setColor(Color::Black);
    textLeave.setCharacterSize(30);
    textLeave.setPosition(50, 410);
    textLeave.setFont(font);

    pokemonText.setColor(Color::Transparent);
    bagText.setColor(Color::Transparent);
    leaveText.setColor(Color::Transparent);
    fightText.setColor(Color::Transparent);
    
    SetRectangles(window);
    SetPokemon(window);

    cursor.setColor(Color::White);
    window->draw(textLeave);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
    window->close();
    
}

void CombatMenu::Attack(RenderWindow* window)
{
	bool isDead = false;


    int trainerMoveSize = trainerPokemons->getPokemons()[0]->getMoves().size();
    int enemyMoveSize = trainerPokemons->getPokemons()[0]->getMoves().size();

    int x = cursor.getPosition().x;
    int y = cursor.getPosition().y;

    if(x == 35)
    {
        if(y == 420)
        {
             moveSelected = trainerPokemons->getPokemons()[0]->getMoves()[0];
        }
        else//If position y == 470
        {
            if(trainerMoveSize >= 2)
            {
                moveSelected = trainerPokemons->getPokemons()[0]->getMoves()[2];
            }
        }
    }
    else //If position x == 325 
    {
        if(y == 420)
        {
            if(trainerMoveSize >= 3)
            {
                moveSelected = trainerPokemons->getPokemons()[0]->getMoves()[1];
            }
        }
        else//If position y == 470
        {
            if(trainerMoveSize == 4)
            {
                moveSelected = trainerPokemons->getPokemons()[0]->getMoves()[3];
            }
        }        
    }

    fight->Attack(trainerPokemons->getPokemons().at(0), enemyPokemon, moveSelected);
    
    SetAllyMove(window, moveSelected);
    SetAllyEffective(window, moveSelected, enemyPokemon);

	if (enemyPokemon->isDead() == true)
	{
		
		trainer->getBag()->AddMoney(100);
		SetKillEnemy(window);
		isDead = true;
	}

	if (isDead == false)
	{
		fight->Attack(enemyPokemon, trainerPokemons->getPokemons().at(0), enemyPokemon->getMoves().at(0));

		SetEnemyMove(window, enemyPokemon->getMoves()[0]);
		SetEnemyEffective(window,  enemyPokemon->getMoves().at(0), trainerPokemons->getPokemons().at(0));
	}
    
	if (trainerPokemons->getPokemons()[0]->isDead() == true)
	{
		SetKillAlly(window);
		isDead = true;
	}

    cursor.setColor(cursorColor);

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    SetChoices(window);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

}

void CombatMenu::SetAllyMove(RenderWindow* window, Move* move)
{
    Text textAllyMove;
    textAllyMove.setString(trainerPokemons->getPokemons()[0]->getName() + "  utilise  \n\n" + move->getName());
    textAllyMove.setCharacterSize(30);
    textAllyMove.setColor(Color::Black);
    textAllyMove.setPosition(50, 410);
    textAllyMove.setFont(font);

    cursor.setColor(Color::White);

    

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    window->draw(textAllyMove);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
}

void CombatMenu::SetAllyEffective(RenderWindow* window,  Move* move, Pokemon* enemy)
{
    Text textAllyEffective;
	if(enemy->getType().getWeakness1() == move->getType().getTypeName() || enemy->getType().getWeakness2() == move->getType().getTypeName())
	{
		textAllyEffective.setString("C'est super efficace !");
	}
	else if(enemy->getType().getStrength1() == move->getType().getTypeName() || enemy->getType().getStrength2() == move->getType().getTypeName())
	{
		textAllyEffective.setString("C'est n'est pas tres efficace.");
	}
	else
	{
		textAllyEffective.setString("C'est normalement efficace.");
	}
    textAllyEffective.setCharacterSize(30);
    textAllyEffective.setColor(Color::Black);
    textAllyEffective.setPosition(50, 410);
    textAllyEffective.setFont(font);

    cursor.setColor(Color::White);

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    window->draw(textAllyEffective);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
}

void CombatMenu::SetEnemyMove(RenderWindow* window, Move* move)
{
    Text textEnemyMove;
    textEnemyMove.setString(enemyPokemon->getName() + "  ennemi  utilise  \n\n" + move->getName());
    textEnemyMove.setCharacterSize(30);
    textEnemyMove.setColor(Color::Black);
    textEnemyMove.setPosition(50, 410);
    textEnemyMove.setFont(font);

    cursor.setColor(Color::White);

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    window->draw(textEnemyMove);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
}

void CombatMenu::SetEnemyEffective(RenderWindow* window,  Move* move, Pokemon* enemy)
{
    Text textEnemyEffective;
    if(enemy->getType().getWeakness1() == move->getType().getTypeName() || enemy->getType().getWeakness2() == move->getType().getTypeName())
	{
		textEnemyEffective.setString("C'est super efficace !");
	}
	else if(enemy->getType().getStrength1() == move->getType().getTypeName() || enemy->getType().getStrength2() == move->getType().getTypeName())
	{
		textEnemyEffective.setString("C'est n'est pas tres efficace.");
	}
	else
	{
		textEnemyEffective.setString("C'est normalement efficace.");
	}
    textEnemyEffective.setCharacterSize(30);
    textEnemyEffective.setColor(Color::Black);
    textEnemyEffective.setPosition(50, 410);
    textEnemyEffective.setFont(font);

    cursor.setColor(Color::White);

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    window->draw(textEnemyEffective);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
}

void CombatMenu::Wait()
{
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();
    while(time < 2)
    {
        time = clock.getElapsedTime().asSeconds();
    }
}

string CombatMenu::IntToString(int number)
{
    stringstream convert;
    convert << number;
    return convert.str();
}

void CombatMenu::SetKillAlly(RenderWindow* window)
{
    bool allDead = true;
    for(int i = 0; i< trainerPokemons->getPokemons().size(); i++)
    {
        if(!(trainerPokemons->getPokemons()[i]->isDead()))
        {
            allDead = false;
            break;
        }
    }

    Text textKillAlly;
    textKillAlly.setString("Votre Pokemon s'est évanoui.\n\nVeuillez en choisir un autre.");
    textKillAlly.setCharacterSize(30);
    textKillAlly.setColor(Color::Black);
    textKillAlly.setPosition(45, 410);
    textKillAlly.setFont(font);

    if(allDead)
    {
        textKillAlly.setString("Aucun de vos Pokemons est en état\n\nde se battre.Vous devez les soigner");
        trainer->getBag()->RemoveMoney(trainer->getBag()->getMoney()/2);
        window->clear();
        SetRectangles(window);
        SetPokemon(window);

        window->draw(textKillAlly);
        window->display();
        Wait();
        Wait();
        
        window->close();
    }
    else
    {
        cursor.setColor(Color::White);

        window->clear();
        SetRectangles(window);
        SetPokemon(window);
        window->draw(textKillAlly);

        imageCapture = window->capture();
        textureCapture.loadFromImage(imageCapture);
        capture.setTexture(textureCapture);

        window->draw(capture);
        window->display();
        Wait();
        PartyMenu partyMenu(trainerPokemons);
        partyMenu.Draw();
    }

}

void CombatMenu::SetKillEnemy(RenderWindow* window)
{
    Text textKillEnemy;
	SetExpGain(window);
    textKillEnemy.setString("Vous etes le vainqueur.\n\nVous gagnez 100$");
    textKillEnemy.setCharacterSize(30);
    textKillEnemy.setColor(Color::Black);
    textKillEnemy.setPosition(50, 410);
    textKillEnemy.setFont(font);

    cursor.setColor(Color::White);

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    window->draw(textKillEnemy);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
	window->close();
}
void CombatMenu::SetExpGain(RenderWindow* window)
{
	string expMessage = fight->setNewExp(trainerPokemons->getPokemons().at(0), enemyPokemon);
	Text textExpGain;
    textExpGain.setString(expMessage);
    textExpGain.setCharacterSize(30);
	textExpGain.setColor(Color::Black);
    textExpGain.setPosition(50, 410);
    textExpGain.setFont(font);

    cursor.setColor(Color::White);

    window->clear();
    SetRectangles(window);
    SetPokemon(window);
    window->draw(textExpGain);

    imageCapture = window->capture();
    textureCapture.loadFromImage(imageCapture);
    capture.setTexture(textureCapture);

    window->draw(capture);
    window->display();
    Wait();
}