#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:

	// Rectangle shape to represent enemy
	sf::RectangleShape m_Body;
	// Vector holds position of enemy	
	sf::Vector2f m_Position;

	sf::Vector2f m_StartPosition; // Starting position of the enemy

	float m_PatrolDistance = 150.f; // Distance the enemy patrols


	float m_Speed = 100.f; // Speed of the enemy

	bool m_WasGroundAhead = true; // To track if there was ground ahead in the last update

public:

	//Initializes the enemy with a position
	Enemy(sf::Vector2f startPosition);

	// Draws the enemy on the window
	void draw(sf::RenderWindow& window);

	// Returns position of enemy
	sf::Vector2f getPosition() const;

	void update(float dt, bool groundAhead); // Update the enemy position by delta time

	// Sets the position of the enemy
	void setPosition(sf::Vector2f position);

	// enemies speed and direction
	float getSpeed() const;

};
