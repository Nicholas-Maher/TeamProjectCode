#pragma once
#include "Pickup.h"

using namespace sf;

class PowerOrb : public Pickup
{

public:

	PowerOrb();

	void spawn(Vector2f startPosition) override;

	// Get the goodness from the pickup
	void gotIt() override;

};