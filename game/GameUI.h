#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Game.h"
#include "BombSet.h"
#include "MissileSet.h"
#include "Enemies.h"
using namespace std;
using namespace sf;

class GameUI
{
private:
	RectangleShape startBtn;
	Vector2f btnPos;
	
public:

//====================================================== 
// GameUI: constructor of a GameUI object
// parameters: 
// return type: none
//======================================================
	GameUI()
	{
		btnPos.x = 390;
		btnPos.y = 290;
		startBtn.setPosition(btnPos);
		startBtn.setFillColor(Color::Transparent);
		startBtn.setOutlineColor(Color::Green);
		startBtn.setOutlineThickness(2);
		startBtn.setSize(Vector2f(50, 30));
	}

//====================================================== 
// drawStart: draws the start screen at the beginning of the game
// parameters: 
//		win: the RenderWindow, containing all the information on the window
// return type: void
//======================================================
	void drawStart(RenderWindow &win)
	{
			Font font;
			if (!font.loadFromFile("C:\\Windows\\Fonts\\agencyr.ttf"))
				die("couldn't load font");
			Font titleFont;
			if (!titleFont.loadFromFile("C:\\Windows\\Fonts\\agencyr.ttf"))
				die("couldn't load font");

			// Title for the Game
			Text title("Wanna-be Space Invaders!", titleFont, 70);
			title.setFillColor(Color::Green);
			title.setPosition(110, 100);

			// Title for the start Button
			Text start("START", font, 25);
			start.setPosition(btnPos.x, btnPos.y);

			win.draw(title);
			win.draw(start);
			win.draw(startBtn);
	}

//====================================================== 
// drawPlayingSpace: draws the current game information after it has begun
// parameters: 
//		win: the RenderWindow, containing all the information on the window
//		game: the Game object, containing the number of enemies killed and lives left
// return type: void
//======================================================
	void drawPlayingSpace(RenderWindow &win, Game &game)
	{
		Font font;
			if (!font.loadFromFile("C:\\Windows\\Fonts\\agencyr.ttf"))
				die("couldn't load font");

			// Title for Lives
			Text lives("Lives Remaining: " + to_string(game.getLives()), font, 22);
			lives.setFillColor(Color::Green);
			lives.setPosition(10, 10);

			// Title for Enemies Killed
			Text killed("Enemies Killed: " + to_string(game.getEnemies()), font, 22);
			killed.setFillColor(Color::Green);
			killed.setPosition(680, 10);

			win.draw(lives);
			win.draw(killed);
	}

//====================================================== 
// handleMouseUp: Checks to see if, when the mouse is pressed, the mouse is within the "Start" or "Retry" button
// parameters: 
//		mousePos: Contains the coordinates of the cursor at the moment the mouse was clicked.
//		game: used to set the level to lvl 1 to start the game
//		gameWon: a bool to be set to false, so after the game is won, you can play again
// return type: bool: that determines if the cursor was within the button
//======================================================
	bool handleMouseUp(Vector2f mousePos, Game &game, bool &gameWon)
	{
		bool isButtonClicked = false;
		if (startBtn.getGlobalBounds().contains(mousePos))
		{
			game.setLevel(1);
			gameWon = false;
			isButtonClicked = true;
		}
		return isButtonClicked;
	}

//====================================================== 
// die: Displays a message if a font cant be loaded
// parameters: 
//		msg: contains the string that displays which font couldnt load
// return type: void
//======================================================
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}

//====================================================== 
// drawEnd: draws the ending screen after the game has finished.
//	displaying different things if the game was won or lost
// parameters: 
//		win: the RenderWindow, containing all the information on the window
//		gameWon: a bool, to determine if the game was succesfully completed or not
// return type: void
//======================================================
	void drawEnd(RenderWindow &win, bool gameWon)
	{
		Font font;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\agencyr.ttf"))
			die("couldn't load font");
		Font titleFont;
		if (!titleFont.loadFromFile("C:\\Windows\\Fonts\\agencyr.ttf"))
			die("couldn't load font");

		// Title of the end of the Game
		Text Ending("Game Over.", titleFont, 70);
		Ending.setFillColor(Color::Green);
		Ending.setPosition(300, 100);

		// Checks to see which message to display
		if (gameWon)
		{
			Text message1("Congratulations! You have won!", font, 25);
			message1.setPosition(285, 220);
			win.draw(message1);
		}
		else
		{
			Text message2("Sorry, you have lost.", font, 25);
			message2.setPosition(340, 220);

			win.draw(message2);
		}
		// Title for the retry button
		Text retry("RETRY", font, 25);
		retry.setPosition(btnPos.x, btnPos.y);
		win.draw(startBtn);
		win.draw(retry);
		win.draw(Ending);
	}

//====================================================== 
// setUpLevel: sets up the playing space, depending on the level of the game
// parameters: 
//		window:contains all the window information
//		gameSet: contains the number of lives left, and enemies killed
//		player: contains the loaction of the player
//		badEnemies: contains the list of all the current enemies on the screen
//		missiles: contains the list of all the current missiles in flight
//		count: a counter to keep track of how many frames have passed.
//		bombs: contains the list of all of the current bombs being dropped by the aliens
//		speed: the number of the speed for the enemies. differs based on the level
//		badEnemies2: contains the list of all the level 2 enemies.
//		gameWon: a boolian to keep track of if the game has been finished or not
// return type: void
//======================================================
	void setUpLevel(RenderWindow &window, Game &gameSet, Ship &player, Enemies &badEnemies, MissileSet &missiles, int &count, BombSet &bombs, float speed, Enemies &badEnemies2, bool &gameWon)
	{
		drawPlayingSpace(window, gameSet);
		player.drawShip(window);
		player.moveShip();
		badEnemies.isHordeTooLow(gameSet);
		badEnemies.drawHorde(window);
		badEnemies.hitDetection(missiles, gameSet);
		// Checks how many frames have passed
		if (count < 40)
		{
			count++;
		}
		// every 40 frames, a bomb will be dropped
		else
		{
			badEnemies.moveHorde();
			bombs.addBomb(badEnemies);
			count = 0;
		}
		bombs.isShipHit(player, gameSet, badEnemies, window);
		bombs.drawBombs(window, speed);		
		missiles.drawMissiles(window);
		// Checks to see if the player has ran out of lives
		if (gameSet.getLives() <= 0)
		{
			gameSet.setLevel(3);
		}
		// Checks to see if the player has killed all the enemies
		if (gameSet.getEnemies() == 10)
		{
			
			gameSet.setLevel(gameSet.getGameLevel() + 1);	
			if (gameSet.getGameLevel() == 2)
			{
				badEnemies2.createEnemies(gameSet);
			}
			else if (gameSet.getGameLevel() == 3)
			{
				gameWon = true;
			}
			gameSet.resetEnemies();								
		}
	}

//====================================================== 
// resetAll: resets the entire game, so another game can be played
// parameters: 
//		gameSet: the Game object, containing the number of enemies killed and lives left
//		badEnemies: contains the list of any level 1 enemies remaining
//		badEnemies2: contains the list of any level 2 enemies remaining
//		bombs: contains the list of any bombs remaining that are being dropped by the enemies
//		missiles: contains the list of all of the missiles currently in flight
// return type: void
//======================================================
	void resetAll(Game &gameSet, Enemies &badEnemies, Enemies &badEnemies2, BombSet &bombs, MissileSet &missiles)
	{
		gameSet.setLevel(1);
		gameSet.resetEnemies();
		gameSet.resetLives();
		badEnemies.deleteEnemyList();
		badEnemies2.deleteEnemyList();
		bombs.deleteBombList();
		missiles.deleteMissileList();
	}
};