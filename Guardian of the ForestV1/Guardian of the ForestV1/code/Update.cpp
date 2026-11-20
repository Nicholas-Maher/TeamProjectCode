#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		m_LevelTimeElapsed = 0;
		loadLevel();
	}

	// if (m_Playing) // og had this
	if (state == State::PLAYING)
	{
		// Update the player
		m_Player.update(dtAsSeconds);

		// Check if the enemy can detect the player
		bool playerDetected = m_Enemy.canDetectPlayer(m_Player.getPosition());

		// Set enemy state based on player detection
		m_Enemy.setChasing(playerDetected);

		// Determine the direction of the enemy based on the player's position
		m_Enemy.updateChaseDirection(m_Player.getPosition());

		// Check ground and update enemy movement
		m_Enemy.update(dtAsSeconds, hasGroundAhead(), m_Player.getPosition());


		// Detect collisions and see if the player has reached the goal tile
		// the inner conditions set the bool required for a new level to be loaded if the level beaten wasn't the last level and set the game state 
		// to victory if the player reaches the goal on the last level
		if (detectCollisions(m_Player))
		{
			m_TotalTimeElapsed += m_LevelTimeElapsed;

			if (m_LM.getCurrentLevel() < m_LM.getNumLevels())
			{
				// New level required
				m_NewLevelRequired = true;
				// Play the reach goal sound
				m_SM.playReachGoal();
			}
			// if the player reaches the goal on the last level
			else
			{
				// set the total time text in the victory screen
				m_VictoryScreen.setTimeText(convertTimeToString(m_TotalTimeElapsed));

				// checks if the total time can go into the top times leaderboard
				if (m_TopTimesScreen.isATopTime((int)m_TotalTimeElapsed))
				{
					m_TopTimesScreen.addTimeToLeaderboard((int)m_TotalTimeElapsed);
				}

				m_TotalTimeElapsed = 0; // resets the total time variable
				state = State::VICTORY;
				m_NewLevelRequired = false;
				// Play the reach goal sound
				m_SM.playReachGoal();
				return;
			}
		}

		// increment the time elapsed
		m_LevelTimeElapsed += dtAsSeconds;

		// Time to update the HUD?
		// Increment the number of frames since the last HUD calculation
		m_FramesSinceLastHUDUpdate++;

		// Update the HUD every m_TargetFramesPerHUDUpdate frames
		if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
		{
			// Update game HUD text
			stringstream ssLevel;

			// Update the time text
			m_Hud.setTime(convertTimeToString(m_LevelTimeElapsed));

			// Update the level text
			ssLevel << "Level: " << m_LM.getCurrentLevel();
			m_Hud.setLevel(ssLevel.str());

			// update the health and power bars
			m_Hud.setHealthBar(m_Player.getHealth(), m_Player.getFullHealth());
			m_Hud.setPowerBar(m_Player.getPower(), m_Player.getFullPower());


			m_FramesSinceLastHUDUpdate = 0;
		}

	}// End if playing

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Player.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Player.getCenter());
		}
	}

	m_MainView.setCenter(m_Player.getCenter());

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

	/*End of Camera Code -- Nicholas */
		
	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function