#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
using namespace std;
using namespace sf;

class Ship
{
private:
	Texture shipTexture;
	Sprite ship;
	float shipX;
	float shipY;

public:

//====================================================== 
// Ship: constructor of a Ship object
// parameters: 
//		win: contains the information of the window
// return type: none
//======================================================
	Ship(RenderWindow &win)
	{
		if (!shipTexture.loadFromFile("NewShip.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}

		ship.setTexture(shipTexture);

		float shipX = win.getSize().x / 2.0f;
		float shipY = 520;
		ship.setPosition(shipX, shipY);
	}

//====================================================== 
// getShipX: gets the x location of the ship 
// parameters: 
// return type: float holding the x value 
//======================================================
	float getShipX()
	{
		return ship.getPosition().x;
	}

//====================================================== 
// getShipY: gets the y location of the ship 
// parameters: 
// return type: float holding the y value 
//======================================================
	float getShipY()
	{
		return ship.getPosition().y;
	}

//====================================================== 
// getShipBounds: gets the space the ship takes up
// parameters: 
// return type: FloatRect of not only the location, but how large the sprite is 
//======================================================
	FloatRect getShipBounds()
	{
		return ship.getGlobalBounds();
	}

//====================================================== 
// drawShip: draws the ship sprite onto the window 
// parameters: 
//		wind: contains all of the information on the screen
// return type: void
//======================================================
	void drawShip(RenderWindow &win)
	{
		win.draw(ship);
	}

//====================================================== 
// moveShip: changes the ships location, based on the arrow keys pressed 
// parameters: 
// return type: void 
//======================================================
	void moveShip()
	{
		float DISTANCE = 6.0f;
		// Checks which arrow was pressed
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{	
			// Makes sure the ship cant move off the screen
			if (ship.getPosition().x <= 0)
			{
				ship.move(0, 0);
			}
			else
			{
				// moving to the left
				ship.move(-DISTANCE, 0);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if ((ship.getPosition().x + 22) >= 800)
			{
				ship.move(0, 0);
			}
			else
			{
				// moving to the right
				ship.move(DISTANCE, 0);
			}
		}
	}

//====================================================== 
// resetShip: resets the location of the ship 
// parameters: 
//		win: contains the information of everyting on the screen
// return type: void
//======================================================
	void resetShip(RenderWindow &win)
	{
		float shipX = win.getSize().x / 2.0f;
		float shipY = 520;
		ship.setPosition(shipX, shipY);
	}
};