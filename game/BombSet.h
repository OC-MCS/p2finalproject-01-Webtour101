#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Bomb.h"
#include "Enemies.h"
#include "Ship.h"
#include "Game.h"
using namespace std;
using namespace sf;

class BombSet
{
private:
	list <Bomb> explosives;
	Texture bombTexture;
	int count = 0;
public:

//====================================================== 
// addBomb: makes a list of bombs, and puting the location needed for each bomb 
// parameters: 
//		aliens: contains the location of a randomly selected alien
// return type: void
//======================================================
	void addBomb(Enemies aliens) // pass it a random enemy
	{
		if (!bombTexture.loadFromFile("Bomb.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}

		Bomb boom(bombTexture);
		boom.setBombPos(aliens.getRandEnemy()); // pass it the random enemy

		explosives.push_back(boom);
	}

//====================================================== 
// drawBombs: runs through the list, and draws each seperate bomb
// parameters: 
//		win: contains all the information to be displayed 
//		speed: contains the speed for the bomb to drop, based on the level
// return type: void
//======================================================
	void drawBombs(RenderWindow &win, float speed)
	{
		
		list<Bomb>::iterator iter;
		for (iter = explosives.begin(); iter != explosives.end(); iter++)
		{
			iter->drawBomb(win, speed);
		}
	}

//====================================================== 
// deleteBomb: runs through the list of bombs and deletes each one 
// parameters: 
// return type: void
//======================================================
	void deleteBomb()
	{
		list<Bomb>::iterator iter;
		for (iter = explosives.begin(); iter != explosives.end();)
		{
			if (iter->getBombY() >= 600)
			{
				iter = explosives.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

//====================================================== 
//	getListOfBomb: allows access to the list of Bombs 
// parameters: 
// return type: list<Bomb> the current list of all bombs on the screen
//======================================================
	list<Bomb>& getListOfBomb()
	{
		return explosives;
	}

//====================================================== 
// isShipHit: Checks if any of the bombs have struck the ship
// parameters: 
//		goodGuy: contains the location of the ship;
//		game: contains the number of lives and number of enemies killed
//		badGuys: allows to reset the list of enemies if there is a hit
//		window: contains all of the information currently on the screen
// return type: void 
//======================================================
	void isShipHit(Ship &goodGuy, Game &game, Enemies &badGuys, RenderWindow &window)
	{
		list<Bomb>::iterator iter;
		for (iter = explosives.begin(); iter != explosives.end();)
		{
			if (iter->getBombBounds().intersects(goodGuy.getShipBounds()))
			{
				game.looseLife();
				iter = explosives.erase(iter);
				badGuys.resetHorde();
				goodGuy.resetShip(window);
			}
			else
			{
				iter++;
			}
		}
	}

//====================================================== 
// deleteBombList: runs through the list of bombs and deletes each one 
// parameters: 
// return type: void
//======================================================
	void deleteBombList()
	{
		list<Bomb>::iterator iter;
		for (iter = explosives.begin(); iter != explosives.end();)
		{
			iter = explosives.erase(iter);
		}
	}
};