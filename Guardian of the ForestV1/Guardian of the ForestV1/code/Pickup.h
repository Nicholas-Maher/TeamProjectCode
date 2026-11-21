#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
protected:

	Sprite m_Sprite;
	String m_Type;

	// Where is the the game object
	Vector2f m_Position;

	bool m_IsActive;

	// How much is this pickup worth?
	int m_Value;

	// Public prototypes go here
public:

	Pickup();

	virtual void spawn(Vector2f startPosition) = 0;

	FloatRect getPosition();

	Sprite getSprite();

	String getType();

	// Get the goodness from the pickup - pure virtual method
	// like how Engine::detectCollisions does
	virtual void gotIt() = 0;

	// return the value of m_Value
	int getValue() const;

	// Returns if the pickup is active
	bool isActive();
};