#include "Enemy.h"
#include <cmath>
#include <iostream>

using namespace sf;

Enemy::Enemy(Vector2f startPosition)
{
	// Set the position of the enemy
	m_Position = startPosition;
	// Set the starting position of the enemy
	m_StartPosition = startPosition;
	// Set the size of the enemy
	m_Body.setSize(Vector2f(50.f,100.f));
	// Set the color of the enemy
	m_Body.setFillColor(Color::Red);
	// Set the position of the enemy body
	m_Body.setPosition(m_Position);
}


// Draws the enemy on the window
void Enemy::draw(RenderWindow& window)
{
	window.draw(m_Body);
}

// Returns position of enemy
Vector2f Enemy::getPosition() const
{
	return m_Position;
}

void Enemy::update(float dt, bool groundAhead, FloatRect playerBounds)
{

	if (!m_IsChasing)
	{
		// If the enemy is not chasing, it should patrol
		if (m_Position.x >= m_StartPosition.x + m_PatrolDistance)
		{
			m_Speed = -100.f;
		}
		else if (m_Position.x <= m_StartPosition.x)
		{
			m_Speed = 100.f;
		}
	}

	// Check if there is safe ground ahead
	if (!groundAhead)
	{
		if (m_IsChasing)
		{
			// Stop chasing at the platform edge
			m_Speed = 0.f;
		}
		else if (m_WasGroundAhead)
		{
			// Reverse direction during normal patrol
			m_Speed = -m_Speed;
		}
	}

	m_WasGroundAhead = groundAhead;

	// Update the position of the enemy based on its speed and delta time
	m_Position.x += m_Speed * dt;

	// Update the position of enemy body
	m_Body.setPosition(m_Position);
}

// Sets the position of the enemy
void Enemy::setPosition(Vector2f position)
{
	m_Position = position;

	m_StartPosition = position; // Update the starting position as well
	m_Body.setPosition(m_Position);
}

// enemies speed andd direction
float Enemy::getSpeed() const
{
	return m_Speed;
}

// Check if the enemy can detect the player based on their position
bool Enemy::canDetectPlayer(FloatRect playerBounds)
{
	//testing if the player is within the detection range of the enemy
	//std::cout << "Detection function called!" << std::endl;

	// Get centre of the player
	float playerX = playerBounds.left + playerBounds.width / 2.f;
	float playerY = playerBounds.top + playerBounds.height / 2.f;

	// Get centre of the enemy
	float enemyX = m_Position.x + 25.f; // Assuming the enemy's width is 50, so center is at +25
	float enemyY = m_Position.y + 50.f; // Assuming the enemy's height is 100, so center is at +50

	// Calculate the distance between the player and the enemy
	float distanceX = playerX - enemyX;
	float distanceY = playerY - enemyY;

	//Checking player detection by enemy
	float distance = std::sqrt((distanceX * distanceX) + (distanceY * distanceY));
	//std::cout << "Distance: " << distance << " | Detection range: " << m_DetectionRange << std::endl;

	// Check if the distance is within the detection range
	return distance <= m_DetectionRange;
}

// Set the chasing state of the enemy
void Enemy::setChasing(bool chasing)
{
	m_IsChasing = chasing;
}

// Get the current movement direction of the enemy (1 for right, -1 for left)
float Enemy::getMovementDirection() const
{
	return m_Speed;
}

void Enemy::updateChaseDirection(FloatRect playerBounds)
{
	if (m_IsChasing)
	{
		// Get the centre of the player
		float playerX = playerBounds.left + playerBounds.width / 2.f;

		// Get the centre of the enemy
		float enemyX = m_Position.x + 25.f;

		// Calculate horizontal distance
		float distanceX = std::abs(playerX - enemyX);

		// Calculate actual gap between character edges
		float actualGap = distanceX - 25.f - (playerBounds.width / 2.f);

		// Stop before reaching the player
		if (actualGap <= m_StoppingDistance)
		{
			m_Speed = 0.f;
		}
		else if (playerX > enemyX)
		{
			m_Speed = m_ChaseSpeed;
		}
		else
		{
			m_Speed = -m_ChaseSpeed;
		}
	}
	else
	{
		// Return to normal patrol speed
		m_Speed = (m_Speed >= 0) ? 100.f : -100.f;
	}
}