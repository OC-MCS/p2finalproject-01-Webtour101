#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Game.h"
using namespace std;
using namespace sf;

class Alien
{
private:

	Sprite enemy;
	float enemyX;
	float enemyY;
	float speed = 0;
public:

//====================================================== 
// Alien: constructor of an Alien object
// parameters: 
//		x: the x location of the single alien
//		y: the y location of the single alien
//		enemyTexture: the texture to be put into the sprite of the enemy
//		game: contains the current game level information
// return type: none
//======================================================
	Alien(float x, float y, Texture &enemyTexture, Game &game)
	{
		if (game.getGameLevel() < 2)
		{
			if (!enemyTexture.loadFromFile("Lvl1Enemy.png"))
			{
				cout << "Unable to load enemy texture!" << endl;
				exit(EXIT_FAILURE);
			}
			enemy.setTexture(enemyTexture);
		}
		else if (game.getGameLevel() == 2)
		{
			if (!enemyTexture.loadFromFile("Lvl2Enemy.png"))
			{
				cout << "Unable to load enemy texture!" << endl;
				exit(EXIT_FAILURE);
			}
			enemy.setTexture(enemyTexture);
		}
		enemyX = x;
		enemyY = y;
		enemy.setPosition(enemyX, enemyY);

	}


//====================================================== 
// setEnemySpeed: sets the speed for the enemy
// parameters: 
//		num: contains the intended speed for the enemies
// return type: void
//======================================================
	void setEnemySpeed(float num)
	{
		speed = num;
	}

//====================================================== 
// drawEnemy: draws the enemy onto the window
// parameters: 
//		win: contains all the information to be displayed 
// return type: void
//======================================================
	void drawEnemy(RenderWindow &win)
	{
		win.draw(enemy);
	}

//====================================================== 
// moveEnemy: changes the enemies location a small amount each frame
// parameters: 
// return type: void 
//======================================================
	void moveEnemy()
	{
		enemy.move(0, speed);
	}

//====================================================== 
// getAlienBounds: gets the space the enemy takes up
// parameters: 
// return type: FloatRect of not only the location, but how large the sprite is 
//======================================================
	FloatRect getAlienBounds()
	{
		return enemy.getGlobalBounds();
	}

//====================================================== 
// getAlienPositionX: gets the x location of the Enemy 
// parameters: 
// return type: float holding the x value 
//======================================================
	float getAlienPositionX()
	{
		return enemy.getPosition().x;
	}

//====================================================== 
// getAlienPositionY: gets the y location of the Enemy 
// parameters: 
// return type: float holding the y value 
//======================================================
	float getAlienPositionY()
	{
		return enemy.getPosition().y;
	}

//====================================================== 
// resetAlienPosition: resets the location of the enemy 
// parameters: 
// return type: void
//======================================================
	void resetAlienPosition()
	{
		enemy.setPosition(enemyX, 40);
	}

};