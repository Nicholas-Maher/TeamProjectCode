#include "Engine.h"

bool Engine::detectCollisions(Player& character)
{
	bool reachedGoal = false;
	// Make a rect for all his parts
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;

	bool playerDamaged = false;

	// Has the character fallen out of the map?
	// This can be part of level manager
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		// respawn the character changeing this mean he falls for every with out end
		character.spawn(m_LM.getStartPosition(), GRAVITY);
		character.hit(m_GameTimeTotal, 20); // the player loses 20 health when they fall off the map
		// sends the player to the game over screen if they run out of health
		if (character.getHealth() <= 0)
		{
			m_GameOverScreen.setMainText("You died!");
			m_LevelTimeElapsed = 0; // resets the level timer
			state = State::GAME_OVER;
		}
	}

	/*  temp version of pickup collision made for just one pickup  */
	if (m_Player.getPosition().intersects(m_PowerOrb.getPosition()) && m_PowerOrb.isActive())
	{
		m_PowerOrb.gotIt();
		m_Player.setPower(m_Player.getPower() + m_PowerOrb.getValue()); // increases the player's power level by the orb value
	}

	/*Nicholas -- player Bourder*/
	/**************************

	// Get the player's current position.
	FloatRect playerBounds = character.getPosition();

	float levelWidth =
		m_LM.getLevelSize().x * TILE_SIZE;

	// Stop the player at the left edge.
	if (playerBounds.left < 0.f)
	{
		character.stopLeft(0.f);
	}

	// Update the player's position after the correction.
	playerBounds = character.getPosition();

	// Stop the player at the right edge.
	if (playerBounds.left + playerBounds.width > levelWidth)
	{
		character.stopRight(levelWidth);
	}

	*///////////////////////////
	/*End of Nicholas - code*/

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Has character been burnt or drowned?
			// Use head as this allows him to sink a bit
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound
						m_SM.playFallInFire();

					}
					else // Water
					{
						// Play a sound
						m_SM.playFallInWater();
					}
				}
			}


			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{

				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}


				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}
			
			// More collision detection here once we have learned about particle effects
			// Has the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is already running			
			if (!m_PS.running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
					{
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());

					}
				}
			}

			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}
		}
	}

	// All done, return, whether or not a new level might be required
	return reachedGoal;
}