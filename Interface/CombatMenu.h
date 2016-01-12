#pragma once 

#include "SFML/Graphics.hpp"
#include "MenuBag.h"
#include "PartyMenu.h"
#include "../Pokemon/Fight.h"

#include <sstream>



using namespace sf;


class CombatMenu
{
public:
    CombatMenu(Trainer* trainer, Pokemon* enemy);
    ~CombatMenu();

    void draw();
    void ShowMoves(RenderWindow* window);

private:
    Trainer* trainer;
    SoftwareLogic::Fight* fight;
    Move* moveSelected;
    Move* enemyMove;

    Font font;
    Pokemon* enemyPokemon;
    Party* trainerPokemons;

    Text moveText1;
    Text moveText2;
    Text moveText3;
    Text moveText4;

    Text pokemonText;
    Text fightText;
    Text leaveText;
    Text bagText;

    Text textAllyName;
    Text textAllyHP;
    Text textAllyLevel;
    Text textAllyExp;
    Text textEnemyName;
    Text textEnemyHP;
    Text textEnemyLevel;

    Color cursorColor;
    Text textLeave;
    Image imageCapture;
    Texture textureCapture;
    Sprite cursor;
    Sprite capture;


    bool isActionSelected;

    void SetRectangles(RenderWindow* window);
    void SetChoices(RenderWindow* window);
    void SetPokemon(RenderWindow* window);
    void MoveCursor(bool isVertical);
    void SelectOption(RenderWindow* window);
    void SetLeave(RenderWindow* window);
    void Attack(RenderWindow* window);


    void SetAllyMove(RenderWindow* window, Move* move);
    void SetAllyEffective(RenderWindow* window,  Move* move, Pokemon* enemy);
    void SetKillAlly(RenderWindow* window);
    void SetEnemyMove(RenderWindow* window, Move* move);
    void SetEnemyEffective(RenderWindow* window,  Move* move, Pokemon* enemy);
	void SetKillEnemy(RenderWindow* window);
	void SetExpGain(RenderWindow* window);

    void Wait();
    string IntToString(int number);
};