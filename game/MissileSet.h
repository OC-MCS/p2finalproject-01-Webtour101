#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Missile.h"
using namespace std;
using namespace sf;

class MissileSet
{
private:
	list <Missile> ammo;
	Texture missileTexture;
	int count = 0;
public:

//====================================================== 
// addMissile: makes a list of missiles, and puting the location needed for each missile
// parameters: 
//		goodGuy: contains the location of the player
// return type: void
//======================================================
	void addMissile(Ship &goodGuy)
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}

		Missile boom(missileTexture);
		boom.setMissilePos(goodGuy);

		ammo.push_back(boom);
	}

//====================================================== 
// drawMissiles: runs through the list, and draws each seperate missile
// parameters: 
//		win: contains all the information to be displayed 
// return type: void
//======================================================
	void drawMissiles(RenderWindow &win)
	{
		list<Missile>::iterator iter;
		for (iter = ammo.begin(); iter != ammo.end();iter++)
		{
			iter->drawMissile(win);
		}
	}

//====================================================== 
// deleteMissile: runs through the list of missiles and deletes each one 
// parameters: 
// return type: void
//======================================================
	void deleteMissile()
	{
		list<Missile>::iterator iter;
		for (iter = ammo.begin(); iter != ammo.end();)
		{
			if (iter->getMissileY() <= 0)
			{
				iter = ammo.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

//====================================================== 
//	getListOfMissile: allows access to the list of Missiles 
// parameters: 
// return type: list<Missile> the current list of all missiles on the screen
//======================================================
	list<Missile>& getListOfMissile()
	{
		return ammo;
	}

//====================================================== 
// deleteMissileList: runs through the list of missiles and deletes each one 
// parameters: 
// return type: void
//======================================================
	void deleteMissileList()
	{
		list<Missile>::iterator iter;
		for (iter = ammo.begin(); iter != ammo.end();)
		{
			iter = ammo.erase(iter);
		}
	}
};