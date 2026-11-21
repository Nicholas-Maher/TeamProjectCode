#include "Engine.h"

#include <iostream>

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
		delete[] m_ArrayEnemySpawnPoints[i];
		delete[] m_ArrayPickupSpawnPoints[i];
	}
	delete[] m_ArrayLevel;
	delete[] m_ArrayEnemySpawnPoints;
	delete[] m_ArrayPickupSpawnPoints;

	// Delete the previously allocated memory for enemies (if it exists)
	for (m_vpEnemiesIter = m_vpEnemies.begin(); m_vpEnemiesIter != m_vpEnemies.end(); ++m_vpEnemiesIter)
	{
		delete* m_vpEnemiesIter;
	}
	m_vpEnemies.clear();

	// Delete the previously allocated memory for pickups (if it exists)
	for (m_vpPickupsIter = m_vpPickups.begin(); m_vpPickupsIter != m_vpPickups.end(); ++m_vpPickupsIter)
	{
		delete* m_vpPickupsIter;
	}
	m_vpPickups.clear();

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

	//m_TimeRemaining = m_LM.getTimeLimit();
	
	/*
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
	*/

	// spawn the pickups and enemies
	loadPickups();
	loadEnemies();

	// Spawn the player
	m_Player.spawn(m_LM.getStartPosition(), GRAVITY);

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}

// loads the npc spawn points into their 2d array, creates them at those positions and puts them into the vector
void Engine::loadEnemies()
{
	// add pointers to NPCs to the vector for NPCs
	m_ArrayEnemySpawnPoints = m_LM.nextLevelEnemySpawnPoints();
	for (int x = 0; x < m_LM.getLevelEnemySpawnPointsSize().x; x++)
	{
		for (int y = 0; y < m_LM.getLevelEnemySpawnPointsSize().y; y++)
		{
			int artefact = m_ArrayEnemySpawnPoints[y][x];
			if (artefact == 5 || artefact == 6 || artefact == 7 || artefact == 8)
			{
				Enemy* enemy = nullptr;
				float enemyX, enemyY;
				switch (artefact)
				{
				case 5:
					enemyX = x * TILE_SIZE;
					enemyY = (y * TILE_SIZE);
					enemy = new Enemy(Vector2f(enemyX, enemyY));
					break;

				// add other enemy types here

				}
				m_vpEnemies.push_back(enemy);
			}
		}
	}
}

// loads the pickups
void Engine::loadPickups()
{
	// add pointers to NPCs to the vector for NPCs
	m_ArrayPickupSpawnPoints = m_LM.nextLevelPickupSpawnPoints();
	for (int x = 0; x < m_LM.getLevelPickupSpawnPointsSize().x; x++)
	{
		for (int y = 0; y < m_LM.getLevelPickupSpawnPointsSize().y; y++)
		{
			int artefact = m_ArrayPickupSpawnPoints[y][x];
			if (artefact == 5 || artefact == 6 || artefact == 7 || artefact == 8)
			{
				Pickup* pickup = nullptr;
				float posX = 0;
				float posY = 0;
				switch (artefact)
				{
				// power orb - can be changed to spawn sometimes when enemies die instead
				case 5:
					posX = x * TILE_SIZE;
					posY = y * TILE_SIZE;
					pickup = new PowerOrb;
					break;

					// add other enemy types here

				}

				if (pickup != nullptr)
				{
					pickup->spawn(Vector2f(posX, posY));
					m_vpPickups.push_back(pickup);
				}
			}
		}
	}
}