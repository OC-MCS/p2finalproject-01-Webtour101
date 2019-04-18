#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Alien.h"
#include "Missile.h"
#include "MissileSet.h"
#include "Game.h"
#include <cstdlib>

using namespace std;
using namespace sf;

class Enemies
{
private:
	list <Alien> horde;
	Texture enemy1Texture;

public:

//====================================================== 
// Enemies: empty contructor to make an enemy object 
// parameters: 
// return type: none
//======================================================
	Enemies()
	{
	}

//====================================================== 
// createEnemies: makes a list of Aliens, and puting the variable needed for each seperate Alien 
// parameters: 
//		game: contains the needed level to determine what kind of enemy to be made
// return type: void
//======================================================
	void createEnemies(Game game)
	{
		// initial location of the first enemy
		float x = 20;
		float y = 40;

		// creating 10 enemies
		for (int i = 0; i < 10; i++)
		{
			Alien badGuy(x, y, enemy1Texture, game);
			if (game.getGameLevel() < 2)
			{
				badGuy.setEnemySpeed(25);
			}
			else if (game.getGameLevel() == 2)
			{
				badGuy.setEnemySpeed(45);
			}
			// puting the created enemy into the list
			horde.push_back(badGuy);
			// incraments the x location for the next enemy
			x = x + 80;
		}
	}

//====================================================== 
// moveHorde: runs through the list, and moves each seperate enemy
// parameters: 
// return type: void 
//======================================================
	void moveHorde()
	{
		list<Alien>::iterator iter;
		for (iter = horde.begin(); iter != horde.end(); iter++)
		{
			iter->moveEnemy();
		}
	}

//====================================================== 
// drawHorde: runs through the list, and draws each seperate enemy
// parameters: 
//		win: contains all the information to be displayed 
// return type: void
//======================================================
	void drawHorde(RenderWindow &win)
	{
		list<Alien>::iterator iter;
		for (iter = horde.begin(); iter != horde.end(); iter++)
		{
			iter->drawEnemy(win);
		}
	}

//====================================================== 
// hitDetection: Checks if any of the enemies have been struck by a missile
// parameters: 
//		booms: contains the list of missiles;
//		gameSet: contains the number of lives and number of enemies killed
// return type: void 
//======================================================
	void hitDetection(MissileSet &booms, Game &gameSet)
	{
		bool didMissileHit = false;
		list<Alien>::iterator EnemyIter;
		list<Missile>::iterator MissileIter;
			for (MissileIter = booms.getListOfMissile().begin(); MissileIter != booms.getListOfMissile().cend();)
			{
					for (EnemyIter = horde.begin(); EnemyIter != horde.end();)
					{
						// nested for loop to run through the list of enemies
						if (EnemyIter->getAlienBounds().intersects(MissileIter->getMissileBounds()))
						{
							EnemyIter = horde.erase(EnemyIter);
							gameSet.increaseKill();
							didMissileHit = true;
						}
						else
						{
							EnemyIter++;
						}
					}
					if (didMissileHit)
					{
						didMissileHit = false;
						MissileIter = booms.getListOfMissile().erase(MissileIter);
					}
					else
					{
						MissileIter++;
					}
			}
	}

//====================================================== 
// getRandEnemy: runs through the list of enemies, and selects one of them to create a bobm
// parameters: 
// return type: Vector2f containing the location of the randomly selected enemy
//======================================================
	Vector2f getRandEnemy()
	{
		int randomNum;
		list<Alien>::iterator iter;
		if (horde.size() != 0)
		{
			randomNum = rand() % (horde.size());

			iter = horde.begin();
			advance(iter, randomNum);

			Vector2f loc(iter->getAlienPositionX(), iter->getAlienPositionY());

			return loc;
		}
	}

//====================================================== 
// isHordeTooLow: runs through the list of enemies, checks if they are too low
// parameters: 
//		game: contains the number of lives the player has
// return type: void 
//======================================================
	void isHordeTooLow(Game &game)
	{
		list<Alien>::iterator iter;
		for (iter = horde.begin(); iter != horde.end();)
		{
			if (iter->getAlienPositionY() > 500)
			{
				list<Alien>::iterator it;
				for (it = horde.begin(); it != horde.end(); it++)
				{
					it->resetAlienPosition();
				}
				game.looseLife();

			}
			else
			{
				iter++;
			}
		}
	}

//====================================================== 
// resetHorde: runs throught the list of enemies and resets the location of each enemy 
// parameters: 
// return type: void
//======================================================
	void resetHorde()
	{
		list<Alien>::iterator iter;
		for (iter = horde.begin(); iter != horde.end(); iter++)
		{
			iter->resetAlienPosition();
		}
	}

//====================================================== 
// deleteEnemyList: runs through the list of enemies and deletes each one 
// parameters: 
// return type: void
//======================================================
	void deleteEnemyList()
	{
		list<Alien>::iterator iter;
		for (iter = horde.begin(); iter != horde.end();)
		{
			iter = horde.erase(iter);
		}
	}
};