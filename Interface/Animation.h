#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include "SFML/Graphics.hpp"

using namespace std;

namespace Interface
{
	class Animation
	{
		public:
			Animation();
			~Animation();
			void initialize(float x, float y, int amountFrameX, int amountFrameY, sf::Clock clock);
			void update(sf::RenderWindow &mainWin, float frameRate);
			void draw(sf::RenderWindow &mainWin);

			bool getActive() const;
			void setActive(bool isActive);

			int getCurrentFrame(int axis) const;
			void setCurrentFrame(int axis, int value);
			
			float getPosition(int axis) const;
			void setPosition(int	axis, int value);

			void setImage(sf::Image image);
		protected:
			int getFrameWidth();
			int getFrameHeight();			
		private:
			sf::Sprite spriteImage;
			sf::Texture texture;
			int currentFrameX;
			int currentFrameY;
			float x;
			float y;
			float frameCounter;
			float switchFrame;
			int amountFrameX;
			int amountFrameY;
			bool active;
			sf::Clock clock;
	};
}



#endif