#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup()
{
	
}

void Pickup::spawn(Vector2f startPosition)
{
	m_Sprite.setPosition(startPosition);
	m_IsActive = true;
}

String Pickup::getType()
{
	return m_Type;
}

int Pickup::getValue() const
{
	return m_Value;
}

bool Pickup::isActive()
{
	return m_IsActive;
}