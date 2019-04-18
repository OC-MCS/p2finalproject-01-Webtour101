#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Enemies.h"

using namespace std;
using namespace sf;

class Bomb
{
private:
	Sprite bomb;

public:

//====================================================== 
// Bomb: constructor of a Bomb object
// parameters: 
//		bombTexture: the texture to be put into the sprite of the bomb
// return type: none
//======================================================
	Bomb(Texture& bombTexture)
	{
		bomb.setTexture(bombTexture);
	}

//====================================================== 
// setBombSet: sets the location for the bomb
// parameters: 
//		pos: contains the vector of the location of the enemy dropping the bomb
// return type: void
//======================================================
	void setBombPos(Vector2f pos)
	{
		bomb.setPosition(pos);
	}

//====================================================== 
// drawBomb: draws the bomb onto the window
// parameters: 
//		win: contains all the information to be displayed 
//		speed: the desired speed of the bomb to fall, based on the level
// return type: void
//======================================================
	void drawBomb(RenderWindow &win, float speed)
	{

		if (bomb.getPosition().y > 0)
		{
			win.draw(bomb);
			bomb.move(0, speed);
		}
	}

//====================================================== 
// getBombBounds: gets the space the bomb takes up
// parameters: 
// return type: FloatRect of not only the location, but how large the sprite is 
//======================================================
	FloatRect getBombBounds()
	{
		return bomb.getGlobalBounds();
	}

//====================================================== 
// getBombY: gets the y location of the bomb 
// parameters: 
// return type: float holding the y value 
//======================================================
	float getBombY()
	{
		return bomb.getPosition().y;
	}

};
