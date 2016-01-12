#include "Animation.h"
using namespace Interface;

Animation::Animation()
{
}
Animation::~Animation()
{
}
int Animation::getFrameHeight()
{
	return 80 / this->amountFrameY;
}
int Animation::getFrameWidth()
{
	 return 72 / this->amountFrameX;
}
bool Animation::getActive() const
{
	return this->active;
}
void Animation::setActive(bool isActive)
{
	this->active = isActive;
}
int Animation::getCurrentFrame(int axis) const
{
	if(axis == 1)
	{
		return currentFrameX;
	}
	else
	{
		return currentFrameY;
	}
}
void Animation::setCurrentFrame(int axis, int value)
{
	if(axis == 1)
	{
		currentFrameX = value;
	}
	else
	{
		currentFrameY = value;
	}
}
float Animation::getPosition(int axis) const
{
	if(axis == 1)
	{
		return x;
	}
	else
	{
		return y;
	}
}
void Animation::setPosition(int axis, int value)
{
	if(axis == 1)
	{
		x = value;
	}
	else
	{
		y = value;
	}
}
void Animation::setImage(sf::Image image)
{
	this->texture.loadFromImage(image);
	this->spriteImage.setTexture(this->texture);
}
void Animation::initialize(float x, float y, int amountFrameX, int amountFrameY, sf::Clock clock)
{
	frameCounter = 0;
	switchFrame = 1;
	this->active = false;
	this->x = x;
	this->y = y;
	this->amountFrameX = amountFrameX;
	this->amountFrameY = amountFrameY;
	this->clock = clock;
}
void Animation::update(sf::RenderWindow &mainWin, float frameRate)
{
	if(active)
	{
		frameCounter += frameRate;
	}
	else
	{
		frameCounter = 0;
	}
	if(frameCounter >= switchFrame)
	{
		frameCounter = 0;
		clock.restart();
		currentFrameX += getFrameWidth();
		if(currentFrameX >= spriteImage.getTexture()->getSize().x)
		{
			currentFrameX = 0;
		}
	}
    if(currentFrameY == 1)
    {
        spriteImage.setTextureRect(sf::IntRect(currentFrameX , currentFrameY * getFrameHeight(), currentFrameX + getFrameWidth(), currentFrameY * getFrameHeight()));
    }
    else if(currentFrameY == 2)
    {
        spriteImage.setTextureRect(sf::IntRect(currentFrameX , currentFrameY * getFrameHeight(), currentFrameX + getFrameWidth(), currentFrameY * getFrameHeight() - getFrameHeight()));
    }
    else 
    {
        spriteImage.setTextureRect(sf::IntRect(currentFrameX , currentFrameY * getFrameHeight(), currentFrameX + getFrameWidth(), currentFrameY * getFrameHeight() + getFrameHeight()));
    }
	spriteImage.setPosition(x, y);
}
void Animation::draw(sf::RenderWindow &mainWin)
{
	mainWin.draw(spriteImage);
}