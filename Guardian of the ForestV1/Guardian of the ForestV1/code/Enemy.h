#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:

	// Rectangle shape to represent enemy
	sf::RectangleShape m_Body;
	// Vector holds position of enemy	
	sf::Vector2f m_Position;

public:

	//Initializes the enemy with a position
	Enemy(sf::Vector2f startPosition);

	// Draws the enemy on the window
	void draw(sf::RenderWindow& window);

	// Returns position of enemy
	sf::Vector2f getPosition() const;

};
