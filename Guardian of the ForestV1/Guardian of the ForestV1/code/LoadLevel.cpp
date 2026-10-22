#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	/*Nicholas fixing - adding a border adound the map*/
	// Get the size of the loaded level in pixels.
	float levelWidth = m_LM.getLevelSize().x * TILE_SIZE;

	float levelHeight = m_LM.getLevelSize().y * TILE_SIZE;

	// Set up the border around the level.
	m_LevelBorder.setPosition(0.f, 0.f);
	m_LevelBorder.setSize(sf::Vector2f(levelWidth, levelHeight));

	m_LevelBorder.setFillColor(sf::Color::Transparent);

	/*End of Nicholas - code*/

	// How long is this new time limit

	m_TimeRemaining = m_LM.getTimeLimit();

	// Spawn the player
	m_Player.spawn(m_LM.getStartPosition(), GRAVITY);

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}