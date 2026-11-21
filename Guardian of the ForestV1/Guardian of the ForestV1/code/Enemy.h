#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Enemy
{
private:

	// Rectangle shape to represent enemy
	RectangleShape m_Body;
	// Vector holds position of enemy	
	Vector2f m_Position;

	Vector2f m_StartPosition; // Starting position of the enemy

	float m_PatrolDistance = 150.f; // Distance the enemy patrols


	float m_Speed = 100.f; // Speed of the enemy

	bool m_WasGroundAhead = true; // To track if there was ground ahead in the last update

	float m_DetectionRange = 250.f; // Range at which the enemy can detect the player

	// Enemy chase the player if they are within the detection range
	bool m_IsChasing = false;
	// Enemy chase speed
	float m_ChaseSpeed = 150.f;
	// Enemy stopping distance from chasing the player
	float m_StoppingDistance = 15.f;

	bool m_IsAlive;

public:

	//Initializes the enemy with a position
	Enemy(Vector2f startPosition);

	// Draws the enemy on the window
	void draw(RenderWindow& window);

	// Returns position of enemy
	Vector2f getPosition() const;

	void update(float dt, bool groundAhead, FloatRect playerBounds); // Update the enemy position by elapsed time and check for ground ahead

	// Sets the position of the enemy
	void setPosition(Vector2f position);

	// enemies speed and direction
	float getSpeed() const;

	// sets the enemy alive status
	void setIsAlive(bool aliveStatus);

	bool getIsAlive() const;

	bool canDetectPlayer(FloatRect playerBounds); // Check if the enemy can detect the player based on their position

	void setChasing(bool chasing); // Set the chasing state of the enemy

	float getMovementDirection() const; // Get the current movement direction of the enemy (1 for right, -1 for left)

	void updateChaseDirection(FloatRect playerBounds); // Update the direction of the enemy based on the player's position

};
