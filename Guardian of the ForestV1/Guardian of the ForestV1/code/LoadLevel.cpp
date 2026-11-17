#include "Engine.h"

#include <iostream>

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	/*Nicholas fixing - adding a border adound the map*/
	/*
	// Get the size of the loaded level in pixels.
	float levelWidth = m_LM.getLevelSize().x * TILE_SIZE;

	float levelHeight = m_LM.getLevelSize().y * TILE_SIZE;

	// Set up the border around the level.
	m_LevelBorder.setPosition(0.f, 0.f);
	m_LevelBorder.setSize(sf::Vector2f(levelWidth, levelHeight));

	m_LevelBorder.setFillColor(sf::Color::Transparent);

	*/
	/*End of Nicholas - code*/

	// How long is this new time limit

	m_TimeRemaining = m_LM.getTimeLimit();

	// Spawn the player
	m_Player.spawn(m_LM.getStartPosition(), GRAVITY);

	m_PowerOrb.spawn(Vector2f(100, 1000));


	// Spawn the enemy at a specific tile position (for example, tile (10, y))	
	int enemyTileX = 25;

	std::cout << "Enemy spawn column: " << enemyTileX << std::endl;
	for (int y = 0; y < m_LM.getLevelSize().y; y++)
	{
		if (m_ArrayLevel[y][enemyTileX] == 1)
		{
			float enemyX = enemyTileX * TILE_SIZE;
			float enemyY = (y * TILE_SIZE) - 100.f;

			m_Enemy.setPosition(Vector2f(enemyX, enemyY));

			// Enemy spawned, exit the loop
			break;
		}
	}

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
	}