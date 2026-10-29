#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPosition)
{
	// Set the position of the enemy
	m_Position = startPosition;
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

void Enemy::update(float dt)
{
	// Move the enemy
	m_Position.x += m_Speed * dt;
	// Update the position of the enemy
	m_Body.setPosition(m_Position);
}