#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Map.h"
using namespace std;

namespace Interface
{
	class Player
	{
		public:
			Player();
			Player(sf::Clock clock);
			~Player();
			void initialize(int x, int y);
			void loadContent();
			void update(sf::RenderWindow &mainWin, string direction, float frameRate, Map map);
			void draw(sf::RenderWindow &mainWin);
            int getX() const;
            int getY() const;
            void setX(int x);
            void setY(int y);

		protected:
			Animation playerAnimation;
		private:
			sf::Image playerImage;
			float x;
			float y;
			int currentFrameX;
			int currentFrameY;			
			float moveSpeedX;
            float moveSpeedY;
			sf::Clock clock;
	};
}

#endif