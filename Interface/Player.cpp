#include "Player.h"
using namespace Interface;
Player::Player()
{
}
Player::Player(sf::Clock clock)
{
	this->clock = clock;
}
Player::~Player()
{
}
void Player::initialize(int x, int y)
{
	this->x = x;
	this->y = y;
	this->moveSpeedX = 20;
    this->moveSpeedY = 18;
	this->currentFrameX = 0;
	this->currentFrameY = 0;
	this->playerAnimation.initialize(x,y,4,4,clock);
	this->playerAnimation.setCurrentFrame(1,0);
	this->playerAnimation.setCurrentFrame(2,0);
}
void Player::loadContent()
{
	if(this->playerImage.loadFromFile("Images/player.png"))
	{
		this->playerAnimation.setImage(this->playerImage);
	}
}
void Player::update(sf::RenderWindow &mainWin, string direction, float frameRate, Map map)
{
	this->playerAnimation.setActive(true);


	if (direction == "Right")
	{
		if(map.IsTileValid(x + moveSpeedX,y))
		{
			this->x += this->moveSpeedX ;//* frameRate;
		}
		this->currentFrameY = 3;
	}
	else if (direction == "Left")
	{
		if(map.IsTileValid(x - moveSpeedX,y))
		{
			this->x -= this->moveSpeedX ;//* frameRate;
		}
		this->currentFrameY = 2;
	}
	else if (direction == "Up")
	{
		if(map.IsTileValid(x,y - moveSpeedY))
		{
			this->y -= this->moveSpeedY ;//* frameRate;
		}
		this->currentFrameY = 1;
	}
	else if (direction == "Down")
	{
		if(map.IsTileValid(x, y + moveSpeedY ))
		{
			this->y += this->moveSpeedY ;//* frameRate;
		}
		this->currentFrameY = 0;
	}
	else
	{
		this->playerAnimation.setActive(false);
	}
    if(map.IsTileValid(this->x, this->y))
    {
        this->playerAnimation.setPosition(1, this->x);
	    this->playerAnimation.setPosition(2, this->y);
    }
	this->playerAnimation.setCurrentFrame(2, this->currentFrameY);
	this->playerAnimation.update(mainWin, frameRate);
}
void Player::draw(sf::RenderWindow &mainWin)
{
	this->playerAnimation.draw(mainWin);
}

int Player::getX() const
{
    return this->x;
}

int Player::getY() const
{
    return this->y;
}

void Player::setX(int x)
{
    this->x = x;
}

void Player::setY(int y)
{
    this->y = y;
}
