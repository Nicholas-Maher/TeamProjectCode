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

	//if (m_Playing)
	if (state == State::PLAYING)
	{
		// Update the player
		m_Player.update(dtAsSeconds);

		// Update the enemy
		m_Enemy.update(dtAsSeconds, hasGroundAhead());

		// Check if the enemy can detect the player
		bool playerDetected = m_Enemy.canDetectPlayer(m_Player.getPosition());

		// testing if player detected
		if (playerDetected)
		{
			std::cout << "Player detected by enemy!" << std::endl;
		}


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
			}
			// if the player reaches the goal on the last level
			else
			{
				// set the total time text in the victory screen
				stringstream ssTotalTime;
				ssTotalTime << "Total Time: " << (int)m_TotalTimeElapsed;
				m_VictoryScreen.setTimeText(ssTotalTime.str());

				// checks if the total time can go into the top times leaderboard
				if (m_TopTimesScreen.isATopTime((int)m_TotalTimeElapsed))
				{
					m_TopTimesScreen.addTimeToLeaderboard((int)m_TotalTimeElapsed);
				}

				state = State::VICTORY;
				m_NewLevelRequired = false;
				return;
			}
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// increment the time elapsed
		m_LevelTimeElapsed += dtAsSeconds;

		// Has the player run out of time
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

		// Time to update the HUD?
		// Increment the number of frames since the last HUD calculation
		m_FramesSinceLastHUDUpdate++;

		// Update the HUD every m_TargetFramesPerHUDUpdate frames
		if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
		{
			// Update game HUD text
			stringstream ssTime;
			stringstream ssLevel;

			// Update the time text
			ssTime << (int)m_TimeRemaining << " seconds";
			m_Hud.setTime(ssTime.str());

			// Update the level text
			ssLevel << "Level: " << m_LM.getCurrentLevel();
			m_Hud.setLevel(ssLevel.str());

			// updates the health bar
			m_Hud.setHealthBar(m_Player.getHealth(), m_Player.getFullHealth());


			m_FramesSinceLastHUDUpdate = 0;
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
	/*End of Camera Code -- Nicholas */

}