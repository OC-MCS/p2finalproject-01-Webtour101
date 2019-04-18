#pragma once
using namespace sf;
using namespace std;

class Game
{
private:
	int EnemiesKilled;
	int LivesLeft;
	int gameLevel = 0;
public:

//====================================================== 
// Game: constructor of a Game object
// parameters: 
// return type: none
//======================================================
	Game()
	{
		EnemiesKilled = 0;
		LivesLeft = 3;
	}

//====================================================== 
// getLives: gets the number of lives remaining in the game
// parameters: 
// return type: integer holding number of lives
//======================================================
	int getLives()
	{
		return LivesLeft;
	}

//====================================================== 
// looseLife: deincraments the number of current lives
// parameters: 
// return type: none
//======================================================
	void looseLife()
	{
		LivesLeft--;
	}

//====================================================== 
// getEnemies: get the number of enemies killed so far in the level
// parameters: 
// return type: integer holding nuber of killed enemies
//======================================================
	int getEnemies()
	{
		return EnemiesKilled;
	}

//====================================================== 
// increaseKill: increments the number of enemies killed by 1
// parameters: 
// return type: none
//======================================================
	void increaseKill()
	{
		EnemiesKilled++;
	}

//====================================================== 
// Game: gets the current level being played 
// parameters: 
// return type: int& returning the level that is currently set
//======================================================
	int& getGameLevel()
	{
		return gameLevel;
	}

//====================================================== 
// setLevel: sets the gameLevel to the provided integer
// parameters: 
//		lvl: the desired level that the game should be set to
// return type: none
//======================================================
	void setLevel(int lvl)
	{
		gameLevel = lvl;
	}

//====================================================== 
// resetEnemies: resets the number of enemies killed
// parameters: 
// return type: none
//======================================================
	void resetEnemies()
	{
		EnemiesKilled = 0;
	}

//====================================================== 
// resetLives: resets the number of lives the user has
// parameters: 
// return type: none
//======================================================
	void resetLives()
	{
		LivesLeft = 3;
	}
};