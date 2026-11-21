#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

class Pickup : public GameObject
{
protected:

	String m_Type;

	bool m_IsActive;

	// How much is this pickup worth?
	int m_Value;

	// Public prototypes go here
public:

	Pickup();

	virtual void spawn(Vector2f startPosition) = 0;

	String getType();

	// Get the goodness from the pickup - pure virtual method
	// like how Engine::detectCollisions does
	virtual void gotIt() = 0;

	// return the value of m_Value
	int getValue() const;

	// Returns if the pickup is active
	bool isActive();
};