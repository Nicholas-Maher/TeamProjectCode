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

		m_HealthBar.setSize(Vector2f(m_Player.getHealth() * m_HealthBarWidthMultiplier, 70));

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
	m_MainView.setCenter(m_Player.getCenter());
}