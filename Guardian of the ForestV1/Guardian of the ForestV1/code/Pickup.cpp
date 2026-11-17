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

FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
	return m_Sprite;
}

int Pickup::getValue() const
{
	return m_Value;
}

bool Pickup::isActive()
{
	return m_IsActive;
}