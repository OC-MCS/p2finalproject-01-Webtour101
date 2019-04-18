#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Ship.h"
using namespace std;
using namespace sf;

class Missile
{
private:

	Sprite missile;

public:

//====================================================== 
// Missile: constructor of a single missile 
// parameters: 
//		missileTexture: to take and put in the texture of the missile
// return type: none
//======================================================
	Missile(Texture& missileTexture)
	{
	
		missile.setTexture(missileTexture);

	}

//====================================================== 
// setMissilePos: sets the location of the missile based on the location of the ship 
// parameters: 
//		goodGuy: contains the location of the ship
// return type: void
//======================================================
	void setMissilePos(Ship goodGuy)
	{
		missile.setPosition(goodGuy.getShipX() + 8, goodGuy.getShipY());
	}


//====================================================== 
// drawMissile: draws the missile onto the window
// parameters: 
//		win: contains all the information to be displayed 
// return type: void
//======================================================
	void drawMissile(RenderWindow &win)
	{
		if (missile.getPosition().y > 0)
		{
			win.draw(missile);
			missile.move(0, -15);
		}
	}

//====================================================== 
// getMissileBounds: gets the space the missile takes up
// parameters: 
// return type: FloatRect of not only the location, but how large the sprite is 
//======================================================
	FloatRect getMissileBounds()
	{
		return missile.getGlobalBounds();
	}

//====================================================== 
// getMissileY: gets the y value of the missile location
// parameters: 
// return type: float that contains the y value of the missile 
//======================================================
	float getMissileY()
	{
		return missile.getPosition().y;
	}

};