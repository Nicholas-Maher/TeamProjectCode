#include "PowerOrb.h"
#include "TextureHolder.h"

PowerOrb::PowerOrb()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/orb1.png"));
	m_Value = 50;
	m_Type = "PowerOrb";
}

void PowerOrb::spawn(Vector2f startPosition)
{
	// Place the orb at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

	m_IsActive = true;
}

void PowerOrb::gotIt()
{
	m_IsActive = false;
}
