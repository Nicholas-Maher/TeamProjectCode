#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		loadLevel();
	}

	if (m_Playing)
	{
		// Update the player
		m_Player.update(dtAsSeconds);

		// Detect collisions and see if the player has reached the goal tile
		// The second part of the if condition is only executed
		// when the player is touching the home tile
		if (detectCollisions(m_Player))
		{
			// New level required
			m_NewLevelRequired = true;
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Has the player run out of time
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

	}// End if playing

	// Sets the main to focus on the player

	/*Nicholas Camera fix to stay verial but foloow the player horizontally  */

	//Keep the level vertically centred.
	float levelHeight = m_LM.getLevelSize().y * TILE_SIZE;

	float viewWidth = m_MainView.getSize().x;
	float viewHeight = m_MainView.getSize().y;

	// Follow the player horizontally,
	float cameraX = m_Player.getCenter().x;

	if (cameraX < viewWidth / 2.f)
	{
		cameraX = viewWidth / 2.f;
	}

	// Keep the camera within the right of player
	float levelWidth = m_LM.getLevelSize().x * TILE_SIZE;

	if (levelWidth > viewWidth && cameraX > levelWidth - viewWidth / 2.f)
	{
		cameraX = levelWidth - viewWidth / 2.f;
	}

	float cameraY = levelHeight / 2.f;

	// If the level is shorter than the screen, centre the view on the level.
	if (levelHeight < viewHeight)
	{
		cameraY = levelHeight / 2.f;
	}

	m_MainView.setCenter(cameraX, cameraY);
}
/*End of Camera Code -- Nicholas */