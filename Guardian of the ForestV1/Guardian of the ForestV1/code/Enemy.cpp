#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(sf::Vector2f startPosition)
{
	// Set the position of the enemy
	m_Position = startPosition;
	// Set the starting position of the enemy
	m_StartPosition = startPosition;
	// Set the size of the enemy
	m_Body.setSize(sf::Vector2f(50.f,100.f));
	// Set the color of the enemy
	m_Body.setFillColor(sf::Color::Red);
	// Set the position of the enemy body
	m_Body.setPosition(m_Position);
}


// Draws the enemy on the window
void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_Body);
}

// Returns position of enemy
sf::Vector2f Enemy::getPosition() const
{
	return m_Position;
}

void Enemy::update(float dt, bool groundAhead)
{

	// If there is no ground ahead, reverse the direction of the enemy
	if (!groundAhead && m_WasGroundAhead)
	{
		m_Speed = -m_Speed;
	}

	m_WasGroundAhead = groundAhead;

	// Update the position of the enemy based on its speed and delta time
	m_Position.x += m_Speed * dt;

	// Check if enemy has reached the patrol distance and reverse its direction if necessary
	if (m_Position.x >= m_StartPosition.x + m_PatrolDistance)
	{
		m_Speed = -100.f;
	}

	if (m_Position.x <= m_StartPosition.x)
	{
		m_Speed = 100.f;
	}

	// Update the position of enemy body
	m_Body.setPosition(m_Position);
}

// Sets the position of the enemy
void Enemy::setPosition(sf::Vector2f position)
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
bool Enemy::canDetectPlayer(sf::FloatRect playerBounds)
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

	float distance = std::sqrt((distanceX * distanceX) + (distanceY * distanceY));
	//std::cout << "Distance: " << distance << " | Detection range: " << m_DetectionRange << std::endl;

	// Check if the distance is within the detection range
	return distance <= m_DetectionRange;
}