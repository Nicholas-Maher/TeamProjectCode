#include "Player.h"
#include "TextureHolder.h"

Player::Player()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/pacman-spritesheet-resized-810-730.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 12,62,50,50 });
	ani_counter = 1;

	m_JumpDuration = .50;
}

bool Player::handleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}

	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}
	// Check if walking keys are pressed
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_WalkLeftPressed = true;
	}
	else
	{
		m_WalkLeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_WalkRightPressed = true;
		
	}
	else
	{
		m_WalkRightPressed = false;
	}

	// Check if running keys are pressed
	if (Keyboard::isKeyPressed(Keyboard::J))
	{
		m_RunLeftPressed = true;
	}
	else
	{
		m_RunLeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::L))
	{
		m_RunRightPressed = true;
	}
	else
	{
		m_RunRightPressed = false;
	}
	

	return m_JustJumped;
}