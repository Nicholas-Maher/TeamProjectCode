#include "PlayableCharacter.h"
#include <iostream>
using namespace std;

void PlayableCharacter::spawn(Vector2f startPosition, float gravity)
{
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

}

void PlayableCharacter::update(float elapsedTime)
{
	// incrementally increases speed while right is pressed until max speed is reached
	if (m_WalkRightPressed)
	{
		walkRight(elapsedTime);
	}
	
	// incrementally increases speed while right is pressed until max speed is reached
	if (m_RunRightPressed)
	{
		runRight(elapsedTime);
	}
	
	// incrementally increases speed while left is pressed until max speed is reached
	if (m_WalkLeftPressed)
	{
		walkLeft(elapsedTime);
	}
	
	// incrementally increases speed while left is pressed until max speed is reached
	if (m_RunLeftPressed)
	{
		runLeft(elapsedTime);
	}

	// If there is no input for walking or running in any direction, the player will slide quickly to a stop in the direction they were last travelling
	if (!m_WalkRightPressed && !m_WalkLeftPressed && !m_RunRightPressed && !m_RunLeftPressed)
	{
		if (m_VelocityX > 0)
		{
			slideStopRight(elapsedTime);
		}
		else if (m_VelocityX < 0)
		{
			slideStopLeft(elapsedTime);
		}
	}

	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2.1 * elapsedTime;
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}

	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);

}

FloatRect PlayableCharacter::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
		);
}

FloatRect PlayableCharacter::getFeet()
{
	return m_Feet;
}

FloatRect PlayableCharacter::getHead()
{
	return m_Head;
}

FloatRect PlayableCharacter::getLeft()
{
	return m_Left;
}

FloatRect PlayableCharacter::getRight()
{
	return m_Right;
}

Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}
/****** Player movement methods - Patrick *****/
void PlayableCharacter::walkRight(float elapsedTime)
{
	m_VelocityX += m_MaxWalkSpeed * m_Acceleration * elapsedTime;

	// Stop accelerating once top speed is reached
	if (m_VelocityX > m_MaxWalkSpeed)
	{
		m_VelocityX = m_MaxWalkSpeed;
		cout << "Walk Right - Cap hit " << endl;
	}
	// Multiplying by delta t is needed here to prevent the character hitting max speed immediately
	m_Position.x += m_VelocityX * elapsedTime;

	
	//m_Position.x += m_MaxWalkSpeed * elapsedTime;
	cout << "Walk Right - Speed: " << m_MaxWalkSpeed << " Velocity: " << m_VelocityX << endl;
}

void PlayableCharacter::runRight(float elapsedTime)
{
	m_VelocityX += m_MaxRunSpeed * m_Acceleration * elapsedTime;

	// Stop accelerating once top speed is reached
	if (m_VelocityX > m_MaxRunSpeed)
	{
		m_VelocityX = m_MaxRunSpeed;
	}
	// Multiplying by delta t is needed here to prevent the character hitting max speed immediately
	m_Position.x += m_VelocityX * elapsedTime;
	cout << "Run Right - Speed: " << m_MaxRunSpeed << " Velocity: " << m_VelocityX << endl;
}

void PlayableCharacter::slideStopRight(float elapsedTime)
{
	m_VelocityX -= m_MaxWalkSpeed * m_Deceleration * elapsedTime;

	if (m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}
	m_Position.x += m_VelocityX * elapsedTime;
}

void PlayableCharacter::walkLeft(float elapsedTime)
{
	m_VelocityX -= m_MaxWalkSpeed * m_Acceleration * elapsedTime;

	if (m_VelocityX < -m_MaxWalkSpeed)
	{
		m_VelocityX = -m_MaxWalkSpeed;
		cout << "Walk Left - Cap hit " << endl;
	}
	m_Position.x += m_VelocityX * elapsedTime;

	//m_Position.x += m_MaxWalkSpeed * elapsedTime;
	cout << "Walk Left - Speed: " << m_MaxWalkSpeed << " Velocity: " << m_VelocityX << endl;
}

void PlayableCharacter::runLeft(float elapsedTime)
{
	m_VelocityX -= m_MaxRunSpeed * m_Acceleration * elapsedTime;

	if (m_VelocityX < -m_MaxRunSpeed)
	{
		m_VelocityX = -m_MaxRunSpeed;
	}
	m_Position.x += m_VelocityX * elapsedTime;
	cout << "Run Left - Speed: " << m_MaxRunSpeed << " Velocity: " << m_VelocityX << endl;
}




void PlayableCharacter::slideStopLeft(float elapsedTime)
{
	m_VelocityX += m_MaxWalkSpeed * m_Deceleration * elapsedTime;

	if (m_VelocityX > 0)
	{
		m_VelocityX = 0;
	}
	m_Position.x += m_VelocityX * elapsedTime;
}

void PlayableCharacter::stopFalling(float position)
{
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void PlayableCharacter::stopRight(float position)
{
	
	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopJump()
{
	// Stop a jump early 
	m_IsJumping = false;
	m_IsFalling = true;
}



