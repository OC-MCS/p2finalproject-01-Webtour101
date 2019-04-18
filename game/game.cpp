//============================================================
// Name: Josiah Ferguson
// Project: Final Assignment; Wanna-be Space Invaders
// Due Date: April 19th 2019
//============================================================
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "GameUI.h"
#include "Game.h"
#include "Ship.h"
#include "Enemies.h"
#include "MissileSet.h"
#include "BombSet.h"
using namespace std;
using namespace sf;


int main()
{
	// Window Information
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60);

	// Stars and Background Informaton
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Sprite background;
	background.setTexture(starsTexture);
	background.setScale(1.5, 1.5);


	// Variables
	Ship player(window);
	GameUI Start;
	Game gameSet;
	Enemies badEnemies;
	Enemies badEnemies2;
	MissileSet missiles;
	BombSet bombs;
	int count = 0;
	bool gameWon = false;
	bool gameLost = false;


	// Animation loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				// To check if the space bar was pressed to fire a missile
				if (event.key.code == Keyboard::Space)
				{
					missiles.addMissile(player);
				}
			}
			// To check if the mouse was pressed
			else if (event.type == Event::MouseButtonReleased)
			{
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					// To check if the mouse is clicking inside the button
					bool isClicked = Start.handleMouseUp(mousePos, gameSet, gameWon);
					if (isClicked)
					{
						Start.resetAll(gameSet, badEnemies, badEnemies2, bombs, missiles);
						badEnemies.createEnemies(gameSet);
					}
			}
		}
		// Drawing every frame of what is happening.
		window.draw(background);

		// To let the user start the game;
		if (gameSet.getGameLevel() == 0)
		{
			Start.drawStart(window);
		}

		// Playing level 1
		else if (gameSet.getGameLevel() == 1)
		{
			Start.setUpLevel(window, gameSet, player, badEnemies, missiles, count, bombs, 8, badEnemies2, gameWon);
		}

		// Playing level 2
		else if (gameSet.getGameLevel() == 2)
		{
			Start.setUpLevel(window, gameSet, player, badEnemies2, missiles, count, bombs, 12, badEnemies2, gameWon);
		}

		// showing "game over" screen, displaying they either won or lost.
		else if (gameSet.getGameLevel() == 3)
		{
			Start.drawEnd(window, gameWon);
		}

		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();
	} 
	return 0;
}
